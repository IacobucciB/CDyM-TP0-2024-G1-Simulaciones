#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdint.h>

#include "lcd.h"

int main(void)
{	
	LCDinit();
	_delay_ms(1);
	LCDclr();
	_delay_ms(1);
	LCDhome();
	_delay_ms(1);
		
	uint8_t msnj[] = "Hello World!";
	LCDstring(msnj, sizeof(msnj) - 1);
	
	while(1) 
	{
    }
}

