#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;
	while(1) {
		PORTB = 0xFF;
		_delay_ms(500);
		PORTB = 0x00;
		_delay_ms(500);
    }
}

