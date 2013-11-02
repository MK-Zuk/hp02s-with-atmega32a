#include <avr/io.h>

#ifndef _LCD_ 
#define _LCD_

//
#define LCD_PB  PORTD
#define LCD_DB	DDRD

#define LCD_P_ER	PORTD
#define LCD_D_ER	DDRD

#define E  0			//numer pinu do którego jest pod³¹czony E
#define RS  1			//numer pinu do którego jest pod³¹czony RS

//E
//#define SET_OUT_E	LCD_DB |= _BV(E)
#define SET_E   LCD_P_ER |= _BV(E)	//ustawienie bitu E w LCD
#define CLR_E   LCD_P_ER &= ~_BV(E)	//wyzerowanie bitu w LCD
 
//RS
//#define SET_OUT_RS	LCD_DB |= _BV(RS)
#define SET_RS  LCD_P_ER |= _BV(RS)
#define CLR_RS  LCD_P_ER &= ~_BV(RS)

void LCD_PL(void);
void LCD_clear(void);
void LCD_INIT(void);
void LCD_WRITE_TEXT(char *text)	;
void LCD_TEXT_LOCAL(unsigned char x, unsigned char y);
void LCD_WRITE_DATE(unsigned char date)	;
void LCD_WRITE_COM(unsigned char command);
void LCD_WRITE_kod(unsigned char nr_kodu);
void LCD_WRITE(unsigned char bajt);
void wait(char time);

#endif 
