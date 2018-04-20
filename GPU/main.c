/* Name: main.c for LYD
 * Author: Christian Mikkelstrup
 * Copyright: Use of code has to be accepted through the author
 * License: Use for inspiration, and use common sense
 */

#include <avr/io.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "displays.h"
#include <avr/interrupt.h>

int globsize = 4;
int Global_Time = 0;

void initialize(){
	DDRC = 0xFF; //alle GPIO på port D sat til outputs
	DDRD = 0xFF;
	DDRA = 0xFF;
	DDRB = 0xFF;
}

void rensinput() // renser input, så vi kan bruge det
{
	for(int i = 0; i < globsize; i++)
	{
		//mellemrum bliver oversat
		if(SoonToBe[i] == ' ')
		{
			SoonToBe[i] = 0b00000000;
		}
		//bindestrej bliver oversat
		if(SoonToBe[i] == '@')
		{
			SoonToBe[i] = 0b01000000;
		}
		//indsæt flere her hvis behov:
		if(SoonToBe[i] == ',')
		{
			SoonToBe[i] = 0b00010000;
		}
	}
}

int givemechar(char tegn) //Brugt i forbindelse med display
{
	if(tegn == 44){ return 16; }
	if(tegn<64)
	{
		return NUMBERS[tegn-48];
	}
	if(tegn==64) return 64;
	return ALPHABET[tegn-65];
}

void display(int t) //Oversættelse fra hvad man skal læse til hvad der står på displayet
{
	//løkker der går gennem de fire cifre på displayet
	for(int i = 0; i < 4; i++)
	{
		//sætter dette ciffer til at være hvad der står i variablen
		//Så at det ser ud somom at det bevæger sig.
		char local = SoonToBe[t+i];
		if(t+i > globsize+3)
		{
			char local = SoonToBe[t-globsize+i-4];
			choices[i] = givemechar(local);

		}
		else if(local <= 43 || local >= 100)
		{
			choices[i] = 0b00000000;
		}
		else
		{
			char local = SoonToBe[t+i];
			choices[i] = givemechar(local);
		}
	}
}

void Light_It_Up(int i)
{
	rensinput(); //2*globsize
	PORTC = PORTC | 0b01111111;
	PORTD = PORTD & 0b11100001;
	PORTD = PORTD | DISPLAYS[i];
	PORTC = PORTC & ((~ choices[i]) | 0b10000000);
	//Timere der tæller opad
	Global_Time++;
}

int size(char Input[])
{
	int size=0;
	for(int i=0;i<100;i++)
	{
		char tegn = Input[i];
		if(tegn>0)
		{
			size++;
		}
		else
		{
			return size;
		}
	}
	return 0;
}

int main(void)
{
	initialize();

	while(1)
	{
		PORTD = 0b11111111;
		//PORTB = 0xFF;
		//PORTC = 0xFF;
		//PORTA = 0xFF;
	}
	return 0;
}
