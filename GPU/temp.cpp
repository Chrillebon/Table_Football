/* Name: main.c for LYD
 * Author: Christian Mikkelstrup
 * Copyright: Use of code has to be accepted through the author
 * License: Use for inspiration, and use common sense
 */

#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

//#include "GLCD_Logic.h"

int r, newx, newy, oldx, oldy;

void initialize(){
	/*DDRD = 0x00; //Læse input
	GLCD_Initalize();
	GLCD_ClearText();
	GLCD_ClearCG();
	GLCD_ClearGraphic();*/
	r=10;
}

void delay()
{}

void GLCD_SetPixel(unsigned char a, unsigned char b, int color)
{
  std::cout << (int)a <<" "<< (int)b << '\n';
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
		GLCD_SetPixel(cx+x, cy+y, 0);
    GLCD_SetPixel(cx-x, cy+y, 0);
    GLCD_SetPixel(cx-x, cy-y, 0);
    GLCD_SetPixel(cx+x, cy-y, 0);
    GLCD_SetPixel(cx+y, cy+x, 0);
    GLCD_SetPixel(cx-y, cy+x, 0);
    GLCD_SetPixel(cx-y, cy-x, 0);
    GLCD_SetPixel(cx+y, cy-x, 0);

		GLCD_SetPixel(a+x, b+y, 1);
		GLCD_SetPixel(a-x, b+y, 1);
		GLCD_SetPixel(a-x, b-y, 1);
		GLCD_SetPixel(a+x, b-y, 1);
		GLCD_SetPixel(a+y, b+x, 1);
		GLCD_SetPixel(a-y, b+x, 1);
		GLCD_SetPixel(a-y, b-x, 1);
		GLCD_SetPixel(a+y, b-x, 1);
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


const unsigned char color = 1;

void GLCD_Rectangle(unsigned char x, unsigned char y, unsigned char b, unsigned char a)
{
  unsigned char j; // zmienna pomocnicza
  // rysowanie linii pionowych (boki)
  for (j = 0; j < a; j++) {
		GLCD_SetPixel(x, y + j, color);
		GLCD_SetPixel(x + b - 1, y + j, color);
	}
  // rysowanie linii poziomych (podstawy)
  for (j = 0; j < b; j++)	{
		GLCD_SetPixel(x + j, y, color);
		GLCD_SetPixel(x + j, y + a - 1, color);
	}
}


void GLCD_Circle(unsigned char cx, unsigned char cy ,unsigned char radius,int reverse)
{
int x, y, xchange, ychange, radiusError;
x = radius;
y = 0;
xchange = 1 - 2 * radius;
ychange = 1;
radiusError = 0;
while(x >= y)
  {
    GLCD_SetPixel(cx+x, cy+y, color-reverse);
    GLCD_SetPixel(cx-x, cy+y, color-reverse);
    GLCD_SetPixel(cx-x, cy-y, color-reverse);
    GLCD_SetPixel(cx+x, cy-y, color-reverse);
    GLCD_SetPixel(cx+y, cy+x, color-reverse);
    GLCD_SetPixel(cx-y, cy+x, color-reverse);
    GLCD_SetPixel(cx-y, cy-x, color-reverse);
    GLCD_SetPixel(cx+y, cy-x, color-reverse);
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


void GLCD_FillRectangle(uint8_t x, uint8_t y, uint8_t dx, uint8_t dy, int reverse)
{
uint8_t i, j;
for(i = x; i < x + dx; i++)
  for(j = y; j < y + dy; j++)
    GLCD_SetPixel(i, j, 1-reverse);
}


int main(void)
{
	initialize();
	//GLCD_FillRectangle(119, 0, 2, 128, 0);
	//GLCD_Ball(100,60,3,0);
	int i=0;
	oldx = 10;
	oldy = 20;
	newx = 200;
	newy = 20;

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



	/*while(1)
	{
		MOVE_Ball(oldx,oldy,newx,newy);
		for(int o=0;o<100;o++)
		{
			delay();
		}
		oldx = newx;
		oldy = newy;
		newx = 150;
		newy = 120;
		MOVE_Ball(oldx,oldy,newx,newy);
		for(int o=0;o<100;o++)
		{
			delay();
		}
		oldx = newx;
		oldy = newy;
		newx = 60;
		newy = 30;
		MOVE_Ball(oldx,oldy,newx,newy);
		for(int o=0;o<100;o++)
		{
			delay();
		}
		oldx = newx;
		oldy = newy;
		newx = 80;
		newy = 80;
		MOVE_Ball(oldx,oldy,newx,newy);
		for(int o=0;o<100;o++)
		{
			delay();
		}
		oldx = newx;
		oldy = newy;
		newx = 200;
		newy = 20;
	}*/
	return 0;
}
