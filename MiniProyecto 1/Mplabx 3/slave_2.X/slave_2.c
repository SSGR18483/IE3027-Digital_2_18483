/*
 * File:   slave_2.c
 * Author: galic
 *
 * Created on 22 de febrero de 2021, 09:43 PM
 */


#include <xc.h>
#define _XTAL_FREQ 8000000
#include"configurator.h"
unsigned char CONTL;
unsigned int elc;

void __interrupt() intpb(void) {
    if (INTCONbits.RBIF == 1) {

        if (RB1 == 1) {
            CONTL--;
        } else if (RB0 == 1) {
            CONTL++;
        }
        INTCONbits.RBIF = 0;
    }

    if (PIR1bits.SSPIF) {
        if (SSPSTATbits.BF) {
            elc = SSPBUF;
        }

        SSPBUF = CONTL;
        PIR1bits.SSPIF = 0;
    }

}

void main(void) {
    confi();
    spis2();
    int_portb();
    while (1) {
        PORTD = CONTL;
    }
    return;
}
