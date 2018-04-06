/* Name: main.c
 * Author: <Steen Grøntved>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <util/delay.h>
#include "displays.h" 	
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>

volatile int Global_Time = 0;
volatile int t = 0;
//int i;
volatile int this = 0;
volatile int globsize = 0;
//volatile int write = 48;
volatile int val = 0;


void initialize(){
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRA = 0x00;
}



void rensinput() // renser input, så vi kan bruge det
{
	int i;
	for(i = 0; i < globsize; i++)
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
	int i;
	for(i = 0; i < 4; i++)
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
	PORTD = PORTD & 0b10000111;
	PORTD = PORTD | DISPLAYS[i];
	PORTC = PORTC & ((~ choices[i]) | 0b10000000);
	//Timere der tæller opad
	Global_Time++;
}


void Handles()
{



}






int main(void)
{

	initialize();

	while(1){ 

		//Udfør ingenting, vent på interrupts
		/*if(write == 48)
		{
			globsize = 4;
		}*/


		if (PINA & 1<<PA0){
			val += 1;

		} else {
			val -= 1;

		}

		//val += 1;
		int value = val;
		
		if (val >= 10000){
			val = 0;

		}
		if (val < 0){
			val = 9999;

		}





		char SoonSoonToBe[5];   //Display Values!!
		sprintf(SoonSoonToBe, "%d", value);

		SoonToBe = SoonSoonToBe;
		globsize = 4;//size(SoonToBe);
		

		display(t); //Gør klar til hvad der skal stå på display

		Light_It_Up(this); //Tænder rent faktisk lyset i displays

		if(Global_Time > 1.5*1000) //rykker bogstaver og tal på display efter tid
		{
			if(globsize>4) t++;
			Global_Time = 0;
		}

		//Går igennem alle mulige bogstaver/tal til der er blankt display, og starter igen.
		if(t > globsize+3)
		{
			t = 0;
		}


		//Tæller display op
		this++;
		if(this>=4)
		{
			this = 0;
		}
	}
	return 0;



	}






