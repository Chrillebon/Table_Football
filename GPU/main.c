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

void initialize(){
	/*DDRD = 0x00;
	DDRA = 0xFF;*/
}

int main(void)
{

	initialize();
	GLCD_Initalize();
	GLCD_ClearText();
	GLCD_ClearCG();
	GLCD_ClearGraphic();

	GLCD_TextGoTo(0,0);
	GLCD_WriteString("Hello World!");

	int x = 25;
	while(1)
	{
		GLCD_Line(x,0,x,128,1);
		GLCD_Line(x+1,0,x+1,128,0);
		x = (x+1)%240;
	}
	return 0;
}
