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
int leer;
char escribir;
char led1;
char giros[6];
char led2;
int cont = 0;
int num;

void __interrupt() txint(void) {
    //    if (cont == 1) {
    //        escribir = led1;
    //        cont = cont + 1;
    //    } else if (cont == 2) {
    //        cont = 1;
    //        escribir = led2;
    //    }
    //  PORTDbits.RD2 =1;
    if (PIR1bits.TXIF == 1) {
        TXREG = escribir;
        if (num == 5) {
            num = 0;
        } else {
            num++;
        }
    } else {
        TXREG = 66;
    }


    if (PIR1bits.RCIF == 1) {
        leer = RCREG;
        // PORTDbits.RD2 = 0;
        //__delay_ms(500);
    }
}

void main(void) {
    con_mp2();
    COM_EUSART(9600);
    while (1) {
        //        led1 = PORTEbits.RE0;
        //        led2 = PORTEbits.RE1;
        if (leer == 1) {
            PORTEbits.RE0 = 0;
        }
        if (leer == 2) {
            PORTEbits.RE0 = 1;
        }
        if (leer == 3) {
            PORTEbits.RE1 = 0;
        }
        if (leer == 4) {
            PORTEbits.RE1 = 1;
        }
        giros[0] = adxl345_read(0x32);
        giros[1] = adxl345_read(0x33);
        giros[2] = adxl345_read(0x34);
        giros[3] = adxl345_read(0x35);
        giros[4] = adxl345_read(0x36);
        giros[5] = adxl345_read(0x37);
    }
    return;
}
