/*
 * main.c
 *
 * Created: 2013-11-02 22:04:14
 *  Author: Marek
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "lib/hp02s.h"
#include "lib/twi.h"
#include "lib/HD44780.h"


void odczyt_cisnienia(void);
volatile unsigned int pressure;

int main(void)
{
    unsigned char licz = 0;
    DDRD = 0xff;
    PORTD = 0xff;
    DDRC = 0xF8;
    PORTC = 0x04;

    init();

    LCD_init();
    LCD_clear();

    while(1)
    {
	    for(licz = 0 ; licz<200 ; licz++)
	    {
		    _delay_ms(10);
	    }
	    odczyt_cisnienia();//odczytuje i wyswietla

    }
}

void odczyt_cisnienia(void)
{
	get_pressure();
	LCD_clear();
	LCD_text("hPa");
	if(pressure/10000)
	{
		LCD_char(pressure/10000+0x30);
		LCD_char( (pressure%10000) / 1000 + 0x30);
		LCD_char( ( (pressure%10000) % 1000) / 100 + 0x30);
		LCD_char( ( ( (pressure%10000) % 1000) % 100) / 10 + 0x30);
		LCD_char('.');
		LCD_char( ( ( (pressure%10000) % 1000) % 100) % 10 + 0x30);
		LCD_text("hPa");
	}
	else
	{
		LCD_char(pressure/1000+0x30);
		LCD_char( (pressure%1000) / 100 + 0x30);
		LCD_char( ( (pressure%1000) % 100) / 10 + 0x30);
		LCD_char('.');
		LCD_char( ( (pressure%1000) % 100) % 10 + 0x30);
		LCD_text("hPa");
	}

}