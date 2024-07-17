/* library headers */
#include <avr/io.h> // AVR microcontroller registers
#define F_CPU 16000000UL // Define CPU clock frequency as 16 MHz
#include <util/delay.h> // Include delay functions

int main(void)
{
	// Configure PINC0 (PC0) as input
	DDRC &= ~(1 << PINC0);
	// Enable pull-up resistor on PINC0 (PC0)
	PORTC |= (1 << PINC0);
	// Configure all PORTB pins as outputs
	DDRB = 0xFF;

	while (1) { // Infinite loop
		// Check if PINC0 (PC0) is high
		if (PINC & (1 << PINC0)) {
			// If PC0 is high, set PORTB to 0b10101010
			PORTB = 0b10101010;
			_delay_ms(100); // Delay for 10 milliseconds
			// Set PORTB to 0x00 (turn off all pins)
			PORTB = 0x00;
			_delay_ms(100); // Delay for 10 milliseconds
			} else {
			// If PC0 is low, set PORTB to 0b01010101
			PORTB = 0b01010101;
			_delay_ms(100); // Delay for 10 milliseconds
			// Set PORTB to 0x00 (turn off all pins)
			PORTB = 0x00;
			_delay_ms(100); // Delay for 10 milliseconds
		}
	}

	return 0; // Return 0 (never reached in this case)
}


