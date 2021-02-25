/*
 * File:   slave_3.c
 * Author: galic
 *
 * Created on 22 de febrero de 2021, 09:43 PM
 */


#include <xc.h>
#include <stdint.h>
float potem = 0;
unsigned int pruebab = 0;
unsigned int elc; 
int pruebaxd;
uint8_t divisor = 0;
uint16_t temperatura = 0;

#define _XTAL_FREQ 8000000
#include"CONFS3.h"

void __interrupt() intadc(void) {
    if (PIR1bits.ADIF == 1) {// reviso que el bit go done termine de convertir
        divisor = ADRESH;
        pruebab = ADRESH; //muevo los valores a una variable para luego usarlo
        __delay_ms(1);
        PIR1bits.ADIF = 0;
        ADCON0bits.GO_DONE = 1; //espero despues para poder realizar otra conversion
    }
    if (PIR1bits.SSPIF) {
        if (SSPSTATbits.BF) {
            pruebaxd = SSPBUF;
        }
        SSPBUF = divisor;
        PIR1bits.SSPIF = 0;

    }


}

void main(void) {
    setups3();
    spis3();
    __delay_us(40);
    ADCONS3();
    TRISB = 0;
    PORTB = 0;

    ADCON0bits.GO_DONE = 1;
    while (1) {
        PORTB = pruebab;
        temperatura = (uint16_t) (divisor * 2);
        if (temperatura < 25) {
            PORTD = 0b00000001;
        } else if ((temperatura >= 25) && (temperatura <= 36)) {
            PORTD = 0b00000011;
        } else {
            PORTD = 0b00000111;
        }

    }
    return;
}
