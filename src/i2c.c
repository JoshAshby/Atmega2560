//-------------------------------------------
/*
I2C.c
2013 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

void twi_start(void) { //set up the clock speed for the I2C/TWI
  TWSR = 0x00;
  TWBR = (F_CPU / 100000UL - 16) / 2;
  #if DEBUG
    uart_sendstr("0x05 - TWI is up...");
  #endif
}

//various different things to help condense code
unsigned char twi_tran(unsigned char type) {
  switch(type) {
     case TWI_START: //Start Condition
       TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
       break;
     case TWI_DATA: //Data
       TWCR = (1 << TWINT) | (1 << TWEN);
       break;
     case TWI_STOP: //Stop Condition
       TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
       return 0;
  }
  while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set in TWCR Register
  return (TWSR & 0xF8); // Return TWI Status Register, mask the prescaler bits (TWPS1,TWPS0)
}

/*
TWI code for writing DAC data to the MCP4725 I2C DAC
First to write to the dac only we must specify this in the POD byte
for DAC only we send 0x40 which is 0b01000000 because we don't want
any of the Power Down stuff and we only want DAC which means C2, C1, C0,
should be 0, 1, 0 respectably. for writing to the DAC and the EEPROM
they would be 0, 1, 1 and the last byte on the address should be 1
*/
int twi_mcp_dac(unsigned int twi_address, uint16_t data, _Bool type) {
    /*
    Pass the address, the 16 bit long data for the DAC/EEPROM
    and either 1 for POD which will write to the EEPROM or 0 to just write to the DAC
    */
    unsigned char n = 0;
    unsigned char twi_status;
    char r_val = -1;
    twi_retry:
        if (n++ >= MAX_TRIES) return r_val;

        //first we must try to start the TWI interface
        twi_status=twi_tran(TWI_START);  //Start Condition
        if (twi_status == TW_MT_ARB_LOST) goto twi_retry;  //TWI Status
        if ((twi_status != TW_START) && (twi_status != TW_REP_START)) goto twi_quit;

        //next we send the slave address, which in this case has 0 to only write to the dac
        TWDR = twi_address | 0;  //Send slave address
        twi_status=twi_tran(TWI_DATA);  //Transmit
        if ((twi_status == TW_MT_SLA_NACK) || (twi_status == TW_MT_ARB_LOST)) goto twi_retry;  //TWSR status
        if (twi_status != TW_MT_SLA_ACK) goto twi_quit;

        //next we send the POD byte which tells the MCP we will only be writing to the DAC and not EEPROM and not in fast mode either
        if (type) {
            TWDR = 0x60;  //Send the POD data
        } else {
            TWDR = 0x40;
        }
        twi_status=twi_tran(TWI_DATA);  //Transmit
        if (twi_status != TW_MT_DATA_ACK) goto twi_quit;  //status

        //next we send the 12bit data in two transfers to get it all across
        TWDR = data;  //Send the first byte of data
        twi_status=twi_tran(TWI_DATA);  //Transmit
        if (twi_status != TW_MT_DATA_ACK) goto twi_quit;  //TWSR status

        //and second part
        TWDR = (data >> 8);  //Send second byte of data
        twi_status=twi_tran(TWI_DATA);  //Transmit
        if (twi_status != TW_MT_DATA_ACK) goto twi_quit;  //TWSR status

        //finally we have to repeat the whole thing over to make sure it got it all according to the datasheet so we do this all again
        if (type) {
            TWDR = 0x60;  //Send the POD data
        } else {
            TWDR = 0x40;
        }
        twi_status=twi_tran(TWI_DATA);  //Transmit
        if (twi_status != TW_MT_DATA_ACK) goto twi_quit;  //TWSR status
        TWDR = data;  //Send the first bytes of Data
        twi_status=twi_tran(TWI_DATA);  //Transmit
        if (twi_status != TW_MT_DATA_ACK) goto twi_quit;  //TWSR status
        TWDR = (data >> 8);  //Send second byte of data
        twi_status=twi_tran(TWI_DATA);  //Transmit
        if (twi_status != TW_MT_DATA_ACK) goto twi_quit;  //TWSR status
        r_val=1;
    twi_quit:
        //and finally stop
        twi_status=twi_tran(TWI_STOP);  //Transmit
        return r_val;
}

uint16_t twi_mcp_read(unsigned int twi_address) {
    /*
    Reads the data stored in the EEPROM and returns it as 16bit long data
    */
    unsigned char n = 0;
    unsigned char twi_status;
    char r_val = -1;
    uint8_t set, first, second, all_first, all_second;
    twi_retry:
        if (n++ >= MAX_TRIES) return r_val;

        //first we must try to start the TWI interface
        twi_status=twi_tran(TWI_START);  //Start Condition
        if (twi_status == TW_MT_ARB_LOST) goto twi_retry;  //TWI Status
        if ((twi_status != TW_START) && (twi_status != TW_REP_START)) goto twi_quit;

        //next we send the slave address, which in this case has 0 to only write to the dac
        TWDR = twi_address | 1;  //Send slave address
        twi_status=twi_tran(TWI_DATA);  //Transmit
        if ((twi_status == TW_MT_SLA_NACK) || (twi_status == TW_MT_ARB_LOST)) goto twi_retry;  //TWSR status
        if (twi_status != TW_MT_SLA_ACK) goto twi_quit;

        set = TWDR;
        mcp_data[0] = set;
        if (twi_status != TW_MT_DATA_ACK) goto twi_quit;

        first = TWDR;
        if (twi_status != TW_MT_DATA_ACK) goto twi_quit;

        second = TWDR;
        mcp_data[1] = (first | (second >> 8));
        if (twi_status != TW_MT_DATA_ACK) goto twi_quit;

        all_first = TWDR;
        if (twi_status != TW_MT_DATA_ACK) goto twi_quit;

        all_second = TWDR;
        mcp_data[2] = (all_first | (all_second >> 8));
        if (twi_status != TW_MT_DATA_ACK) goto twi_quit;
        r_val=1;

    twi_quit:
        //and finally stop
        twi_status=twi_tran(TWI_STOP);  //Transmit
        return r_val;
}
