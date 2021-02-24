/*
 * File:   master.c
 * Author: galic
 *
 * Created on 22 de febrero de 2021, 09:43 PM
 */


#include <xc.h>
#include "configuracion.h"
#include "lcd.h"
#include "EUSCON.h"
#include "spimaster.h"
#include<stdint.h>
#include <stdio.h>
char buffer[20];
char buffer2[20];
int cons;
unsigned char var1;
float divisor;
int voltage_int1;
float voltage2;
int voltage_int2;
char digitos[3];
char digitos2[3];
int i;
int fla;
char datos[20];
int incre = 0;
int incre2 = 0;
char leer;
char datos2[20];

void __interrupt() intac(void) {

    if (PIR1bits.TXIF == 1) {
        TXREG = datos[incre];
        if (incre == 20) {
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
    spiconm();
    cons = 0;
    __delay_us(25);
    LCD_Initialize();
    CONUSARTM(9600);
    LCDGoto(0, 0);
    LCDStr(" S1:   S2:   S3: ");
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
        __delay_ms(5);
        PORTCbits.RC0 = 1;

        voltage_int1 = (uint16_t) ((((divisor * 500) / 255)));
        for (i = 0; i < 3; i++) {
            digitos[i] = (char) (voltage_int1 % 10);
            voltage_int1 /= 10;
        }
    LCDGoto(0, 1);
    sprintf(datos, "%i.%i%iV\r\n", digitos[2], digitos[1], digitos[0]);
    LCDStr(datos);
    }
}

