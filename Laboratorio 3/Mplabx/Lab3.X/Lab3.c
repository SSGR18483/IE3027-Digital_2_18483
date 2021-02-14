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
int cons;
unsigned char var1;
float voltage1;
int voltage_int1;
float voltage2;
int voltage_int2;
char digits[2];
int i;


void __interrupt() intac(void) {
    //parte 2 obtener el valor del ADC en una variable

    if (ADCON0bits.GO_DONE == 0) {
        // reviso que el bit go done termine de convertir
        if (cons == 0) {
            voltage1 = ADRESH;
        } else if (cons == 1) {
            voltage2 = ADRESH;
        }//muevo los valores a una variable para luego usarlo
        __delay_us(25);
        PIR1bits.ADIF = 0;
        ADCON0bits.GO_DONE = 1;
        //cons++;
        if (cons == 2) {
            cons = 0;
        }
        ADCON0bits.CHS = cons; //espero despues para poder realizar otra conversion
    }

}

void main(void) {
    setup();
    cons = 0;
    intr();
    __delay_us(25);
    Lcd_Init();
    __delay_ms(11);
    ADCL_con();
    ADCON0bits.GO_DONE = 1;
    while (1) {
        if (cons == 0) {
            voltage_int1 = (uint16_t) (((voltage1 * 500) / 255));
            for (i = 0; i < 3; i++) {
                digits[i] = (char) (voltage_int1 % 10);
                voltage_int1 /= 10;
            }
            Lcd_Set_Cursor(1,1);
            sprintf(buffer, "%i.%i%iV", digits[2], digits[1], digits[0]);
            Lcd_Write_String(buffer);
        } else if (cons == 1) {
            voltage_int2 = (uint16_t) (((voltage2 * 500) / 255));
            for (i = 0; i < 3; i++) {
                digits[i] = (char) (voltage_int1 % 10);
                voltage_int2 /= 10;
            }
            Lcd_Set_Cursor(2, 7);
            sprintf(buffer, "%i.%i%iV", digits[2], digits[1], digits[0]);
            Lcd_Write_String(buffer);
        }
    }
}
