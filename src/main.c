//-------------------------------------------
/*
MAIN.c
2013 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby

freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

int main(void) { //Main loop, runs once but can have an infinit loop in it
  cli();
  /*
  First we need to set the hardaware up, this is a macro in global.h which takes care of calling the various funtions that
  setup the registers to the proper seting, and also pulls the CPU_POW pin high
  if debug in GLOBAL.h is set, then debug keys will be sent out through the serial port
  when this function is called
  */
  bios();
  //if we're in debug mode, make sure you send stuff saying we got to the main code
  #if DEBUG
    uart_sendstr("0x6 - Main code checkpoint...");
  #endif

  sei();

  init_out('D', 5);
  //infinit loop that doesn't stop running. (always true since 1 is always 1 )
  while(1) {
      pwm1A(led);
  };
  return 0; //never reached since 1 is always true
}
