//-------------------------------------------
/*
I2C.h
2013 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef I2C_H
#define I2C_H
#include "global.h"

//-------------------------------------------
//Macros (defines)
//-------------------------------------------
#define MAX_TRIES 50
#define TWI_START 0
#define TWI_DATA 1
#define TWI_STOP 2

//-------------------------------------------
//Prototypes
//-------------------------------------------
void twi_start(void);
unsigned char twi_tran(unsigned char type);
int twi_mcp_dac(unsigned int twi_address, uint16_t data, _Bool type);
uint16_t twi_mcp_read(unsigned int twi_address);

//-------------------------------------------
//Variables
//-------------------------------------------
uint16_t mcp_data[3];

#endif
