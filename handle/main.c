#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "check_rot.h"

void timer0_init()
{
    // set up timer with prescaler = 8
    TCCR0 |= (1 << CS01) & ~(1 << CS02);

    // initialize counter
    TCNT0 = 0;

    TIMSK |= (1<<TOIE0); // overflow enable

    sei(); //Global interrupts
}

ISR(TIMER0_OVF_vect)//overflow interrupt funktion:
{
  TCNT0 = 0;
  overflow++;
}

void oflow() // Endnu en overflow funktion, men mere præcis i styring af hvornår den kommer
{
  overflow = 0;
  PORTB &= ~smart[0]; // Skal ikke modtage nu
  send();
}

void initialize(){
DDRC=0x00;
DDRB=0b11111001;
DDRD=0xFF;
timer0_init();
}

void memset(int arr[2][4])
{
  int i,o;
  for(i=0;i<2;i++)
  {
    for(o=0;o<4;o++)
    {
      arr[i][o] = 0;
    }
  }
}

void send()
{
  //PORTD er værdier
  if(sendstat == 0)
  {
    PORTD = 255;
  }
  else if(sendstat == 1) //pos1
  {
    PORTD = p1_value;
  }
  else if(sendstat == 2) //speed1
  {
    PORTD = diff1;
  }
  else if(sendstat == 3) //pos2
  {
    PORTD = p2_value;
  }
  else if(sendstat == 4) //speed2
  {
    PORTD = diff2;
  }
  sendstat++;
  if(sendstat >= 5) //reset
  {
    sendstat = 0;
  }
}

int main(void)
{
	initialize();
  memset(val);
  while (1){
    rot1();
    speed1();
    rot2();
    speed2();
    if(overflow == 2)
    {
      PORTB |= smart[0]; //Nu kan den modtage
    }
    if(overflow >= 4)
    {
      oflow();
      speedcontrol++;
    }
    if(speedcontrol >= 18) //Så man kan nå at dreje så meget som muligt, uden den kommer uden for grænserne
    {
      //127 så den kan dreje begge veje
      diff1 = abs(h1_value);
      diff2 = abs(h2_value);
      h1_value = 127;
      h2_value = 127;
      speedcontrol = 0;
    }
  }
}
