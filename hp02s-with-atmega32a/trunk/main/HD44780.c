/*
 * hd44780.c
 *
 *  Created on:
 *	 Edited on: 02-10-2012
 *      Author: Daniel
 *
 *	All rights reserved.
 */

#include "HD44780.h"

//----opóŸnienie
void wait(char time)
{
unsigned char a, b; // zmnienne licznikowe
for( ; time > 0; --time) // ta pêtla zostanie wykonana x-razy
  for(b = 10; b > 0; --b) // a ta 10 razy
	for(a = 100; a > 0; --a) // natomiast ta 100 razy
	__asm("nop"); // dodatkowa instrukcja opóŸniaj¹ca o 1 cykl
	// razem to da opóŸnienie ok. x * 1ms
	// x od 0 do 255
}

//----inicjalizacja
void LCD_init(void)
{
	unsigned char init = 0;		//zmienna pomocnicza

	wait(15);
	CLR_E;
	CLR_RS;

	for(init =3 ; init > 0 ; init--)
		{
		SET_E;
		PORT_LCD |= (1 << LCDpin_4) | (1 << LCDpin_5);
		CLR_E;	//zapis gdy zbocze opadajace
		wait(5);
		//_delay_ms(5);
		}
	SET_E;
	PORT_LCD |= (tryb_tr << LCDpin_4) | (1 << LCDpin_5);

	CLR_E;
	wait(1);
	//_delay_ms(1);
	LCD_KOM(LCD_conf_4); // interfejs 4-bity, 2-linie, znak 5x7
	LCD_KOM(LCD_init1); // wy³¹cz LCD, kursor i miganie
	LCD_KOM(LCD_CLR); // czyœæ LCD
	LCD_KOM(LCD_init2); // bez przesuwania w prawo
	LCD_KOM(LCD_init3); // w³¹cz LCD, bez kursora i mrugania


}

//----czyszczenie ekranu
void LCD_clear(void)
{
	LCD_KOM(LCD_CLR); 	// czyœæ LCD
	LCD_local(0,0);		//ustaw kursor na poczatek
}

//----zapis danych
void LCD_write(unsigned char data)
{
	SET_E;
	if(tryb_tr)
	{
		PORT_LCD = data;
		CLR_E;
	}else
	{
		if(data & 0x10)
			PORT_LCD |= _BV(LCDpin_4);
		else
			PORT_LCD &= ~_BV(LCDpin_4);

		if(data & 0x20)
			PORT_LCD |= _BV(LCDpin_5);
		else
			PORT_LCD &= ~_BV(LCDpin_5);

		if(data & 0x40)
			PORT_LCD |= _BV(LCDpin_6);
		else
			PORT_LCD &= ~_BV(LCDpin_6);

		if(data & 0x80)
			PORT_LCD |= _BV(LCDpin_7);
		else
			PORT_LCD &= ~_BV(LCDpin_7);

		CLR_E;//zapis gdy zbocze opadaj¹ce;
		SET_E;

		if(data & 0x01)
			PORT_LCD |= _BV(LCDpin_4);
		else
			PORT_LCD &= ~_BV(LCDpin_4);

		if(data & 0x02)
			PORT_LCD |= _BV(LCDpin_5);
		else
			PORT_LCD &= ~_BV(LCDpin_5);

		if(data & 0x04)
			PORT_LCD |= _BV(LCDpin_6);
		else
			PORT_LCD &= ~_BV(LCDpin_6);

		if(data & 0x08)
			PORT_LCD |= _BV(LCDpin_7);
		else
			PORT_LCD &= ~_BV(LCDpin_7);

		CLR_E;//zapis gdy zbocze opadaj¹ce;

	}

	wait(1);
}

//----zapis komendy
void LCD_KOM(unsigned char command)
{
	CLR_RS;
	LCD_write(command);
}

//----zapis tekstu
void LCD_text(char *text)
{
	unsigned int i = 0;

	for(; text[i] != 0 ; i++)
	{
		if(text[i] == 47 && text[i+1] == 110) //skok do lini je¿eli /n
		{
			LCD_local(0,1);
			i++;
			i++;
		}

		LCD_char(text[i]);
	}
}

//----zmiana lokalizacji kursora
void LCD_local(unsigned char x, unsigned char y)	//y = 1 lub wiecej druga linia, x++ o kolumne dalej.
{
	LCD_KOM(0x80|((x)+(y*64)));
}

//----zapis 1 znaku
void LCD_char(unsigned char data)
{
	SET_RS;
	LCD_write(data);
}

//----zapis znakow PL i nie tylko
void LCD_PL(void);

//----wypisanie liczby ze zmiennej unsigned int
void LCD_numb(unsigned int number)
{
	LCD_char((number/10000)+0x30);
	LCD_char((number%10000)/1000+0x30);
	LCD_char(((number%10000)%1000)/100+0x30);
	LCD_char((((number%10000)%1000)%100)/10+0x30);
	LCD_char((((number%10000)%1000)%100)%10+0x30);
}
