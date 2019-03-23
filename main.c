
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "xc.h"

#include "i2c.h"

#define FOSC 8000000        
#define FCY FOSC / 2
#define BRG 78
#define SLAVE_ADDRESS_WRITE 0x10
#define SLAVE_ADDRESS_READ 0x11


int main ( void )
{
    Init_I2C(BRG);      //I2C Initialization
   
    while ( 1 )
    {
        //send 14 to the slave device
        Sendbyte_I2C(SLAVE_ADDRESS_WRITE, 14);
        
        //request a data from the slave device
        uint16_t receivedData = getbyte_I2C(SLAVE_ADDRESS_READ);
        
    }
}

