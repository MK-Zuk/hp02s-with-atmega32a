/*
 * hp02s.h
 *
 *  Created on: 10-10-2012
 *	 Edited on: 10-10-2012
 *      Author: Daniel
 *
 *	All rights reserved.
 */

#ifndef HP02S_H_
#define HP02S_H_

//**********okreslenie podlaczenia MCLK i xCLR

#define PORT_xCLR PORTB
#define DDR_xCLR DDRB
#define PIN_xCLR PB0

#define PORT_MCLK PORTB
#define DDR_MCLK DDRB
#define PIN_MCLK PB1

//**********ustawienie odpowiednio MCL i xCLR

#define xCLR_out	(DDR_xCLR |= _BV(PIN_xCLR))
#define MCLK_out	(DDR_MCLK |= _BV(PIN_MCLK))

#define xCLR_on		(PORT_xCLR |= _BV(PIN_xCLR))
#define xCLR_off	(PORT_xCLR &= ~_BV(PIN_xCLR))

#define MCLK_on		(PORT_MCLK |= _BV(PIN_MCLK))
#define MCLK_off	(PORT_MCLK &= ~_BV(PIN_MCLK))

//**********deklaracje funkcji

void calibr_factor(void);
unsigned int read_value_D1(void);
unsigned int read_value_T1(void);
void init_inter(void);
void get_pressure(void);
void init(void);

#endif /* HP02S_H_ */
