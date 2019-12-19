/*
 * SneMotor.c
 *
 * Created: 18-12-2019 11:17:33
 *  Author: thom8865
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define RGB_R OCR3C
#define RGB_G OCR3B
#define MOTOR_SPEED OCR3A

void init_Timer3()
{
	// Compare Output Mode: Fast PWM Mode: Clear OC0A on Compare Match, set OC0A at BOTTOM, non-inverting mode 
	TCCR3A |= (1<<COM3A1) | (1<<COM3B1) | (1<<COM3C1) ;					// datasheet 17.11.2
	
	//Waveform Generation Mode: Mode 5 Fast PWM: WGM0 = 1, WGM2 = 1 (Table 17-2)
	TCCR3A |= (1<<WGM30);
	TCCR3B |= (1<<WGM32);
	
	// Clock Select Bit: clk/64 prescaling: CS = 011 : CS01 = 1, CS00 = 1 (Table 17-6), frekv. = 980Hz
	TCCR3B |= (1<<CS31) | (1<<CS30);		// datasheet 17.11.6
	
	DDRE |= (1<<PE3) | (1<<PE4) | (1<<PE5);
}

void init_ADC()
{
	ADMUX |= (1 << REFS0);	// 5V supply used for ADC reference,  datasheet 26.8.1
	DIDR2 |= (1 << ADC8D);	// disable digital input on ADC8 pin, datasheet 26.8.7
	// enable ADC, start ADC, ADC clock = 16MHz / 128 = 125kHz, datasheet 26.8.3
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRB |= (1 << MUX5); // Select ADC8 
}

void SneControl()
{
	float ADC_data;
	float temp;
	float tempK;
	unsigned int tempC;
	
	if (!(ADCSRA & (1 << ADSC)))
	{												// check if ADC conversion is complete
		ADC_data = ADC;								// get the ADC value, datasheet 28.9.3
		
		temp = log(10000.0 * (1024.0 / ADC_data -1));
		tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp)) * temp);
		tempC = tempK - 273.15;

		ADCSRA |= (1 << ADSC);						// start the next ADC conversion
	}
	
	if (tempC < 30) // Skal simulere at en snekanon begynder at skyde sne hvis der er minus grader.
	{				// Men da jeg ikke kan simulere minus grader har jeg ændret det til at den skyder sne når 
					// når det er over 30 grader, som jeg kan vise med ved at sætte fingrene på NTC'en.
		
		MOTOR_SPEED = 0;
		RGB_G = 0;
		RGB_R = 255;
	}
	else if (tempC > 30)
	{
		MOTOR_SPEED = 255;
		RGB_G = 255;
		RGB_R = 0;
	}
	
}