
#include <avr/io.h>
#define F_CPU 16000000UL
#define delay 50
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>
#include "stdio_setup.h"
#include <string.h>
#include "LCDSetup/lcd.h"
#include "LED/LEDOptions.h"
#include "LCD/LCDOptions.h"
#include "SERVO/Gardiner.h"
#include "MOTOR/SneMotor.h"
#define Column1 PC0
#define Column2 PC1
#define Column3 PC2
#define Column4 PC3
#define Row1 PC7
#define Row2 PC6
#define Row3 PC5
#define Row4 PC4
#define KeyPadColumns PORTC
#define KeyPadPullUp PORTC
#define KeyPadRows PINC
#define KeyPadRegister DDRC

void Init_Keypad(void);
int ColumnScan(void);
int ReadRows(void);
void DecodeKeypad(int,int);

int led = 0;

int main(void)
{
	UartInit();

	lcd_init(LCD_DISP_ON);
	
	lcd_clrscr();
	
	Init_Keypad();
	Init_Led();
	Init_Timer1();
	init_Timer3();
	init_ADC();
	int Column;
	int Row;
	
	
	
    while (1) 
    {
		Column = ColumnScan();
		_delay_ms(delay);
		Row = ReadRows();
		DecodeKeypad(Column, Row);
		
		LEDPicker();
		
		SneControl();
		
    }
}

void Init_Keypad()
{
	KeyPadRegister &= ~(1 << Row4 | 1 << Row3 | 1 << Row2 | 1 << Row1); // Sætter row lines til input
	KeyPadRegister |= (1 << Column1) | (1 << Column2) | (1 << Column3) | (1 << Column4); // Sætter column lines til output
	KeyPadPullUp |= (1 << Row4) | (1 << Row3) | (1 << Row2) | (1 << Row1); // Enabler pull up på input (rows)
	KeyPadColumns |= (1 << Column1) | (1 << Column2) | (1 << Column3) | (1 << Column4); // Sætter outport porte til logisk 1
	
}



int ColumnScan()
{
	static int columnCounter = 1;
	KeyPadColumns |= (1 << Column1) | (1 << Column2) | (1 << Column3) | (1 << Column4); //Sætter output pins til logisk 1
	
	if (columnCounter == 1)
	{
		KeyPadColumns &= ~(1 << Column1); //Sætter bit til logisk 0
		columnCounter++;
		return 1;
	}
	else if (columnCounter == 2)
	{
		KeyPadColumns &= ~(1 << Column2);
		columnCounter++;
		return 2;
	}
	else if (columnCounter == 3)
	{
		KeyPadColumns &= ~(1 << Column3);
		columnCounter++;
		return 3;
	}
	else if (columnCounter == 4)
	{
		KeyPadColumns &= ~(1 << Column4);
		columnCounter = 1;
		return 4;
	}
	
    return 0;
}

int ReadRows()
{
	
	
	if (~KeyPadRows & (1 << Row1)) // Tjekker om PC7 / Row1 er blevet 0 aka, knappen er trykket ned.
	{
		_delay_ms(10); // Venter 10 ms inden den tjekker igen, i tilfælde af kontakt krel.
		if (~KeyPadRows & (1 << Row1))
		{
			return 5;
		}
	}
	
	if (~KeyPadRows & (1 << Row2))
	{
		_delay_ms(10);
		if (~KeyPadRows & (1 << Row2))
		{
			return 6;
		}
	}
	
	if (~KeyPadRows & (1 << Row3))
	{
		_delay_ms(10);
		if (~KeyPadRows & (1 << Row3))
		{
			return 7;
		}
	}
	
	if (~KeyPadRows & (1 << Row4))
	{
		_delay_ms(10);
		if (~KeyPadRows & (1 << Row4))
		{
			return 8;
		}
	}
	
	return 0;

}

void DecodeKeypad(int column, int row)
{
	int key = column * 10 + row; 
	
	//Kolonnerne har numrene 1, 2, 3, 4 fra højre, og rækkerne har numrene 5 ,6 ,7 ,8 fra bunden
	//Key'en er en sammensætning af kolonne tallet og række tallet. eks kolonne 1 og række 7 giver key 17.
	
	switch (key)
	{
		case 48: // 1
		GlaedeligJul();	// Udskriver en jule hilsen på LCD displayet.
		break;
		case 47: // 4
		OCR1C = 500;	// Ruller gardiner for.
		break;
		case 46: // 7
		lcd_clrscr();
		lcd_puts("Knap \"7\"");
		break;
		case 45: // * 
		lcd_clrscr();
		lcd_puts("Knap \"*\"");
		break;
		case 38: // 2
		JingleBells();	// Udskriver teksten til jingle bells på LCD Displayet.
		break;
		case 37: // 5
		OCR1C = 2500;	// Ruller gardiner fra.
		break;
		case 36: // 8
		lcd_clrscr();
		lcd_puts("Knap \"8\"");
		break;
		case 35: // 0
		lcd_clrscr();
		lcd_puts("Knap \"0\"");
		break;
		case 28: // 3
		lcd_clrscr();
		lcd_puts("Knap \"3\"");
		break;
		case 27: // 6
		lcd_clrscr();
		lcd_puts("Knap \"6\"");
		break;
		case 26: // 9
		lcd_clrscr();
		lcd_puts("Knap \"9\"");
		break;
		case 25: // #
		lcd_clrscr();
		lcd_puts("Knap \"#\"");
		break;
		case 18: // A
		led = 3;
		break;
		case 17: // B
		led = 2;
		break;
		case 16: // C
		led = 1;
		break;
		case 15: // D
		led = 0;
		break;
		default:
		
		break;
	}
}

void LEDPicker()
{
	switch (led) // Baseret på en int der bliver sat i DecodeKeyboard(), bliver der valgt et lysshow.
	{
		case 0:
		TurnOffLed();
		break;
		case 1:
		TurnOnLed();
		break;
		case 2:
		Expand();
		break;
		case 3:
		Blinking();
		break;
		default:
		break;
	}
}

