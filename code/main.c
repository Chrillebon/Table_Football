#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "check_rot.h"

void timer0_init()
{
    // set up timer with prescaler = 1024
    TCCR0 |= (1 << CS02)|(1 << CS00);

    // initialize counter
    TCNT0 = 0;

    TIMSK |= (1<<TOIE0); // overflow enable

    sei();
}

ISR(TIMER0_OVF_vect)//overflow interrupt funktion:
{
  TCNT0 = 0;
  overflow++;
}

void oflow()
{
  diff = abs(h1_value);
  h1_value = 0;
  overflow = 0;
}

void initialize(){
DDRC=0b00000000;
DDRB=0b00111001;
DDRD=0b11111111;
timer0_init();
}

int main(void)
{
	initialize();
	p1_value = 10;
  while (1){
    rot1(0);
    rot1(1);
    rot2(0);
    rot2(1);
    if(overflow >= 1)
    {
      oflow();
    }
    PORTD = diff;
  }
}
