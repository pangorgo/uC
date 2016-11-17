---
layout: post
title: uC -> Raspberry Pi - serial communication
---

Sending data from uC to Raspberry Pi using serial UART interface

## Serial interface

UART - Universal Asynchronous Receiver/Transmitter is a hardware device for for asynchronous serial communication. Asynchronous means that both end points are not synchronized by common clock source. Transmission speed (baud rate) is predefined and both endpoint should use the same. **This is reason why you shouldn't use internal uC oscilator, which is very imprecise (it deviation is up to to 10%).** Instead external crystal oscilator should be used which uncertainity is only 0.1%.

![UART](https://upload.wikimedia.org/wikipedia/commons/thumb/2/24/UART_timing_diagram.svg/1600px-UART_timing_diagram.svg.png)


## Atmega 328p

Controller expose serial interface on interfaces RXD/TXD
![](http://www.hobbytronics.co.uk/image/data/tutorial/arduino-hardcore/atmega328-arduino-pinout.jpg)


## Raspbery Pi

### Wiring

Raspberry PI unlike many usual PCs and laptops has built in UART device. Serial interface is exposed on GPIO PINS
![RPi GPIO](http://raspi.tv/wp-content/uploads/2014/07/Raspberry-Pi-GPIO-pinouts.png)

One have to remember that RPi serial ports are 3V, and to connect it to uC it has to be powered with the same voltage or converter should be used in the middle.

On schema below, programator wiring is not included.

![_config.yml]({{ site.baseurl }}/images/1_bb.jpg))

### uc Code

All code can be found here: https://github.com/pangorgo/uC/tree/master/helloworld_uart

Following code sends `ab\n` characters to serial every 1 second

**main.c**

```
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
```

**uart.c**

```
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

```

### RPI

```
Code Sample should be here
```
