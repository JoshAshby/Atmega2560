//-------------------------------------------
/*
PWM.c
2013 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

void pwm_setup(char which) {
  //========================
  //PWM0
  //========================
  void pwm0(void) {
    TCCR0B |= (1<<CS00)
           | (1<<CS01); //set timerO clock prescaler to 64
    TCCR0A |= (1<<WGM00);//fast pwm with top as 0xFF

    DDRD |= (1<<5);
    DDRD |= (1<<6); //set the OCR0 pins as outputs
    #if DEBUG
      uart_sendstr("0x11 - PWM_0 is up...");
    #endif
  }
  //========================
  //PWM1
  //========================
  void pwm1(void) {
    TCCR1B |= (1<<CS11)
           | (1<<CS10);//set timer1 clock prescaler to 64
    TCCR1A |= (1<<WGM10)
           | (1<<WGM12); //fast pwm (8bit) with top as 0x03FF

//This bits for incase you want 16bit and not 10bit PWM on timer1
//        TCCR1A |= (1<<WGM11)
//                | (1<<WGM12)
//                | (1<<WGM13); //fast pwm (16bit) with top as 0x03FF
//        //ICR1H = 0xFF; //set IRC1 to max for full 16bit resolution
//        //IRC1L = 0xFF;

    DDRB |= (1<<1);
    DDRB |= (1<<2);//set the OCR1 pins as outputs

    #if DEBUG
      uart_sendstr("0x12 - PWM_1 is up...");
    #endif
  }
  //========================
  //PWM2
  //========================
  void pwm2(void) {
    TCCR2B |= (1<<CS22);//set timer2 clock prescaler to 64
    TCCR2A |= (1<<WGM20);//fast pwm with top as 0xFF

    DDRD |= (1<<3);
    DDRB |= (1<<3); //set the OCR2 pins as outputs
    #if DEBUG
      uart_sendstr("0x13 - PWM_2 is up...");
    #endif
  }
  switch (which) {
    case 0:
      pwm0();
      pwm1();
      pwm2();
      #if DEBUG
        uart_sendstr("0x10 - PWM_ALL is up...");
      #endif
      break;
    case 1:
      pwm0();
      break;
    case 2:
      pwm1();
      break;
    case 3:
      pwm2();
      break;
  }
  return;
}

void pwm0A(uint8_t value) {
  TCCR0A |= (1<<COM0A1);
  OCR0A = value;
}

void pwm0B(uint8_t value) {
  TCCR0A |= (1<<COM0B1);
  OCR0B = value;
}

void pwm1A(uint16_t value) {
  TCCR1A |= (1<<COM1A1);
  OCR1A = value;
}

void pwm1B(uint16_t value) {
  TCCR1A |= (1<<COM1B1);
  OCR1B = value;
}

void pwm2A(uint8_t value) {
  TCCR2A |= (1<<COM2A1);
  OCR2A = value;
}

void pwm2B(uint8_t value) {
  TCCR2A |= (1<<COM2B1);
  OCR2B = value;
}
