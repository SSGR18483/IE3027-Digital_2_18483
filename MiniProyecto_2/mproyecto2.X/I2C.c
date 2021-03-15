/*
 * LIBRERIA I2C ELABORADA POR ELECTROSOME
 * TOMADA DE :https://electrosome.com/i2c-pic-microcontroller-mplab-xc8/
 * 
 * utilizada por Santiago Galicia
 */
#include "i2c.h"

//MASTER FUNCTIONS
#define _XTAL_FREQ 8000000

void I2C_Master_Init(const unsigned long c)
{
  SSPCON = 0b00101000;            //SSP Module as Master
  SSPCON2 = 0;
  SSPADD = (_XTAL_FREQ/(4*c))-1; //Setting Clock Speed
  SSPSTAT = 0;
  TRISC3 = 1;                   //Setting as input as given in datasheet
  TRISC4 = 1;                   //Setting as input as given in datasheet
}

//FOR WAITING
void I2C_Master_Wait()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
}

//START CONDITION
void I2C_Master_Start()
{
  I2C_Master_Wait();    
  SEN = 1;             //Initiate start condition
}

//STOP CONDITION
void I2C_Master_Stop()
{
  I2C_Master_Wait();
  PEN = 1;           //Initiate stop condition
}

//WRITE DATA
void I2C_Master_Write(int d)
{
  I2C_Master_Wait();
  SSPBUF = d;         //Write data to SSPBUF
}

//READ DATA
int I2C_Master_Read(int a)
{
  int temp;
  I2C_Master_Wait();
  RCEN = 1;
  I2C_Master_Wait();
  temp = SSPBUF;      //Read data from SSPBUF
  I2C_Master_Wait();
  ACKDT = (a)?0:1;    //Acknowledge bit
  ACKEN = 1;          //Acknowledge sequence
  return temp;
}
