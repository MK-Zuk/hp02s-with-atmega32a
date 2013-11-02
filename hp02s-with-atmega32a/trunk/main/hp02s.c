/*
 * hp02s.c
 *
 *  Created on: 10-10-2012
 *	 Edited on: 10-10-2012
 *      Author: Daniel
 *
 *	All rights reserved.
 */
/*
 * Zajêtosc pamiecie program 1.5kB
 * 					 data 12 bajtow
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "twi.h"
#include "hp02s.h"

volatile unsigned int pressure = 0, D0, T0, P0, S, C;

//********** odczyt wspolczynnik klaibracyjnych
void calibr_factor(void)
{
	xCLR_off;
	twi_start();
	twi_write(160);
	twi_write(2);
	twi_start();
	twi_write(161);
	D0 = (unsigned int)twi_read(1) * 256 + (unsigned int)twi_read(1);
	T0 = (unsigned int)twi_read(1) * 256 + (unsigned int)twi_read(1);
	P0 = (unsigned int)twi_read(1) * 256 + (unsigned int)twi_read(1);
	S = (unsigned int)twi_read(1) * 256 + (unsigned int)twi_read(1);
	C = (unsigned int)twi_read(1) * 256 + (unsigned int)twi_read(0);
	twi_stop();
}

//********** odczyt wartosc D1 i T1
unsigned int read_value_D1(void)
{
	unsigned char i=0;
	unsigned int D1 = 0;

	//odczyt D1
	twi_start();
	twi_write(0xEE);
	twi_write(0xFF);
	twi_write(0xf0);
	twi_stop();
	for(i=0 ; i<38 ; i++)
	{
		_delay_ms(1);
	}
	twi_start();
	twi_write(0xEE);
	twi_write(0xFD);
	twi_start();
	twi_write(0xEF);
	D1 = (unsigned int)twi_read(1) * 256 + (unsigned int)twi_read(0);
	twi_stop();
	return D1;
}

unsigned int read_value_T1(void)
{
	unsigned char i=0;
	unsigned int T1 = 0;

	//odczyt T1
	twi_start();
	twi_write(0xEE);
	twi_write(0xFF);
	twi_write(0xE8);
	twi_stop();
	for(i=0 ; i<38 ; i++)
	{
		_delay_ms(1);
	}
	twi_start();
	twi_write(0xEE);
	twi_write(0xFD);
	twi_start();
	twi_write(0xEF);
	T1 = (unsigned int)twi_read(1) * 256 + (unsigned int)twi_read(0);
	twi_stop();
	return T1;
}

void get_pressure(void)
{
	unsigned int D1, T1;
	int dUP = 0, dUT = 0;
	xCLR_on;
	D1 = read_value_D1();
	xCLR_off;
	xCLR_on;
	T1 = read_value_T1();
	xCLR_off;

	dUP = (int)(D1 - D0);

	dUT = ((29*((int)(T1 - T0))/50)-((int)((T1 - T0)*(T1 - T0)))/76666)* (S/C);

	pressure = (unsigned int)(P0 + 100 * (long int)((dUP) + (dUT)) / S);


}

void init_inter(void)
{
	TCCR1A	|=	(1 << COM1A0);				//ustawienie toogle i CTC
	TCCR1B |= (1 << WGM12);					//pb1
	OCR1A = 61 ;							//122 cykle	oko³o 32kHz
	TCCR1B |= (1 << CS10);					//preskaler 1

	sei();
}


void init(void)
{
	xCLR_out;
	MCLK_out;
	calibr_factor();
	xCLR_off;
	init_inter();
}
