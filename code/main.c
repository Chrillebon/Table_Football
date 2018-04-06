/* Name: main.c
 * Author: <Steen Grøntved>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <util/delay.h>

int op_ned;
int gem;
int state1;
int state2;

int value = 100;

void initialize(){ //prototype
DDRC=0x00;
DDRB=0xFF;
DDRD=0xFF;

}

int main(void)
{
	initialize();
	PORTD=0b11111111;

while (1){


/*
if ((PINC & 1<<PC4) && !(PINC & 1<<PC5)) {
	PORTB = 0b00000010;
}
	if (!(PINC & 1<<PC4) && (PINC & 1<<PC5)) {
		PORTB = 0b00000100;
}
	if (!(PINC & 1<<PC4) && !(PINC & 1<<PC5)){
		PORTB = 0b00000000;
	}*//*

else if (((PINC & 0<<PC4) && (PINC & 1<<PC5))){
	PORTB = 0b00000010;
}
else if (((PINC & 0<<PC4) && (PINC & 0<<PC5))){
	PORTB = 0b00000000;
}
else if (((PINC & 1<<PC4) && (PINC & 0<<PC5))){
	PORTB = 0b00000100;
}*/



/*
	if ((PINC & 1<<PC4) && (PINC & 1<<PC5)){
		if (op_ned == 1){
			value ++;
			op_ned = 0;
			gem = 0;
		}
		 if (op_ned == 2){
			value--;
			op_ned = 0;
			gem = 0;
		}
	}
	if (gem == 0){
		if (!(PINC & 1<<PC4) && (PINC & 1<<PC5)){
			op_ned = 1;
			gem = 1;
		}
		 if ((PINC & 1<<PC4) && !(PINC & 1<<PC5)){
		op_ned = 2;
		gem = 1;
	}
}*/


	if (!(PINC & 1<<PC4) && !(PINC & 1<<PC5)){
		state1 = 1;
	}
	else if ((PINC & 1<<PC4) && !(PINC & 1<<PC5)) {
		state1 = 2;
	}
	else if ((PINC & 1<<PC4) && (PINC & 1<<PC5)) {
		state1 = 3;
	}
	else if (!(PINC & 1<<PC4) && (PINC & 1<<PC5)){
		state1 = 4;
	}

while (1){
	if (!(PINC & 1<<PC4) && !(PINC & 1<<PC5)){
		state2 = 1;
	}
	else if ((PINC & 1<<PC4) && !(PINC & 1<<PC5)) {
		state2 = 2;
	}
	else if ((PINC & 1<<PC4) && (PINC & 1<<PC5)) {
		state2 = 3;
	}
	else if (!(PINC & 1<<PC4) && (PINC & 1<<PC5)){
		state2 = 4;
	}
/*
	if (state1 == 1 && state2 == 2){
		value++;
	} */
	if (state1 == 1 && state2 == 4){
		value --;
	} /*
	else if (state1 == 2 && state2 == 3){
		value++;
	}
	else if (state1 == 2 && state2 == 1){
		value--;
	}
	else if (state1 == 3 && state2 == 4){
		value++;
	}
	else if (state1 == 3 && state2 == 2){
		value--;
	} */
	else if (state1 == 4 && state2 == 1){
		value++;
	} /*
	else if (state1 == 4 && state2 == 3){
		value--;
	}*/

	state1 = state2;


 if (value > 100){
	 PORTB = 0b00000110;
	 	PORTD=0b11111111;
 } else{
	 PORTB = 0b00000000;
	 PORTD = 0b00000000;
 }
}
}
}
