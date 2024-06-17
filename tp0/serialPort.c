#include "SerialPort.h"

// ------ Definitions of Public Functions -------------------

// Serial Port Initialization

void SerialPort_Init(uint8_t config){
	// config = 0x33 ==> Configure UART 9600bps, 8-bit data, 1 stop @ F_CPU = 8MHz.
	// config = 0x25 ==> Configure UART 9600bps, 8-bit data, 1 stop @ F_CPU = 4MHz.
	UCSR0B = 0;
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	UBRR0H = (unsigned char)(config>>8);
	UBRR0L = (unsigned char)config;
}


// Transmitter Initialization

void SerialPort_TX_Enable(void){
	UCSR0B |= (1<<TXEN0);
}

void SerialPort_TX_Interrupt_Enable(void){
	UCSR0B |= (1<<UDRIE0);
	//UCSR0B |= (1<<TXCIE0); // TXC interrupt
}

void SerialPort_TX_Interrupt_Disable(void)
{
	UCSR0B &=~(1<<UDRIE0);
	//UCSR0B &= ~(1<<TXCIE0); // TXC interrupt
}


// Receiver Initialization

void SerialPort_RX_Enable(void){
	UCSR0B |= (1<<RXEN0);
}

void SerialPort_RX_Interrupt_Enable(void){
	UCSR0B |= (1<<RXCIE0);
}


// Transmission

// Wait until the TX buffer is free.
void SerialPort_Wait_For_TX_Buffer_Free(void){
	// Polling - Blocking until transmission is complete.
	while(!(UCSR0A & (1<<UDRE0)));
}

void SerialPort_Send_Data(char data){
	UDR0 = data;
}

void SerialPort_Send_String(char * msg){  // msg -> "Hello how are you today?" 20 ASCII+end of string, takes 20ms
	uint8_t i = 0;
	//'\0' = 0x00
	while(msg[i]){ // *(msg+i)
		SerialPort_Wait_For_TX_Buffer_Free(); // 9600bps 8N1 format, 10 bits, 10.T bit=10/9600=1ms
		SerialPort_Send_Data(msg[i]);
		i++;
	}
}


// Reception

// Wait until the RX buffer is full.
void SerialPort_Wait_Until_New_Data(void){
	// Polling - Blocking, may last indefinitely!
	while(!(UCSR0A & (1<<RXC0)));
}


char SerialPort_Recive_Data(void){
	return UDR0;
}


void SerialPort_Send_uint8_t(uint8_t num){
	
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_Data('0'+num/100);
	
	num-=100;
	
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_Data('0'+num/10);
	
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_Data('0'+ num%10);
}

/***************************************************************
This function writes a integer type value to UART
Arguments:
1)int val	: Value to print
2)unsigned int field_length :total length of field in which the value is printed
must be between 1-5 if it is -1 the field length is no of digits in the val
****************************************************************/
void SerialPort_send_int16_t(int val,unsigned int field_length)
{
	char str[5]={0,0,0,0,0};
	int i=4,j=0;
	while(val)
	{
		str[i]=val%10;
		val=val/10;
		i--;
	}
	if(field_length==-1)
	while(str[j]==0) j++;
	else
	j=5-field_length;

	if(val<0) {
		SerialPort_Wait_For_TX_Buffer_Free();
		SerialPort_Send_Data('-');
	}
	for(i=j;i<5;i++)
	{
		SerialPort_Wait_For_TX_Buffer_Free();
		SerialPort_Send_Data('0'+str[i]);
	}
}

