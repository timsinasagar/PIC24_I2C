
#include "xc.h"
#include "i2c.h"

void Init_I2C(int BRG)
{
        I2C1BRG = BRG;      //the rate of data transfer PAGE 249
    
        I2C1CONLbits.I2CEN = 1; //enable bit
    
        I2C1CONLbits.I2CSIDL = 0; //continue in idle mode 
    
        I2C1CONLbits.A10M = 0;  //7-bit slave address 
}

void Start_I2C(void)
{
    I2C1CONLbits.SEN = 1; //initiates start condition 
    
    while(I2C1CONLbits.SEN); //wait until start condition finishes 
    
}

void Stop_I2C(void)
{
    I2C1CONLbits.PEN = 1; //initiates stop condition
    
    while(I2C1CONLbits.PEN); //wait until stop condition finishes 
    
}

void Sendbyte_I2C(uint8_t ADDRESS, uint8_t data)
{
    
    Start_I2C();                    //start i2c
    
    while(I2C1STATbits.TBF);        //wait until the buffer is available (not full)
    
    I2C1TRN = ADDRESS; 
    while(I2C1STATbits.TRSTAT);
    
    I2C1TRN = data;                 //assign data to the transmit register
    while(I2C1STATbits.TRSTAT);     //wait for the transfer to complete 
    
    Stop_I2C();                     //stop i2c
}


uint8_t getbyte_I2C(uint8_t address)
{
    // start i2c  
    Start_I2C();
    
    //send the device address byte to the slave with a read indication
    I2C1TRN = address;              //high byte address of the slave address
    while(I2C1STATbits.TRSTAT);     //wait until the transfer is complete 
    I2C1CONLbits.RCEN = 1;          //enable receive mode 
        
    while(I2C1STATbits.ACKSTAT);        //wait for and verify an ack from the slave 
    
    while(I2C1STATbits.RBF == 0);       //wait until the receive is complete 
    
    uint8_t receivedData = I2C1RCV;     //grab the received bit 
    
    I2C1CONLbits.ACKEN = 1;             //Generate an ACK or NACK 
    
    //stop  i2c
    Stop_I2C();
    
    return receivedData;
}
