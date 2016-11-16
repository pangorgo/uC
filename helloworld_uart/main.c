#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>

#define FOSC 12000000
#define BAUD 9600

void main( void ) 
{
  DDRB |= (1 << PB0); //Data Direction Register B: writing a 1 to the bit enables output
  SerialInit(FOSC, BAUD, 8, 1, 0);
  while(1)
  {
    PORTB= 0b00000001; //turns on LED attached to port PB0
    _delay_ms(10000); //creates a 1-second delay
    PORTB= 0b00000000; //Turns off all B pins, including PB0
    _delay_ms(10000); //creates another 1-second delay
    SerialPrint("ab\n");
  }
  while(1)
  {
    SerialPrintChar(SerialRead());
  }
}
