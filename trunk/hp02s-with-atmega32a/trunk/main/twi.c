/*
Biblioteka do obs�ugi sprz�towego TWI - I2C.
Stworzona na podstawie mikrokontrolera Atmega8 
i jego noty katalogowej.

Design by danielo$		

TWSR - rejestr statusu twi
TWDR - dane TWI
TWCR - rejestr kontrolny twi

*/
//==============================

#include "twi.h"

//==============================
//	polecenie startu 
//==============================

void twi_start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);		//wys�anie polecenia start
	while (!(TWCR & (1<<TWINT)));				//czeka na ustawienie TWINT
												//oznacza to prawid�owe wys�anie STARTU
	TWCR &= 0b01011111;							//programowe wyzerowanie TWSTA

}

//==============================
//	polecenie stopu
//==============================

void twi_stop(void)
{
	TWCR |= 0b10010100;		//wys�anie m.inn. polecenia stop,
			//przerwanie	//aktywacja twi
}

//==============================
//polecenie odebrania danych
//acknowledge = 1 -> ack (potwierdzenie)
//acknowledge = 0 -> no_ack (brak potwierdzenia)
//==============================

unsigned char twi_read(unsigned char acknowledge)
{
  TWCR |= (1<<TWINT)|(acknowledge<<TWEA)|(1<<TWEN);

  while (!(TWCR & (1<<TWINT)));
  if (((TWSR & 0xF8) != 0x50) && ((TWSR & 0xF8) != 0x58)) //w twsr kody 50 i 58 odpowiedzialne 
    {													//s� za ack lub no_ack
      return 1; // je�eli wyst�pi� error z ack, to zwr�� error
    };

  return TWDR; // zwr�� dane z TWI

}

//==============================
//polecenie wys�ania danych
//==============================

void twi_write(unsigned char date)
{
	TWDR = date;
	TWCR |= (0<<TWINT);
	while(!(TWCR & (1<<TWINT)));
}
