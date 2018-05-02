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
#include <stdbool.h>
//#include "GLCD_Logic.h"

int r, newx, newy, oldx, oldy, lastrecstat = 0, recstat = 0, clockstat = 0, debug = 0;
int logicval[3][3] = {100, 100, 99, 60, 99, 0, 180, 99, 0};

/*
Logicval
			0				1				2
0		ballx		bally		*ball-speed*
1		*p1-x*	p1-y		*p1-speed*
2		*p2-x*	p2-y		*p2-speed*

**: not in use
*/

void initialize(){
	DDRD = 0x00; //Læse input
	DDRB = 0x00; //Læse status
	GLCD_Initalize();
	GLCD_ClearText();
	GLCD_ClearCG();
	GLCD_ClearGraphic();
	r=3;
}

bool isReserved(unsigned char x, unsigned char y)
{
	if (x < 20) return true; //Venstre linje eller mindre
	if (x > 219) return true; //Højre linje eller mere
	if (x == 118) return true; //Midterlinjen
	if ((x == 47 || x == 191) && y <= 92 && y >= 33) return true; //Forreste linje straffefelt begge sider
	if ((x == 27 || x == 211) && y <= 80 && y >= 45) return true;  //Forreste linje målfelt begge sider
	if ((y == 92 || y == 33) && (x >= 192 || x <= 46)) return true; //Nederste og øverste strej i Straffefelt

	if (y == 43 && x >= 114 && x <= 122) return true; //43. linje
	if (y == 44 && (x==111 || x==112 || x==113 || x==123 || x==124 || x==125)) return true; //44. linje
	if (y == 45 && ((x>=20 && x<=26) || x==109 || x==110 || x==126 || x==127 || x>=212)) return true; //45. linje
	if (y == 46 && (x==107 || x==108 || x==128 || x==129)) return true;
	if (y == 47 && (x==106 || x==130)) return true;
	if (y == 48 && (x==105 || x==131)) return true;
	if (y == 49 && (x==104 || x==132)) return true;
	if (y == 50 && (x==103 || x==133)) return true;
	if (y == 51 && (x==102 || x==134)) return true;
	if (y == 52 && (x==101 || x==135)) return true;
	if (y == 53 && (x==101 || x==135)) return true;
	if (y == 54 && (x==100 || x==136)) return true;
	if (y == 55 && (x==100 || x==136)) return true;
	if (y == 56 && (x==99 || x==137)) return true;
	if (y == 57 && (x==99 || x==137)) return true;
	if (y == 58 && (x==99 || x==137)) return true;
	if (y == 59 && (x==98 || x==138)) return true;
	if (y == 60 && (x==98 || x==138)) return true;
	if (y == 61 && (x==98 || x==138)) return true;
	if ((y==62 || y==63 || y==64) && (x==37 || x==38 || x==98 || x==117 || x==119 || x==138 || x==200 || x==201)) return true;

	if (y == 79 && (x==106 || x==130)) return true;
	if (y == 78 && (x==105 || x==131)) return true;
	if (y == 77 && (x==104 || x==132)) return true;
	if (y == 76 && (x==103 || x==133)) return true;
	if (y == 75 && (x==102 || x==134)) return true;
	if (y == 74 && (x==101 || x==135)) return true;
	if (y == 73 && (x==101 || x==135)) return true;
	if (y == 72 && (x==100 || x==136)) return true;
	if (y == 71 && (x==100 || x==136)) return true;
	if (y == 70 && (x==99 || x==137)) return true;
	if (y == 69 && (x==99 || x==137)) return true;
	if (y == 68 && (x==99 || x==137)) return true;
	if (y == 67 && (x==98 || x==138)) return true;
	if (y == 66 && (x==98 || x==138)) return true;
	if (y == 65 && (x==98 || x==138)) return true;

	if (y == 80 && ((x>=20 && x<=26) || x==107 || x==108 || x==128 || x==129 || x>=212)) return true;
	if (y == 81 && (x==109 || x==110 || x==126 || x==127)) return true;
	if (y == 82 && (x==111 || x==112 || x==113 || x==123 || x==124 || x==125)) return true;
	if (y == 83 && x >= 114 && x <= 122) return true;

	return false;
}

void MOVE_Ball(unsigned char cx, unsigned char cy, unsigned char a, unsigned char b)
{
int x, y, xchange, ychange, radiusError;
x = r;
y = 0;
xchange = 1 - 2 * r;
ychange = 1;
radiusError = 0;
while(x >= y)
  {
		int o;
		for(o=0;o<2;o++)//o=-x;o<=x;o++)
		{
			if(!isReserved(cx+o,cy+y))
				GLCD_SetPixel(cx+o, cy+y, 0);

			if(!isReserved(cx-o,cy+y))
				GLCD_SetPixel(cx-o, cy+y, 0);

			if(!isReserved(cx-o,cy-y))
				GLCD_SetPixel(cx-o, cy-y, 0);

			if(!isReserved(cx+o,cy-y))
				GLCD_SetPixel(cx+o, cy-y, 0);

			if(!isReserved(cx+y,cy+o))
				GLCD_SetPixel(cx+y, cy+o, 0);

			if(!isReserved(cx-y,cy+o))
				GLCD_SetPixel(cx-y, cy+o, 0);

			if(!isReserved(cx-y,cy-o))
				GLCD_SetPixel(cx-y, cy-o, 0);

			if(!isReserved(cx+y,cy-o))
				GLCD_SetPixel(cx+y, cy-o, 0);

			if(!isReserved(a+o,b+y))
				GLCD_SetPixel(a+o, b+y, 1);

			if(!isReserved(a-o, b+y))
				GLCD_SetPixel(a-o, b+y, 1);

			if(!isReserved(a-o, b-y))
				GLCD_SetPixel(a-o, b-y, 1);

			if(!isReserved(a+o, b-y))
				GLCD_SetPixel(a+o, b-y, 1);

			if(!isReserved(a+y, b+o))
				GLCD_SetPixel(a+y, b+o, 1);

			if(!isReserved(a-y, b+o))
				GLCD_SetPixel(a-y, b+o, 1);

			if(!isReserved(a-y, b-o))
				GLCD_SetPixel(a-y, b-o, 1);

			if(!isReserved(a+y, b-o))
				GLCD_SetPixel(a+y, b-o, 1);
		}




    y++;
    radiusError += ychange;
    ychange += 2;
    if ( 2*radiusError + xchange > 0 )
    {
      x--;
    	radiusError += xchange;
    	xchange += 2;
  	}
  }
}

void draw_field()
{
	GLCD_FillRectangle(17,0,2,128,0); //Venstre side
	GLCD_Rectangle(18,33,30,60); //Venstre Straffefelt
	GLCD_Rectangle(18,45,10,36); //Venstre Målfelt
	GLCD_FillRectangle(37,62,2,2,0); //Venstre Straffeplet
	GLCD_FillRectangle(17,47,1,32,1); //Tyndere venstre strej
	GLCD_Rectangle(15,47,4,32); //Venstre Målkasse

	GLCD_FillRectangle(117,62,3,3,0); //Midterprik
	GLCD_Circle(118,63,20,0); //Midtercirkel
	GLCD_FillRectangle(118,0,1,128,0); //Midterlinjen


	GLCD_FillRectangle(239-18-1,0,2,128,0); //Højre side
	GLCD_Rectangle(239-18-30,33,30,60); //Højre straffefelt
	GLCD_Rectangle(239-18-10,45,10,36); //Højre Målfelt
	GLCD_FillRectangle(239-37-2,62,2,2,0); //Højre Straffeplet
	GLCD_FillRectangle(239-17-1,47,1,32,1); //Tyndere højre strej
	GLCD_Rectangle(239-15-4,47,4,32); //Højre Målkasse
}

int read()
{
	int res = 0, t = 128, u = 1;
	for(int i=0;i<8;i++)
	{
		if(PIND & t)
		{
			res+=u;
		}
		t /= 2;
		u *= 2;
	}
	return res;
}

int status()
{
	int vala = (PINB & 4), valb = (PINB & 2);
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
		GLCD_Circle(128,64,20,0);
		return 3;
	}
	return 4; //Burde aldrig komme herned...
}

void recieve()
{
	char damn[5];
	debug = 0;
	while(debug < 5)
	{
		int temp = read();
		int tempclk = (PINB & 1);
		recstat = status();
		if(tempclk)
		{
			if(clockstat != tempclk)
			{
				debug++;
				clockstat = tempclk;
				sprintf(damn, "%d", recstat);
				GLCD_TextGoTo(4,0);
				GLCD_WriteString(damn);
				if(recstat == 4 || temp == 255)
				{
					//Gør intet
				}
				else if(recstat == 0)
				{
					logicval[0][0] = temp;
				}
				else if(recstat == 1)
				{
					logicval[0][1] = temp;
				}
				else if(recstat == 2)
				{
					logicval[1][1] = temp;
				}
				else if(recstat == 3)
				{
					logicval[2][1] = temp;
				}
			}
		}
		else
		{
			clockstat = 0;
		}
	}
}

void draw_ball_test()
{
	MOVE_Ball(oldx,oldy,newx,newy);
	oldx = newx;
	oldy = newy;
	newx = 150;
	newy = 120;
	MOVE_Ball(oldx,oldy,newx,newy);
	oldx = newx;
	oldy = newy;
	newx = 60;
	newy = 30;
	MOVE_Ball(oldx,oldy,newx,newy);
	oldx = newx;
	oldy = newy;
	newx = 80;
	newy = 80;
	MOVE_Ball(oldx,oldy,newx,newy);
	oldx = newx;
	oldy = newy;
	newx = 120;
	newy = 50;
	MOVE_Ball(oldx,oldy,newx,newy);
	/*for(int o=0;o<1000;o++)
	{
		delay();
	}*/
	oldx = newx;
	oldy = newy;
	newx = 200;
	newy = 20;
}


int main(void)
{
	initialize();
	//GLCD_FillRectangle(119, 0, 2, 128, 0);
	//GLCD_Ball(100,60,3,0);
	oldx = 10;
	oldy = 20;
	newx = 200;
	newy = 20;

	draw_field();
	//draw_ball_test();

	oldx = 0;
	oldy = 0;

	char str[5];

	while(1)
	{
		int i=0;
		recieve();
		GLCD_TextGoTo(0,0);
		sprintf(str, "%d", logicval[1][1]);
		GLCD_WriteString(str);
		GLCD_TextGoTo(0,2);
		sprintf(str, "%d", logicval[2][1]);
		GLCD_WriteString(str);
		MOVE_Ball(oldx, oldy, logicval[1][1], logicval[2][1]); // <-------
		oldx = logicval[1][1];
		oldy = logicval[2][1];
		//draw_ball_test();
	}
	return 0;
}
