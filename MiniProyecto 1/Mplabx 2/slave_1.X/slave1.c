/*
 * File:   slave1.c
 * Author: galic
 *
 * Created on 22 de febrero de 2021, 03:43 PM
 */

#include"conbits.h"
#include <xc.h>
unsigned char var1;
void __interrupt() intadc(void) {
    if (ADCON0bits.GO == 0) {// reviso que el bit go done termine de convertir
        var1 = ADRESH; //muevo los valores a una variable para luego usarlo
        __delay_us(25);
        PIR1bits.ADIF = 0;
        ADCON0bits.GO_DONE = 1; //espero despues para poder realizar otra conversion
    }
}

void main(void) {
    ADCON();
    SetupS1();
    __delay_us(25);
    ADCON0bits.GO_DONE = 1;
    while (1) {
    }
    return;
}
