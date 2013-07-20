//-------------------------------------------
/*
BUTTON.h
2013 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef BUTTON_H
#define BUTTON_H
#include "global.h"

//-----------------------------------------------
//Macros (defines)
//-----------------------------------------------
#define DEBOUNCE_TIME 10

//-----------------------------------------------
//Variables
//-----------------------------------------------
uint8_t dig_count[3];
uint8_t once[3];

//-----------------------------------------------
//Structers and Unions and typedefs
//-----------------------------------------------

//-----------------------------------------------
//Prototypes
//-----------------------------------------------
void button1_once(void);
void button2_once(void);
void button3_once(void);
void button(int which, int what);
void check_buttons(void);
void init_buttons(void);

#endif

