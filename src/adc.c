//-------------------------------------------
/*
ADC.c
2013 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

/*
anything that needs to be ran when ever a new conversion happens goes in here
other wise, simply read from the data registers if data isn't all that important
aka: you can miss a few bits of data and still be good to go
*/
ISR(ADC_vect) {
}

void adc_start(_Bool left) {//Passing a 0 will not left align results
  ADCSRA |= (1 << ADPS2)
         | (1 << ADPS1)
         | (1 << ADPS0); // Set ADC prescaler to 128 - 125KHz sample rate @ 16MHz
  ADMUX |= (1 << REFS0); // Set ADC reference to AVCC
  if (left) {
    ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading
  }
  ADCSRA |= (1 << ADATE);
  ADCSRA |= (1 << ADEN);  // Enable ADC
  ADCSRA |= (1 << ADIE);  // Enable ADC Interrupt

  ADMUX &= ~(1 << MUX0)
        &  ~(1 << MUX1)
        &  ~(1 << MUX2)
        &  ~(1 << MUX3);

  ADCSRA |= (1 << ADSC);  // Start A2D Conversions
  #if DEBUG
    uart_sendstr("0x03 - ADC is up...");
  #endif
  return;
}

void adc_stop(void) {
  //stop the ADC
  ADCSRA &= ~(1 << ADSC);
  return;
}

void adc_change(char chan) {
  //stop the ADC
  ADCSRA &= ~(1 << ADSC);
  //and now change the ADMUX bits to fit which channal you want to use
  //sets the MUX0-3 bits inthe ADMUX register
  switch (chan) {
    case 0://binary 0 (reading downwards)
      ADMUX &= ~(1 << MUX0)
            &  ~(1 << MUX1)
            &  ~(1 << MUX2)
            &  ~(1 << MUX3);
      break;
    case 1://binary 1
      ADMUX |=  (1 << MUX0);
      ADMUX &= ~(1 << MUX1)
            &  ~(1 << MUX2)
            &  ~(1 << MUX3);
      break;
    case 2://binary 2
      ADMUX &= ~(1 << MUX0);
      ADMUX |=  (1 << MUX1);
      ADMUX &= ~(1 << MUX2)
            &  ~(1 << MUX3);
      break;
    case 3: //should have the picture by now
      ADMUX |=  (1 << MUX0)
            |   (1 << MUX1);
      ADMUX &= ~(1 << MUX2)
            &  ~(1 << MUX3);
      break;
    case 4:
      ADMUX &= ~(1 << MUX0)
            &  ~(1 << MUX1);
      ADMUX |=  (1 << MUX2);
      ADMUX &= ~(1 << MUX3);
      break;
    case 5:
      ADMUX |=  (1 << MUX0);
      ADMUX &= ~(1 << MUX1);
      ADMUX |=  (1 << MUX2);
      ADMUX &= ~(1 << MUX3);
      break;
    case 6:
      ADMUX &= ~(1 << MUX0);
      ADMUX |=  (1 << MUX1)
            |   (1 << MUX2);
      ADMUX &= ~(1 << MUX3);
      break;
    case 7:
      ADMUX |=  (1 << MUX0)
            |   (1 << MUX1)
            |   (1 << MUX2);
      ADMUX &= ~(1 << MUX3);
      break;
    case 8:
      ADMUX &= ~(1 << MUX0)
            &  ~(1 << MUX1)
            &  ~(1 << MUX2);
      ADMUX |=  (1 << MUX3);
      break;
  }
  //re-enable ADC conversions now that the channel is selected
  ADCSRA |= (1 << ADSC);
  return;
}
