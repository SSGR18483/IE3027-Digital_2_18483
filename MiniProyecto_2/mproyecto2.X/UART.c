#include"UART.h"
#define _XTAL_FREQ 8000000
#include<stdint.h>
#include <stdio.h>
void COM_EUSART(const long int baudrate){
    long int p;
    TXSTA = 0b00100000;
    BAUDCTLbits.BRG16 = 0;
    RCSTA= 0b10010000;
    p = (_XTAL_FREQ - baudrate*64)/(baudrate*64);   
    SPBRG = p;
    //error de eusart baudrate
}

