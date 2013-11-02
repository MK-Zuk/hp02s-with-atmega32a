/*
Biblioteka do obs�ugi sprz�towego TWI - I2C.
Stworzona na podstawie mikrokontrolera Atmega8 
i jego noty katalogowej.

Design by danielo$
*/

#include <avr/io.h>

//je�eli jest ju� do��czony to nie do��czaj
#ifndef _TWI_ 
#define _TWI_ 

void twi_start(void);
void twi_stop(void);
unsigned char twi_read(unsigned char acknowledge);
void twi_write(unsigned char date);

#endif
