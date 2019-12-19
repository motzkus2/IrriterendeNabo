/*
 * Gardiner.c
 *
 * Created: 17-12-2019 12:31:40
 *  Author: thom8865
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void Init_Timer1(){
	// Compare Output Mode: Phase Correct PWM Mode 17.9.4
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<COM1C1) ;					
	
	//Waveform Generation Mode: Mode 10 PWM Phase correct: WGM13 = 1, WGM11 (Table 17-2)
	TCCR1B |= (1<<WGM13);
	TCCR1A |= (1<<WGM11);
	
	// Clock Select Bit: clk/64 prescaling: CS = 011 : CS01 = 1, CS00 = 1
	TCCR1B |= (1<<CS11);		// datasheet 17.11.5
	
	DDRB |= (1<<PB7) | (1<<PB6) | (1<<PB5);
	
	//Set Top
	ICR1 = 20000;
}