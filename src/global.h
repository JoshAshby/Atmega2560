//-------------------------------------------
/*
GLOBAL.h
2013 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef GLOBAL_H
#define GLOBAL_H

//-----------------------------------------------
//Libraries
//-----------------------------------------------
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <compat/twi.h>
#include <inttypes.h>
#include <stdlib.h>
#include <avr/sleep.h>
#include <avr/delay.h>

#include "boot.h"
#include "adc.h"
#include "pwm.h"
#include "i2c.h"
#include "uart.h"
#include "digital.h"
#include "button.h"

//-----------------------------------------------
//Macros (defines)
//-----------------------------------------------
//Debug
//========================
#define DEBUG 1 //if true, anything inside of an if(DEBUG){} or #if DEBUG tag will run, DEBUG_KEYS are sent this way

//CPU power and Debug LEDs
//========================
#define CPU_POW 2 //PORTD

//Status LEDs
//========================
#define stat_led1 5 //PORTD
#define stat_led2 6 //PORTD

//Buttons
//========================
#define button_one 0b00001000 //PORTD pin 3
#define button_two 0b00010000 //PORTD pin 4

//TWI addresses
//========================
#define MCP_ADDRESS 0xC0 //address of the MCP I2C DAC
//addresses of the IGT I2C gyroscope
#define GX_H    0x1D
#define GX_L    0x1E
#define GY_H    0x1F
#define GY_L    0x20
#define GZ_H    0x21
#define GZ_L    0x22

//-----------------------------------------------
//Variables
//-----------------------------------------------
uint8_t led;

//-----------------------------------------------
//Structers and Unions and typedefs
//-----------------------------------------------

//-----------------------------------------------
//Prototypes
//-----------------------------------------------

#endif
