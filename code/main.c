#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "check_rot.h"

void timer0_init()
{
    // set up timer with prescaler = 256 /*1024*/
    TCCR0 |= (1 << CS02)/*|(1 << CS00)*/;

    // initialize counter
    TCNT0 = 0;

    TIMSK |= (1<<TOIE0); // overflow enable

    sei();
}

ISR(TIMER0_OVF_vect)//overflow interrupt funktion:
{
  TCNT0 = 0;
  overflow++;
  delayval++;
}

void oflow()
{
  //127 så den kan dreje begge veje
  diff1 = abs(h1_value);
  diff2 = abs(h2_value);
  h1_value = 127;
  h2_value = 127;
  overflow = 0;
}

void initialize(){
DDRC=0b00000000;
DDRB=0b00111110;
DDRD=0b11111111;
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

void delay()
{
  delayval = 0;
  while(delayval < 1000)
  {
    //Vent
  }
  return;
}

void send()
{
  //B6 og B7 er status
  //PORTD er værdier
  if(sendstat < 5) //pos1
  {
    PORTB |= smart[0]; //Skal ikke modtage i anden ende (aktiv lav)
    PORTD = 0; //Skal ikke sende fejlværdier
    //status = 0,0
    PORTB &= ~smart[6];
    PORTB &= ~smart[7];
    PORTD = p1_value;
    delay();
    PORTB &= ~smart[0]; //Kan godt modtage fra nu af
  }
  else if(sendstat >=5 && sendstat < 10) //speed1
  {
    PORTB |= smart[0]; //Skal ikke modtage i anden ende (aktiv lav)
    PORTD = 0; //Skal ikke sende fejlværdier
    //status = 1,0
    PORTB |= smart[6];
    PORTB &= ~smart[7];
    PORTD = diff1;
    delay();
    PORTB &= ~smart[0]; //Kan godt modtage fra nu af
  }
  else if(sendstat >= 10 && sendstat < 15) //pos2
  {
    PORTB |= smart[0]; //Skal ikke modtage i anden ende (aktiv lav)
    PORTD = 0; //Skal ikke sende fejlværdier
    //status = 1,1
    PORTB |= smart[6];
    PORTB |= smart[7];
    PORTD = p2_value;
    delay();
    PORTB &= ~smart[0]; //Kan godt modtage fra nu af
  }
  else if(sendstat >= 15 && sendstat < 20) //speed2
  {
    PORTB |= smart[0]; //Skal ikke modtage i anden ende (aktiv lav)
    PORTD = 0; //Skal ikke sende fejlværdier
    //status = 0,1
    PORTB &= ~smart[6];
    PORTB |= smart[7];
    PORTD = diff2;
    delay();
    PORTB &= ~smart[0]; //Kan godt modtage fra nu af
  }
  sendstat++;
  if(sendstat >= 20)//8) //reset
  {
    sendstat = 0;
  }
}

int main(void)
{
	initialize();
  memset(val);
	p1_value = 10;
  int slowsend = 0;
  while (1){
    rot1();
    speed1();
    rot2();
    speed2();
    if(overflow >= 1)
    {
      oflow();
    }
    if(slowsend == 3)
    {
      send();
    }
    slowsend = (slowsend+1)%4;
  }
}
