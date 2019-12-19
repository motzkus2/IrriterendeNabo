/*
 * LEDOptions.c
 *
 * Created: 17-12-2019 10:31:10
 *  Author: thom8865
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#define delay 50
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>


void Expand()
{
	PORTA = 0b00000001;
	_delay_ms(100);
	PORTA = 0b00000011;
	_delay_ms(100);
	PORTA = 0b00000111;
	_delay_ms(100);
	PORTA = 0b00001111;
	_delay_ms(100);
	PORTA = 0b00011111;
	_delay_ms(100);
	PORTA = 0b00111111;
	_delay_ms(100);
	PORTA = 0b00111110;
	_delay_ms(100);
	PORTA = 0b00111100;
	_delay_ms(100);
	PORTA = 0b00111000;
	_delay_ms(100);
	PORTA = 0b00110000;
	_delay_ms(100);
	PORTA = 0b00100000;
	_delay_ms(100);
	PORTA = 0b00000000;
	_delay_ms(100);
	PORTA = 0b00100000;
	_delay_ms(100);
	PORTA = 0b00110000;
	_delay_ms(100);
	PORTA = 0b00111000;
	_delay_ms(100);
	PORTA = 0b00111100;
	_delay_ms(100);
	PORTA = 0b00111110;
	_delay_ms(100);
	PORTA = 0b00111111;
	_delay_ms(100);
	PORTA = 0b00011111;
	_delay_ms(100);
	PORTA = 0b00001111;
	_delay_ms(100);
	PORTA = 0b00000111;
	_delay_ms(100);
	PORTA = 0b00000011;
	_delay_ms(100);
}

void Blinking()
{
	
	PORTA = 0b10101010;
	_delay_ms(200);
	PORTA = ~PORTA;
	_delay_ms(200);
	
}

void TurnOnLed()
{
	PORTA = 0b00111111;

}

void TurnOffLed()
{
	PORTA = 0x00;
}

void Init_Led()
{
	DDRA |= (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3) | (1 << DDA4) | (1 << DDA5) | (1 << DDA6) | (1 << DDA7);
	
}
