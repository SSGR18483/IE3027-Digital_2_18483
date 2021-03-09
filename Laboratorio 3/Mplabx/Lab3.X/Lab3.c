/*
 * File:   Lab3.c
 * Author: galic
 *
 * Created on 10 de febrero de 2021, 10:10 PM
 */

#include <xc.h>

#define _XTAL_FREQ 8000000
#include "confb.h"
#include"INT.h"
#include"adc.h"
#include "CONFIG.h"
#include "lcd.h"
#include"EUSCON.h"
#include<stdint.h>
#include <stdio.h>
char buffer[20];
char buffer2[20];
int cons;
unsigned char var1;
float voltage1;
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
    //parte 2 obtener el valor del ADC en una variable
    if (PIR1bits.ADIF == 1) {
        // reviso que el bit go done termine de convertir
        fla = 1;
        if (cons == 0) {
            voltage1 = ADRESH;
        } else if (cons == 1) {
            voltage2 = ADRESH;
        }//muevo los valores a una variable para luego usarlo
        cons++;
        PIR1bits.ADIF = 0;
        if (cons == 2) {
            cons = 0;
        }
        ADCON0bits.CHS = cons;
    }

    if (PIR1bits.TXIF == 1) {
        TXREG = datos[incre];
        if (incre == 20) {
            incre = 0;
        } else {
            incre++;
        }
    }
    if (PIR1bits.RCIF == 1) {
        leer = RCREG;
        if (leer == '+') {
            incre2++;
        } else if (leer == '-') {
            incre2--;
        }
    }
    // sprintf(datos, "%i.%i%iV %i.%i%iV %i\r\n",digitos[2],digitos[1],digitos[0],digitos2[2],digitos2[1],digitos[0],incre2);

}

void main(void) {
    setup();
    cons = 0;
    intr();
    __delay_us(25);
    LCD_Initialize();
    ADCL_con();
    ADCON0bits.GO_DONE = 1;
    CONUSART(9600);
    LCDGoto(0, 0);
    LCDStr(" S1:   S2:   S3: ");
    while (1) {
        if (fla == 1) {
            fla = 0;
            sprintf(datos2, "%3i", incre2);
            LCDGoto(12, 1);
            LCDStr(datos2);
            __delay_us(25);
            ADCON0bits.GO_DONE = 1;
        }
        if (cons == 0) {
            voltage_int1 = (uint16_t) ((((voltage1 * 500) / 255) ));
            for (i = 0; i < 3; i++) {
                digitos[i] = (char) (voltage_int1 % 10);
                voltage_int1 /= 10;
            }
            LCDGoto(0, 1);
            sprintf(buffer, "%i.%i%iV", digitos[2], digitos[1], digitos[0]);
            LCDStr(buffer);
        } else if (cons == 1) {
            voltage_int2 = (uint16_t) (((voltage2 * 500) / 255));
            for (i = 0; i < 3; i++) {
                digitos2[i] = (char) (voltage_int2 % 10);
                voltage_int2 /= 10;
            }
            LCDGoto(6, 1);
            sprintf(buffer2, "%i.%i%iV", digitos2[2], digitos2[1], digitos2[0]);
            LCDStr(buffer2);
        }
        sprintf(datos, "%i.%i%iV %i.%i%iV %i\r\n", digitos[2], digitos[1], digitos[0], digitos2[2], digitos2[1], digitos[0], incre2);

    }
}

