#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#define PWM_PERIOD 100

#define PWM_OFF PORTB &= ~(1<<PORTB5)
#define PWM_ON PORTB |= (1<<PORTB5)

static uint8_t pwm_delta = 1;

void PWM_Soft_Update(uint16_t pwm_delta){
	static uint16_t PWM_Pos = 0;
	if(++PWM_Pos>=PWM_PERIOD){
		PWM_Pos = 0;
	}
	if(PWM_Pos<pwm_delta){
		PWM_ON;
	} else {
		PWM_OFF;
	}
}

ISR(TIMER0_COMPA_vect){
	// static uint16_t pwm_delta = 1;
	if(pwm_delta<70){
		pwm_delta++;
	}
	if(pwm_delta == 70){
		pwm_delta = 0;
	}	
	
	PWM_Soft_Update(pwm_delta);
}

int main(void)
{
	DDRB = 0xFF; //PBx as output
	TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00); // Fast PWM Non Inversor
	TCCR0B |= (1<<CS01); // Scaler 8
	OCR0A = 249; // Some value for edge
	TIMSK0 = (1<<OCIE0A); // Interruption
	sei(); // Enable Interruptions
	
	while(1) {

    }
}

