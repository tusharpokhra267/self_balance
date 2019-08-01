/*
 * GccApplication4.c
 *
 * Created: 31-07-2019 22:37:49
 * Author : TUSHAR
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>



#include "mpu6050/mpu6050.h"



#define F_CPU 16000000UL

#include <util/delay.h>

#define baudrate 9600

#define FOSC 8000000UL

#define UBRR 51


void uart_init (void)

{

	UBRR0H = (UBRR >> 8);

	UBRR0L = UBRR;

	UCSR0C |=(1<<UCSZ00)|(1<<UCSZ01);

	UCSR0B |=(1<<RXEN0)|(1<<TXEN0);

	

}



void uart_transmit (char data)

{

	while (!( UCSR0A & (1<<UDRE0)));

	UDR0 = data;

	

}



char uart_receive (void)

{

	while (!( UCSR0A & (1<<RXC0)));

	return UDR0;

}



void usart_transmit_string(char *str)

{



	while(*str > 0)

	{

		

		uart_transmit(*str);

		str++;

	}

}







int main(void)

{

	mpu6050_init();

	uart_init();

	

	//int intdata=179;

	char data[10] ;

	int16_t ax = 0;

	int16_t ay = 0;

	int16_t az = 0;

	int16_t gx = 0;

	int16_t gy = 0;

	int16_t gz = 0;

	

	while (1)

	{

		mpu6050_getRawData(&ax, &ay, &az, &gx, &gy, &gz);

		itoa(ax,data,10);

		usart_transmit_string(data);

		_delay_ms(50);

	}

}
