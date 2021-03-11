/*
 * File:   mini2.c
 * Author: galic
 *
 * Created on 6 de marzo de 2021, 04:21 PM
 */


#include <xc.h>
#include"CONM2.h"
#include"UART.h"
#define _XTAL_FREQ 8000000
char leer;
char escribir;
char led1;
char led2;
int cont=0;

void __interrupt() txint(void) {
//    if (cont == 1) {
//        escribir = led1;
//        cont = cont + 1;
//    } else if (cont == 2) {
//        cont = 1;
//        escribir = led2;
//    }
    if (PIR1bits.TXIF == 1) {
        TXREG = escribir;
    }

    if (PIR1bits.RCIF == 1) {
        leer = RCREG;
    }
}

void main(void) {
    con_mp2();
    COM_EUSART(9600);
    while (1) {
//        led1 = PORTEbits.RE0;
//        led2 = PORTEbits.RE1;
        if (leer == 0x01) {
            PORTEbits.RE0 = 0;
        } else if (leer == 0x02) {
            PORTEbits.RE0 = 1;
        } else if (leer == 0x03) {
            PORTEbits.RE1 = 0;
        } else if (leer == 0x04) {
            PORTEbits.RE1 = 1;
        }
        else{
        PORTEbits.RE0 = 0;
        PORTEbits.RE1 = 0;}
    }
    return;
}
