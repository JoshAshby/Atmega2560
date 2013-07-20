//-------------------------------------------
/*
UART.h
2013 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef UART_H
#define UART_H
#include "global.h"

//-------------------------------------------
//Macros (defines)
//-------------------------------------------
#define BAUD 9600
#define BUFF_LEN 700
#define BAUD_PRESCALE (((F_CPU / (BAUD * 16UL))) - 1)

//-------------------------------------------
//Prototypes
//-------------------------------------------
void uart_start(void);
void uart_sendint(uint8_t data);
void uart_sendint16(uint16_t data);
void uart_sendstr(char *data);
uint8_t uart_get(void);

//-------------------------------------------
//Variables
//-------------------------------------------
char input_buffer[BUFF_LEN];

uint16_t read_spot;


#endif
