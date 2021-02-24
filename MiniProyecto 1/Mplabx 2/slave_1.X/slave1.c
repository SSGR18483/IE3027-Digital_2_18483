/*
 * File:   slave1.c
 * Author: galic
 *
 * Created on 22 de febrero de 2021, 03:43 PM
 */

#include"conbits.h"
#include"adc.h"
#include <xc.h>
#include<stdint.h>
float potem = 0;
int pruebaxd;
uint8_t divisor = 0 ;
#define _XTAL_FREQ 8000000

void __interrupt() intadc(void) {
    if (PIR1bits.ADIF == 1) {// reviso que el bit go done termine de convertir
        potem = ADRESH;
        pruebaxd = ADRESH;//muevo los valores a una variable para luego usarlo
        __delay_us(35);
        PIR1bits.ADIF = 0;
        ADCON0bits.GO_DONE = 1; //espero despues para poder realizar otra conversion
    }
    
    if (PIR1bits.SSPIF){
        if(!SSPSTATbits.BF){
        PORTD = SSPBUF;
        }
        SSPBUF = divisor;
        PIR1bits.SSPIF = 0;
        
    }
    
    
}

void main(void) {
    ADCONS();
    pruebaxd=0;
    SetupS1();
    __delay_us(35);
    ADCON0bits.GO_DONE = 1;
    while (1) {
    }
}
