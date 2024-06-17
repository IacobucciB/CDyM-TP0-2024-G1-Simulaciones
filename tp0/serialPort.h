#ifndef SERIALPORT_H_
#define SERIALPORT_H_

// ------------------- Includes ----------------------------

// Micro controller Header File
#include <avr/io.h>

// Micro controller Interrupts
#include <avr/interrupt.h>

// -------- Prototypes of Public Functions ---------------

// Serial Port Initialization
void SerialPort_Init(uint8_t);

// Transmitter Initialization
void SerialPort_TX_Enable(void);
void SerialPort_TX_Interrupt_Enable(void);
void SerialPort_TX_Interrupt_Disable(void);

// Receiver Initialization
void SerialPort_RX_Enable(void);
void SerialPort_RX_Interrupt_Enable(void);

// Transmission
void SerialPort_Wait_For_TX_Buffer_Free(void);    // Polling - Blocking until transmission is complete.
void SerialPort_Send_Data(char);
void SerialPort_Send_String(char *);
void SerialPort_Send_uint8_t(uint8_t);
void SerialPort_Send_int16_t(int val, unsigned int field_length);

// Reception
void SerialPort_Wait_Until_New_Data(void);    // Polling - Blocking, may last indefinitely!
char SerialPort_Receive_Data(void);

#endif /* SERIALPORT_H_ */
