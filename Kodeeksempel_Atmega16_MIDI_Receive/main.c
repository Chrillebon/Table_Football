/* Name: main.c
 * Author: <Steen Grøntved>
 * Copyright: <insert your copyright message here>
 * License: <insert  your license reference here>
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
int tal;
int sendstat = 0;
int laststat = 0;
int newvalue;
int handle[5] = {99, 99, 99, 99, 99};



void initialize(){
	DDRC = 0xFF;
	DDRD = 0b11111010;
	DDRA = 0x00;
	DDRB = 0x00;
	sei();
}

void timer0_init()
{
    // set up timer with prescaler = 1024
    TCCR0 |= (1 << CS02)|(1 << CS00);

    // initialize counter
    TCNT0 = 0;
}


void rensinput() // renser input, så vi kan bruge det
{
	int i, val;
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
		val = SoonToBe[i];
		if(val > 57)
		{
			SoonToBe[i] = 0x00;
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
	/*if(tegn <= 57 && tegn >= 48)
	{
		return NUMBERS[tegn-48];
	}
	return 0;*/
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

void handles()
{
	int temp = read();
	sendstat = status();
	if(laststat == sendstat)
	{
		handle[sendstat] = temp;
	}
	laststat = sendstat;
}

int read()
{
	int res = 0, t = 1;
	for(int i=0;i<8;i++)
	{
		res += (PINA & t);
		t *= 2;
	}
	return res;
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

int givemevalues(int t){
	if(t == 00){
		PORTD |= 0b00000000;
		for(int i=0;i<1000;i++){}

	}

	else if(t == 01){
		PORTD |= 0b00000001;
		for(int i=0;i<1000;i++){}
	}

	else if(t == 10){
		PORTD |= 0b00000010;
		for(int i=0;i<1000;i++){}
	}

	else if(t == 11){
		PORTD |= 0b00000011;
		for(int i=0;i<1000;i++){}
	}
	return read();
}

int status()
{
	int vala = (PIND & 1), valb = (PIND & 4);
	if(!vala && !valb) //Status: 0,0
	{
		return 0;
	}
	else if(vala && !valb) //Status: 1,0
	{
		return 1;
	}
	else if(vala && valb) //Status: 1,1
	{
		return 2;
	}
	else if(!vala && valb) //Status: 0,1
	{
		return 3;
	}
	return 4; //Burde aldrig komme herned...
}


int main(void)
{

	initialize();
	timer0_init();
	int value = 0;
	/*p1speedold = p1speed;
	p1speed = givemevalues(10);
	p1placeold = p1place;
	p1place = givemevalues(01);
	p2speedold = p2speed;
	p2speed = givemevalues(11);
	p2placeold = p2place;
	p2place = givemevalues(00);*/


	while(1){

		//Udfør ingenting, vent på interrupts
		/*if(write == 48)
		{
			globsize = 4;
		}*/


		/*if (PINA & 1<<PA0){
			val += 1;

		} else {
			val -= 1;

		}*/

		//val += 1;
		/*	p1speedold = p1speed;
		p1speed = givemevalues(10);
		p1placeold = p1place;
		p1place = givemevalues(01);
		p2speedold = p2speed;
		p2speed = givemevalues(11);
		p2placeold = p2place;
		p2place = givemevalues(00);*/


		/*if (p1speed != p1speedold){
			tal = 10;
		}
		if (p2speed != p2speedold){
			tal = 11;
		}
		if (p1place != p1placeold){
			tal = 01;
		}
		if (p2place != p2placeold){
			tal = 00;
		}*/

	/*	tal = 11;//01//10//11
		if (p2speed != p2speedold){
			tal = 10;
		}*//*else{
			tal = 11;
		}*/
		/*if (givemevalues(1)!=p1place){
			tal = 1;
		}
		if (givemevalues(10)!=p1speed){
			tal = 10;
		}
		if (givemevalues(11)!=p2speed){
			tal = 11;
		}
		if (givemevalues(0)!=p2place){
			tal = 0;
		}*/
		if (val >= 10000){
			val = 0;

		}
		if (val < 0){
			val = 9999;

		}
		//char v = "1";
		handles();

		char SoonSoonToBe[5];   //Display Values!!
		sprintf(SoonSoonToBe, "%d", handle[2]);

		SoonToBe = SoonSoonToBe;
		globsize = size(SoonToBe);
		rensinput();

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
