#ifndef _HD44780_H_
#define _HD44780_H_

#include <avr/io.h>

//---------- wstepna konfiguracja

#define tryb_tr 	0 		// 0 - tryb 4 bitowy, 1 - tryb 8 bitowy (wysylanie danych po 4 lub 8 bitow)
							//zmienic takze bit w definicji lcd_conf_4
//---------- konfiguracja pinow podlaczonych do wyswietlacza
//********** nalezy zmienic wedlug podlaczenia

#define PORT_E		PORTD
#define DDR_E		DDRD
#define PORT_RS		PORTD
#define DDR_RS		DDRD

#define PORT_LCD	PORTD
#define DDR_LCD		DDRD

#define LCDpin_rs	PD1
#define LCDpin_e	PD0

#define SET_RS		PORT_RS |= _BV(LCDpin_rs)		//ustawienie bitu E w LCD
#define CLR_RS		PORT_RS &= ~_BV(LCDpin_rs)		//wyzerowanie bitu w LCD

#define SET_E		PORT_E |= _BV(LCDpin_e)
#define CLR_E		PORT_E &= ~_BV(LCDpin_e)

#define LCDpin_0	PD0		//zapis w formacie PD0
#define LCDpin_1	PD1
#define LCDpin_2	PD2
#define LCDpin_3	PD3
#define LCDpin_4	PD4
#define LCDpin_5	PD5
#define LCDpin_6	PD6
#define LCDpin_7	PD7


//********** funkcje konfigurujace IO uC - nie zmieniac
#define LCD_D0		(1 << LCDpin_0)
#define LCD_D1		(1 << LCDpin_1)
#define LCD_D2		(1 << LCDpin_2)
#define LCD_D3		(1 << LCDpin_3)
#define LCD_D4		(1 << LCDpin_4)
#define LCD_D5		(1 << LCDpin_5)
#define LCD_D6		(1 << LCDpin_6)
#define LCD_D7		(1 << LCDpin_7)

//---------- definicje funkcji obslugi wyswietlacza

void LCD_init(void);
void LCD_clear(void);
void LCD_write(unsigned char data);
void LCD_KOM(unsigned char command);
void LCD_text(char *text);
void LCD_local(unsigned char x, unsigned char y);
void LCD_char(unsigned char data);
void LCD_PL(void);
void waite(unsigned char time);
void LCD_numb(unsigned int number);

//---------- komendy obslugujace wyswietlacz

#define LCD_CLR		0x01
#define LCD_HOME	0x02
#define LCD_conf_4	0x28 		// interfejs 4-bity, 2-linie, znak 5x7
#define LCD_init1  	0x08 		// wy³¹cz LCD, kursor i miganie
#define LCD_init2	0x06 		// bez przesuwania w prawo
#define LCD_init3	0x0C	 	// w³¹cz LCD, bez kursora i mrugania

#endif
