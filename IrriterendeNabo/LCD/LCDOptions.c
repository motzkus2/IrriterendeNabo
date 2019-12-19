/*
 * LCDOptions.c
 *
 * Created: 17-12-2019 10:50:41
 *  Author: thom8865
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#define delay 50
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>
#include "stdio_setup.h"
#include <string.h>

void GlaedeligJul()
{
			lcd_clrscr();
			
			char s1[] = "Glaedelig Jul\n";
			char s2[] = "Og Godt Nytaar";
			
			int index = 0;
			
			for (index = 0; index < strlen(s1); index++) // Udskriver strengen karakter for karakter så det ser mere flydende ud.
			{
				lcd_putc(s1[index]);
				_delay_ms(100);
			}
			
			for (index = 0; index < strlen(s2); index++)
			{
				lcd_putc(s2[index]);
				_delay_ms(100);
			}
}

void JingleBells()
{
	lcd_clrscr();
	
	char s1[] = "Jingle Bells\n";
	char s2[] = "Jingle All\n";
	char s3[] = "The Way";
	char s4[] = "Oh What Fun\n";
	char s5[] = "It is to run";
	char s6[] = "In a One-Horse\n";
	char s7[] = "Open Sleigh! ";
	char s8[] = "Hey!";
	
	
	int index = 0;
	
	for (index = 0; index < strlen(s1); index++)
	{
		lcd_putc(s1[index]);
		_delay_ms(100);
	}
	
	_delay_ms(500);
	
	for (index = 0; index < strlen(s1); index++)
	{
		lcd_putc(s1[index]);
		_delay_ms(100);
	}
	
	_delay_ms(500);
	lcd_clrscr();
	
	for (index = 0; index < strlen(s2); index++)
	{
		lcd_putc(s2[index]);
		_delay_ms(100);
	}
	
	for (index = 0; index < strlen(s3); index++)
	{
		lcd_putc(s3[index]);
		_delay_ms(100);
	}
	_delay_ms(500);
	lcd_clrscr();
	
	for (index = 0; index < strlen(s4); index++)
	{
		lcd_putc(s4[index]);
		_delay_ms(100);
	}
	
	_delay_ms(500);
	
	for (index = 0; index < strlen(s5); index++)
	{
		lcd_putc(s5[index]);
		_delay_ms(100);
	}
	
	_delay_ms(500);
	lcd_clrscr();
	
	for (index = 0; index < strlen(s6); index++)
	{
		lcd_putc(s6[index]);
		_delay_ms(100);
	}
	
	for (index = 0; index < strlen(s7); index++)
	{
		lcd_putc(s7[index]);
		_delay_ms(100);
	}
	
	_delay_ms(500);
	lcd_puts(s8);
}