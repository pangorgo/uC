#define F_CPU 12000000 //ustawienie oscylatora na 1MHz
#include <avr/io.h> //dołączenie podstawowej biblioteki
#include <avr/interrupt.h> //dołączenie biblioteki z przerwaniami
#include <util/delay.h> //dołączenie biblioteki z opóźnieniami

void main( void )
{
  DDRB |= (1 << PB0); //Data Direction Register B: Set B0 as output
  DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
  // PD2 (PCINT0 pin) is now an input

  PORTD |= (1 << PORTD2);    // turn On the Pull-up
  // PD2 is now an input with pull-up enabled
  
EICRA |= 1<<ISC01; //konfiguracja przerwania INT0
  EIMSK |= 1<<INT0; //włączenie przerwania INT0

  sei(); //turn interrupts ON
  while(1){}
}


ISR(INT0_vect) //początek funkcji obsługi przerwania
{
  PORTB= 0b00000001; //turns on LED attached to port PB0
  _delay_ms(100); //creates a 1-second delay
  PORTB= 0b00000000; //Turns off all B pins, including PB0
}
