/*
 * File:   mini2.c
 * Author: galic
 *
 * Created on 6 de marzo de 2021, 04:21 PM
 */


#include <xc.h>
#include"CONM2.h"
#include"UART.h"
void main(void) {
    con_mp2();
    COM_EUSART(9600);
    PORTEbits.RE1=1;
    return;
}
