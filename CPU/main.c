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
volatile int this = 0;
volatile int globsize = 0;
int recstat = 0;
int lastrecstat = 0;
int sendstat = 0;
int handle[5] = {0, 254, 255, 255, 255};
int logicval[3][3] = {100, 100, 0, 50, 62, 0, 150, 61, 0};
int clockstat = 0;

/*
Logicval:
			0				1				2
0		ballx		bally		ballspeed
1		p1-x		p1-y		p1-speed
2		p2-x		p2-y		p2-speed
*/



void initialize(){
	DDRC = 0xFF;
	DDRD = 0b11111110;
	DDRA = 0x00;
	DDRB = 0xFF;
	sei();
}

void timer0_init()
{
    // set up timer with prescaler = 1024
    TCCR0 |= (1 << CS02)|(1 << CS00);

    // initialize counter
		TCNT0 = 0;
}

void recieve()
{
	int temp = read(); //Læser før jeg tjekker om status er tændt
	int tempclk = (PIND & 1); //læser status
	if(tempclk)//skal kun gøre noget hvis den er tændt
	{
		if(clockstat != tempclk) //når den skifter og koden tjekker første gang
		{
			clockstat = tempclk;
			recstat++;
			if(temp == 255 || recstat == 5)
			{
				//255 bliver sendt som sidste/første data
				recstat = 0;
			}
			else
			{
				//Fordeler de nye værdier ind i handle
				handle[recstat-1] = temp;
			}
		}
	}
	else //Den er lav
	{
		if(clockstat != tempclk) //Den er lige skiftet
		{
			send(); //Nu sender den data videre igen
		}
		clockstat = 0;
	}
}

int read() //Sådan læses data
{
	int res = 0, t = 1;
	for(int i=0;i<8;i++)
	{
		res += (PINA & t);
		t *= 2;
	}
	return res;
}

void send() //Sender for nu de samme værdier videre
{
	if(sendstat == 0)
	{
		PORTB = 255;
	}
	if(sendstat == 1) // ball-x
	{
		PORTB = handle[0];//logicval[0][0];
	}
	else if(sendstat == 2) //Ball-y
	{
		PORTB = handle[2];//logicval[0][1];
	}
	else if(sendstat == 3) // P1-speed//p1-y
	{
		PORTB = handle[1];//logicval[1][1];
	}
	else if(sendstat == 4) // P2-speed//p2-y
	{
		PORTB = handle[3];//logicval[2][1];
	}
	sendstat++;
	if(sendstat >= 5) //reset
  {
    sendstat = 0;
  }
}

void logic()
{
	//Er ikke noget nu - vi havde ikke tid
	//Burde her regne ud hvad bolden ville gøre, hvis den rammer en spiller
}

int main(void)
{

	initialize();
	timer0_init();

	while(1){
		recieve();

		logic();

		debug(); // Findes under debug.h

	}
	return 0;

	}
