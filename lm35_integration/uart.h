
/*
 * uart.h
 *
 * Created: 25-03-2026 23:11:11
 *  Author: Sunil Thomas
 */ 

#ifndef UART_H_
#define UART_H_


#include <util/delay.h>
#include <stdint.h>
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>

void uart_init();
void uart_transmit(char data);
void uart_string(char *str);


#endif /* UART_H_ */