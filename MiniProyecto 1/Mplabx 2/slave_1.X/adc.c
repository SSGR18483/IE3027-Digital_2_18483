
#include"adc.h"
void ADCONS(void){
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.RCIE = 1;
    PIE1bits.TXIE = 1;
    PIE1bits.ADIE = 1;
    ADCON0 = 0b10000001;
    ADCON1 = 0;
}