/*
 * File:   master.c
 * Author: galic
 *
 * Created on 22 de febrero de 2021, 09:43 PM
 */

#define _XTAL_FREQ 8000000
#include <xc.h>
#include "configuracion.h"
#include "lcd.h"
#include "EUSCON.h"
#include "spimaster.h"
#include<stdint.h>
#include <stdio.h>
char buffer[20];
float divisor;
uint16_t voltage_int1;
char digitos[3];
unsigned int contador2;
int i;
char datos[20];
int incre = 0;
char leer;
unsigned int temperatura;
char hola[25] = "noxd";

void __interrupt() intac(void) {

    if (PIR1bits.TXIF == 1) {
        TXREG = datos[incre];
        //        LCDGoto(0,0);
        //        LCDChar(hola[incre]);
        if (incre == 16) {
            incre = 0;
        } else {
            incre++;
        }
    }
    // sprintf(datos, "%i.%i%iV %i.%i%iV %i\r\n",digitos[2],digitos[1],digitos[0],digitos2[2],digitos2[1],digitos[0],incre2);

}

void main(void) {
    setupm1();
    inter();
    __delay_us(25);
    LCD_Initialize();
    CONUSARTM(9600);
    spiconm();
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    PORTCbits.RC0 = 0;
    PORTCbits.RC1 = 1;
    PORTCbits.RC2 = 1;
    while (1) {
        PORTCbits.RC0 = 0;
        SSPBUF = 1;
        if (!SSPSTATbits.BF) {
            divisor = SSPBUF;
        }
        __delay_ms(2);
        PORTCbits.RC0 = 1;

        PORTCbits.RC1 = 0;
        SSPBUF = 1;
        if (!SSPSTATbits.BF) {
            contador2 = SSPBUF;
        }
        __delay_ms(2);
        PORTCbits.RC1 = 1;
        
        PORTCbits.RC2 = 0;
        SSPBUF = 1;
        if(!SSPSTATbits.BF){
            temperatura = SSPBUF;
        }
        __delay_ms(2);
        PORTCbits.RC2 = 1;
        
        voltage_int1 = (uint16_t) ((((divisor * 500) / 255)));
        for (i = 0; i < 3; i++) {
            digitos[i] = (char) (voltage_int1 % 10);
            voltage_int1 /= 10;
        }
        sprintf(datos, "%i.%i%iV %3i %3i\r\n", digitos[2], digitos[1], digitos[0],contador2,temperatura);
        LCDGoto(0, 0);
        LCDStr(" S1    S2    S3 ");
        LCDGoto(0, 1);
        LCDStr(datos);
    }
}

