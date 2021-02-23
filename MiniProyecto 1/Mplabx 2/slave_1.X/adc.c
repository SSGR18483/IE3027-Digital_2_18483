
#include"adc.h"
void ADCONS(void){
    PIE1bits.ADIE = 1;
    ADCON0 = 0b10000001;
    ADCON1 = 0;
}