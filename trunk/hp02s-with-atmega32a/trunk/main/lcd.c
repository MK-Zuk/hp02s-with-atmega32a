#include "lcd.h"

const char znaki[64] = {
	32 , 32 , 14 ,  1 , 15 , 17 , 15 ,  2,	// ¹
	 2 ,  4 , 14 , 16 , 16 , 16 , 14 , 32,	// æ
	32 , 32 , 14 , 17 , 30 , 16 , 14 ,  2,	// ê
	12 ,  4 ,  6 , 12 ,  4 ,  4 , 14 , 32,	// ³
	// 2 ,  4 , 22 , 25 , 17 , 17 , 17 , 32,	// ñ
	 7 ,  5 ,  7 ,  0 ,  0 ,  0 ,  0 ,  0,	// 4-stopnie
	//2 ,  4 , 14 , 17 , 17 , 17 , 14 , 32,  // ó
	 4 , 14 , 21 ,  4 ,  4 ,  4 ,  4 ,  4,  // 5-strza³ka góra
	// 2 ,  4 , 14 , 16 , 14 ,  1 , 30 , 32,	// œ
	 4 ,  4 ,  4 ,  4 ,  4 , 21 , 14 ,  4,	// 6-strza³ka dó³
	//4 , 32 , 31 ,  2 ,  4 ,  8 , 31 , 32	// ¿
	 4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4	// 7-kreska
	};
	
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

/*unsigned char time1, time2, th,hu,dec;
th = ((0.001*F_CPU-5)/5) / 1000;
hu = ((unsigned char)((0.001*F_CPU-5)/5) % 1000) / 100;
dec = ((unsigned char)((0.001*F_CPU-5)/5) % 1000) % 100;

	do
	{
		for(;th > 0;th --)
		{
			for(time1 = 10 ; time1>0; time1--)
				for(time2 = 100 ; time2 > 0 ; time2--)
					{
					asm("nop");
					}
		}
		for(;hu > 0; hu--)
		{
			for(time2 = 100 ; time2 > 0 ; time2--)
				{
				asm("nop");
				}
		}
		for(;dec > 0; dec--)
		{
		asm("nop");				
		}
	}while(--time);	//jeden obieg = 1ms*/


}

//zapis bajtu do lcd
void LCD_WRITE(unsigned char bajt)
{
SET_E;
LCD_PB = ((LCD_PB & 0x0F) | (bajt & 0xF0)); //najstarsze bity sa przesylane do LCD
/*
bity 1,2,3 portu b sa podpiete do lcd i nie mozna ich zmieniac
LCD_PB & 0x0F powoduje ¿e 4 m³odsze bity pozostaja takie jakie byly
a zeruja sie 4 starsze bity. Podobnie ni¿ej
*/
CLR_E;//zapis gdy zbocze opadaj¹ce;
SET_E;
LCD_PB = ((LCD_PB & 0x0F) | ((bajt & 0x0F) << 4)); //4 najmlodsze sa przesylane do LCD (najpierw sa przesuniete o 4 w lewo)
CLR_E;//zapis gdy zbocze opadaj¹ce;
wait(1);
}

void LCD_WRITE_kod(unsigned char nr_kodu)
{
SET_RS;
SET_E;
LCD_PB = ((LCD_PB & 0x0F) | (nr_kodu & 0xF0)); //najstarsze bity sa przesylane do LCD
/*
bity 1,2,3 portu b sa podpiete do lcd i nie mozna ich zmieniac
LCD_PB & 0x0F powoduje ¿e 4 m³odsze bity pozostaja takie jakie byly
a zeruja sie 4 starsze bity. Podobnie ni¿ej
*/
CLR_E;//zapis gdy zbocze opadaj¹ce;
SET_E;
LCD_PB = ((LCD_PB & 0x0F) | ((nr_kodu & 0x0F) << 4)); //4 najmlodsze sa przesylane do LCD (najpierw sa przesuniete o 4 w lewo)
CLR_E;//zapis gdy zbocze opadaj¹ce;
wait(1);
}

//zapis komendy do lcd
void LCD_WRITE_COM(unsigned char command) // command - adres
{
CLR_RS;
LCD_WRITE(command);
}

//zapis danych do lcd
void LCD_WRITE_DATE(unsigned char date)		//pojedyncze znaki umieszczamy w ' ' np. 'd'
{
SET_RS;
LCD_WRITE(date);
}



void LCD_TEXT_LOCAL(unsigned char x, unsigned char y)	//y = 1 lub wiecej druga linia, x++ o kolumne dalej.
{
LCD_WRITE_COM(0x80|((x)+(y*64)));
}

void LCD_WRITE_TEXT(char *text)	//tekst umieszczamy w " " np. "tekst"
{
unsigned char i =0;

	for(; text[i]!=0 ; i++)
	{
		if(text[i] == 47 && text[i+1] == 110) //skok do lini je¿eli /n
		{
		LCD_TEXT_LOCAL(0,1);
		i++;
		i++;
		}
	LCD_WRITE_DATE(text[i]);
	}
	/*
	wskazujemy na dana i zwiekszamy wskaznik.
	*/
}

//inicjalizacja LCD
void LCD_INIT(void)
{
unsigned char init;


wait(15);
CLR_E;
CLR_RS;


for(init =3 ; init > 0 ; init--)
	{
	SET_E;
	LCD_PB &= 0x3F;
	CLR_E;	//zapis gdy zbocze opadajace	
	wait(5);
	//_delay_ms(5);
	}
SET_E;
LCD_PB &= 0x2F;

CLR_E;
wait(1);
//_delay_ms(1);
LCD_WRITE_COM(0x28); // interfejs 4-bity, 2-linie, znak 5x7
LCD_WRITE_COM(0x08); // wy³¹cz LCD, kursor i miganie
LCD_WRITE_COM(0x01); // czyœæ LCD
LCD_WRITE_COM(0x06); // bez przesuwania w prawo
LCD_WRITE_COM(0x0C); // w³¹cz LCD, bez kursora i mrugania


}
 
void LCD_clear(void)
{
  LCD_WRITE_COM(0x01);	// wyczyœæ LCD
 // wait(10);	// czekaj chwilê
  LCD_TEXT_LOCAL(0,0);		// ustaw kursor na pocz¹tek
}

void LCD_PL(void)
{
  unsigned char l;
  unsigned char cgram = 64;		//ustaw adres CGRAM na 0
  for(l=0;l<64;l++)
	{
	LCD_WRITE_COM(cgram);
    LCD_WRITE_DATE(znaki[l]);	//wpisuj kolejne definicje do CGRAM
	cgram++;
	}
}