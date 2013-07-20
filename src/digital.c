//-------------------------------------------
/*
DIGITAL.c
2013 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

void init_out(char port, int pin) {
  switch (port) { //switch determines if which port it is
    case 'D':
      DDRD |= (1<<pin); //change the pin to output
      break;
    case 'B':
      DDRB |= (1<<pin); //change pin to output
      break;
  }
}

void out(char port, int pin, _Bool value) {
  /*
  Change the state of a pin on given port
  simply pass the Port as either D or B (make sure to enclose it in single
  quotes like so: 'D')
  The pin number you would like to change state of,
  and either a 0 to sink current or 1 to source it on that pin
  */
  switch (port) { //switch determines if which port it is
    case 'D':
//      DDRD |= (1<<pin); //change the pin to output
      if(value == 1) { //sink or source current
        PORTD |= (1<<pin);
      } else {
        PORTD &= ~(1<<pin);
      }
      break;
    case 'B':
//      DDRB |= (1<<pin); //change pin to output
      if(value == 1) { //sink or source current
        PORTB |= (1<<pin);
      } else {
        PORTB &= ~(1<<pin);
      }
      break;
  }
}
