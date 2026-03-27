/*
 * uart.c
 *
 * Created: 25-03-2026 23:08:20
 *  Author: Sunil Thomas
 */ 


#include "uart.h"
#define F_CPU 16000000UL


// uart for string

void uart_init()
{
	//1 baud rate for 9600
	UBRR0H = 0;
	UBRR0L = 103;
	//2.enabling the transmitting and receiving
	UCSR0B |=((1<<RXEN0) | (1<<TXEN0));
	//3. data frame configuration - 8 bit
	UCSR0B &=~(1<<UCSZ02);
	UCSR0C|=((1<<UCSZ01)|(1<<UCSZ00));
	//4. parity select
	UCSR0C &=~((1<<UPM01)|(1<<UPM00));
	//5 stop bit select-> 1or 2
	UCSR0C &=~(1<<USBS0);
}
//uart transmit function
void uart_transmit(char data)
{
	//waiting until the buffer is ready
	while (!(UCSR0A & (1<<UDRE0))); //feeding the data to buffer
	UDR0= data;
}
// to print string
void uart_string(char *str)
{
	while(*str)
	{
		uart_transmit(*str);
		str++;
	}
}




