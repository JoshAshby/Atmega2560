//-------------------------------------------
/*
BUTTON.c
2013 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

//What to run only once and once only when button 1 has been pressed.
void button1_once(void) {
  #if DEBUG
    uart_sendstr("0x81 - Button 1 pressed");
  #endif
  if(led <= 250) {
    led += 5;
  }
  return;
}

void button2_once(void) {
  #if DEBUG
    uart_sendstr("0x82 - Button 2 pressed");
  #endif
  if(led >= 5) {
    led -= 5;
  }
  return;
}

void button3_once(void) {
  #if DEBUG
    uart_sendstr("0x83 - Button 3 pressed");
  #endif
  return;
}

void button(int which, int what) {
  if(which == 0) {
    if(what == 1) {
      //Runs once once per button press and no more.
      if(once[which] == 1) {
        return;
      } else {
        button1_once();
      }
      once[which] = 1;
      return;
    } else {
      once[which] = 0;
      return;
    }
  }
  if(which == 1) {
    if(what == 1) {
      //Runs once once per button press and no more.
      if(once[which] == 1) {
        return;
      } else {
        button2_once();
      }
      once[which] = 1;
      return;
    } else {
      once[which] = 0;
      return;
    }
  }
  if(which == 2) {
    if(what == 1) {
      //Runs once once per button press and no more.
      if(once[which] == 1) {
        return;
      } else {
        button3_once();
      }
      once[which] = 1;
      return;
    } else {
      once[which] = 0;
      return;
    }
  }
  return;
}

void check_buttons(void) {
  /*
  In here is a fancy counter that keeps track of how long the button has been stable for
  if the button is still bouncing then the count will reset before it reaches the safe
  limit to count it as pressed.
  simply increases or resets a counter
  if the counter is above 5 it means the button is stable enough to be used
  if this happens, the function tied to that button is called
  if the button is released, then the count is cleared
  and the button bounce function is called
  */
  cli();
  #if DEBUG_BUT
    if ((PIND & button_one) | (PIND & button_two)) {
      uart_sendstr("0x08 - Button pressed");
    }
  #endif
  if((PIND & button_one) && (PIND & button_two)) {
    dig_count[2]++;
    if (dig_count[2] > DEBOUNCE_TIME) {
      button(2, 1);
      return;
    }
  } else {
    //if the button changes state, reset the count and trigger the button bounce function
    dig_count[2] = 0;
    button(2, 0);
    if((PIND & button_one)) {
      dig_count[0]++;
      if (dig_count[0] > DEBOUNCE_TIME) {
        button(0, 1);
        return;
      }
    } else {
      //if the button changes state, reset the count and trigger the button bounce function
      dig_count[0] = 0;
      button(0, 0);
    }
    if((PIND & button_two)) {
      dig_count[1]++;
      if (dig_count[1] > DEBOUNCE_TIME) {
        button(1, 1);
        return;
      }
    } else {
      //if the button changes state, reset the count and trigger the button bounce function
      dig_count[1] = 0;
      button(1, 0);
    }
  }
  sei();
  return;
}

/*
Buttons, this section uses timer2 because timer 1 is reserved for 16bit tasks
and timer0 is reserved for the kernel and task switching
*/
void init_buttons(void) {
  DDRD &= ~(1<<3)
       & ~(1<<4);

  TCNT2 = 0; //set the inital timer value to 0
  TCCR2B |= (1<<CS02); //set the clock prescaler to clock/256 or 62.5kHz
  TIMSK2 |= (1<<TOIE0); //start the timer with the interrupt overflow turned on

  #if DEBUG
    uart_sendstr("0x07 - DEBOUNCE is up...");
  #endif
  return;
}

ISR(TIMER2_OVF_vect) {
  /*
  Timer2 overflow interrupt servic routine for the debouncing of buttons.
  */
  check_buttons();
  return;
}
