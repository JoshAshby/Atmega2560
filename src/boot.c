//-------------------------------------------
/*
BOOT.c
2013 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
//BIOS
//========================
/*
This function is to setup hardaware, it will start
the pwm, adc, uart, and twi along with turn on the CPU power pin.
If the pin isn't pulled hight then somethings gone wrong before the
CPU is even up and running the code most of the time. Just so you know

UART has to be started first if your deebuging and using the serial console to do so
All debug keys get output to there

We're only starting PWM1 because the kernel uses TIMER0 for context switches,
and the button debouncer uses TIMER2 for the overflow interrupt

ADC is started with the results left aligned to make fake 8bit
*/
#include "global.h"
void bios(void) {
  uart_start();
  pwm_setup(2);
  adc_start(1);
  twi_start();

  //button code
  init_buttons();

  //set the CPU_POW led pin to high to show we have power
  DDRD |= (1<<CPU_POW);
  PORTD |= (1<<CPU_POW);

  //set the status leds as outputs
  DDRD |= (1<<stat_led1);
  DDRD |= (1<<stat_led2);

  //if this is my dev board, pull them low because the leds are cathode
  #if DEV
    PORTD &= ~(1<<stat_led1)
          & ~(1<<stat_led2);
  #endif

  #if DEBUG
    uart_sendstr("0x01 - Hardware setup successful...");
    uart_sendstr("Bios complete...");
    uart_sendstr("Starting main code...");
  #endif
  return;
}
