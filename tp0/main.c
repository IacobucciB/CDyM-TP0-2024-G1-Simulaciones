#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

/*
ERROR:
PINB6 is not a general purpose I/O pin, it cannot be controlled
It is used for the XTAL input of the external oscillator
*/

int main(void)
{
	DDRC &= ~(1 << PINC0); // clear bit 0 of DDRB, DDRC0 is input
	PORTC |= (1 << PINC0); // set bit 0 of PORTC, internal PULL-UP
	while(1)
	{
		if (PINC & (1 << PINC0)) // if PINC0 is 1
		{
			PORTB = 0b00001111;
			_delay_ms(10);
			PORTB = 0x00;
			_delay_ms(10);
		}
		else
		{
			PORTB = 0b11110000;
			_delay_ms(10);
			PORTB = 0x00;
			_delay_ms(10);
		}

	}
	return 0;
}

