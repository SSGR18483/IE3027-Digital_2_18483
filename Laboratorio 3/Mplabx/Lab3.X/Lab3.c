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
char digits[3];
char digits2[3];
int i;
int fla;

void __interrupt() intac(void) {
    //parte 2 obtener el valor del ADC en una variable
    fla =1;
    if (ADCON0bits.GO_DONE == 0) {
        // reviso que el bit go done termine de convertir
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

}

void main(void) {
    setup();
    cons = 0;
    intr();
    __delay_us(25);
    LCD_Initialize();
    ADCL_con();
    ADCON0bits.GO_DONE = 1;
    LCDGoto(0, 0);
    LCDStr(" S1:   S2:   S3: ");
    while (1) {
        if (fla==1){
            fla=0;
            __delay_us(25);

            ADCON0bits.GO_DONE = 1;
            if (cons == 0) {
                voltage_int1 = (uint16_t) (((voltage1 * 500) / 255));
                for (i = 0; i < 3; i++) {
                    digits[i] = (char) (voltage_int1 % 10);
                    voltage_int1 /= 10;
                }
                LCDGoto(0, 1);
                sprintf(buffer, "%i.%i%iV", digits[2], digits[1], digits[0]);
                LCDStr(buffer);
            } else if (cons == 1) {
                voltage_int2 = (uint16_t) (((voltage2 * 500) / 255));
                for (i = 0; i < 3; i++) {
                    digits2[i] = (char) (voltage_int2 % 10);
                    voltage_int2 /= 10;
                }
                LCDGoto(7, 1);
                sprintf(buffer2, "%i.%i%iV", digits2[2], digits2[1], digits2[0]);
                LCDStr(buffer2);
            }
            //cons++;
        }
    }
}
