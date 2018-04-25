/* Name: main.c for LYD
 * Author: Christian Mikkelstrup
 * Copyright: Use of code has to be accepted through the author
 * License: Use for inspiration, and use common sense
 */

#include <avr/io.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "Graphic.c"
#include "Graphic.h"
#include "T6963C.c"
#include "T6963C.h"
#include "GLCD_Logic.h"

/*
Koordinates:
				0				1					2
0			Ballx		Player1x	Player2x
1			Bally		Player1y	Player2y
*/

void initialize(){
	DDRD = 0x00; //Læse input
	GLCD_Initalize();
	GLCD_ClearText();
	GLCD_ClearCG();
	GLCD_ClearGraphic();
}

void update()
{
	//Ball
	RDY_Ball(Koor[0][0], Koor[0][1]);
	//Alle Spillerne
	MOVE_Ball();

}

int main(void)
{
	initialize();

	while(1)
	{

	}
	return 0;
}
