//-------------------------------------------
/*
ADC.h
2013 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef ADC_H
#define ADC_H
#include "global.h"

//-------------------------------------------
//Prototypes
//-------------------------------------------
void adc_start(_Bool left);
void adc_stop(void);
void adc_change(char chan);

#endif
