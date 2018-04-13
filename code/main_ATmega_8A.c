/* Name: main.c
 * Author: <Steen Grøntved>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void timer0_init()
{
    // set up timer with prescaler = 1024
    TCCR0 |= (1 << CS02)|(1 << CS00);

    // initialize counter
    TCNT0 = 0;
}


int p1_state1;
int p1_state2;

int p2_state1;
int p2_state2;

int h1_state1;
int h1_state2;

int h2_state1;
int h2_state2;

int p1_value = 250;
int p2_value = 100;

int h1_value = 100;
int h2_value = 100;

int hm1;
int hm2;

int runder = 0;
int hb1;
int hb2;

void initialize(){ //prototype
DDRC=0b00000000;
DDRB=0b00111001;
DDRD=0b11111111;
sei();
}

int main(void)
{
	initialize();
	timer0_init();
while (1){

//Placerring encoder 1

	if (!(PINC & 1<<PC4) && !(PINC & 1<<PC5)){
		p1_state2 = 1;
	}
	else if ((PINC & 1<<PC4) && !(PINC & 1<<PC5)) {
		p1_state2 = 2;
	}
	else if ((PINC & 1<<PC4) && (PINC & 1<<PC5)) {
		p1_state2 = 3;
	}
	else if (!(PINC & 1<<PC4) && (PINC & 1<<PC5)){
		p1_state2 = 4;
	}

	if (p1_state1 == 1 && p1_state2 == 4){
		if (p1_value>0){
			p1_value --;
		}
	}
	else if (p1_state1 == 4 && p1_state2 == 1){
		if (p1_value<255){
			p1_value++;
		}
	}
p1_state1 = p1_state2;

	//Hastighed encoder 1

			if (!(PINB & 1<<PB1) && !(PINB & 1<<PB2)){
			h1_state2 = 1;
		}
		else if ((PINB & 1<<PB1) && !(PINB & 1<<PB2)) {
			h1_state2 = 2;
		}
		else if ((PINB & 1<<PB1) && (PINB & 1<<PB2)) {
			h1_state2 = 3;
		}
		else if (!(PINB & 1<<PB1) && (PINB & 1<<PB2)){
			h1_state2 = 4;
		}

		if (h1_state1 == 1 && h1_state2 == 2){
			h1_value++;
		}
		if (h1_state1 == 1 && h1_state2 == 4){
			h1_value --;
		}
		else if (h1_state1 == 2 && h1_state2 == 3){
			h1_value++;
		}
		else if (h1_state1 == 2 && h1_state2 == 1){
			h1_value--;
		}
		else if (h1_state1 == 3 && h1_state2 == 4){
			h1_value++;
		}
		else if (h1_state1 == 3 && h1_state2 == 2){
			h1_value--;
		}
		else if (h1_state1 == 4 && h1_state2 == 1){
			h1_value++;
		}
		else if (h1_state1 == 4 && h1_state2 == 3){
			h1_value--;
		}
h1_state1 = h1_state2;

// Placering encoder 2

	if (!(PINC & 1<<PC0) && !(PINC & 1<<PC1)){
		p2_state2 = 1;
	}
	else if ((PINC & 1<<PC0) && !(PINC & 1<<PC1)) {
		p2_state2 = 2;
	}
	else if ((PINC & 1<<PC0) && (PINC & 1<<PC1)) {
		p2_state2 = 3;
	}
	else if (!(PINC & 1<<PC0) && (PINC & 1<<PC1)){
		p2_state2 = 4;
	}

	if (p2_state1 == 1 && p2_state2 == 4){
		if (p2_value>0){
			p2_value --;
		}
	}
	else if (p2_state1 == 4 && p2_state2 == 1){
		if (p2_value<255){
			p2_value++;
		}
	}

	p2_state1 = p2_state2;

// Hastighed encoder 2

	if (!(PINC & 1<<PC2) && !(PINC & 1<<PC3)){
		h2_state2 = 1;
	}
	else if ((PINC & 1<<PC2) && !(PINC & 1<<PC3)) {
		h2_state2 = 2;
	}
	else if ((PINC & 1<<PC2) && (PINC & 1<<PC3)) {
		h2_state2 = 3;
	}
	else if (!(PINC & 1<<PC2) && (PINC & 1<<PC3)){
		h2_state2 = 4;
	}

	if (h2_state1 == 1 && h2_state2 == 2){
		h2_value++;
	}
	if (h2_state1 == 1 && h2_state2 == 4){
			h2_value --;
	}
	else if (h2_state1 == 2 && h2_state2 == 3){
		h2_value++;
	}
	else if (h2_state1 == 2 && h2_state2 == 1){
		h2_value--;
	}
	else if (h2_state1 == 3 && h2_state2 == 4){
		h2_value++;
	}
	else if (h2_state1 == 3 && h2_state2 == 2){
		h2_value--;
	}
	else if (h2_state1 == 4 && h2_state2 == 1){
			h2_value++;
	}
	else if (h2_state1 == 4 && h2_state2 == 3){
		h2_value--;
	}
h2_state1 = h2_state2;

// virker ikke endnu (hastigheds-beregnelse)
/*
if (runder==10 && TCNT0 == runder){
	hb1 = hb1 + (h1_value*100);
	hb2 = hb2 + (h2_value*100);
	runder = runder + 10;
} else if (runder==20 && TCNT0 == runder){
  hb1 = hb1 + (h1_value*100);
	hb2 = hb2 + (h2_value*100);
	runder = runder + 10;
} else if (runder==30 && TCNT0 == runder){
  hb1 = hb1 + (h1_value*100);
  hb2 = hb2 + (h2_value*100);
	runder = runder + 10;
} else if (runder==40 && TCNT0 == runder){
  hb1 = hb1 + (h1_value*100);
  hb2 = hb2 + (h2_value*100);
	runder = runder + 10;
} else if (runder==50 && TCNT0 == runder){
  hb1 = hb1 + (h1_value*100);
  hb2 = hb2 + (h2_value*100);
	runder = runder + 10;
} else if (runder==60 && TCNT0 == runder){
  hb1 = hb1 + (h1_value*100);
  hb2 = hb2 + (h2_value*100);
	runder = runder + 10;
} else if (runder==70 && TCNT0 == runder){
  hb1 = hb1 + (h1_value*100);
  hb2 = hb2 + (h2_value*100);
	runder = runder + 10;
} else if (runder==80 && TCNT0 == runder){
  hb1 = hb1 + (h1_value*100);
  hb2 = hb2 + (h2_value*100);
	runder = runder + 10;
} else if (runder==90 && TCNT0 == runder){
  hb1 = hb1 + (h1_value*100);
  hb2 = hb2 + (h2_value*100);
	runder = runder + 10;
} else if (runder==100 && TCNT0 == runder){
  hb1 = hb1 + (h1_value*100);
  hb2 = hb2 + (h2_value*100);
	hm1 = hb1/10;
	hm2 = hb2/10;
	runder = 10;
	TCNT0 = 0;
}
*/

/*
 if (h1_value > 1000){
	 PORTB = 0b00111111 & PORTB;
	 PORTB = PORTB | 0bAB000000;
	 PORTB = 0b00000001;
	 	PORTD=0b11111111;
 } else{
	 PORTB = 0b00000000;
	 PORTD = 0b00000000;
 } */

 // Data fra Atmega 8 til Atmega 16 på baggrund af modtagende status-pins

if (!(PINB & 1<<PB6) && !(PINB & 1<<PB7)){
PORTD = p1_value;
} else if (!(PINB & 1<<PB6) && (PINB & 1<<PB7)){
PORTD = p2_value;
} else if ((PINB & 1<<PB6) && !(PINB & 1<<PB7)){
PORTD = h1_value;
} else if ((PINB & 1<<PB6) && (PINB & 1<<PB7)){
PORTD = h2_value;
}

}
}
