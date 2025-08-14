#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{

	DDRD = 0xFF;
	PORTD = 0x00;

	DDRB = 0x00;
	PORTB = 0xFF;
	
	while(1)
	{
		if (PINB)
		{
			PIND = PINB;
		}
	}
	return 0;
}

