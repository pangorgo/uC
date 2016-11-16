#include <avr/io.h>
#include "uart.h"

//initialize serial interface
void SerialInit(unsigned long int fosc, unsigned int baud, short int bits, short int stopBits, short int parity)
{
  unsigned int ubrr = fosc/16/baud-1;

  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;

  UCSR0B = (1<<RXEN0)|(1<<TXEN0);

  switch(parity)
  {
    case 1:
      UCSR0C = (1<<UPM01);
      break;
    case 2:
      UCSR0C = (1<<UPM01)|(1<<UPM00);
      break;
  }

  switch(stopBits)
  {
    case 2:
      UCSR0C = (1<<USBS0);
      break;
  }

  switch(bits)
  {
    case 6:
      UCSR0C = (1<<UCSZ00);
      break;
    case 7:
      UCSR0C = (1<<UCSZ01);
      break;
    case 8:
      UCSR0C = (3<<UCSZ00);
      break;
  }
}

void SerialPrintChar(unsigned char data)
{
  while (!(UCSR0A&(1<<UDRE0)));
  UDR0 = data;
}

void SerialPrintRaw(short int bits)
{
  while (!(UCSR0A&(1<<UDRE0)));
  UDR0 = bits;
}


void SerialPrint(unsigned char *s)
{
  while(*s)
  {
    SerialPrintChar(*s);
    s++;
  }
}

unsigned char SerialRead(void)
{
  while (!(UCSR0A&(1<<RXC0)));
  return UDR0;
}
