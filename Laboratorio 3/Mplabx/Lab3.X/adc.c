/*
 * File:   adc.c
 * Author: galic
 *
 * Created on 10 de febrero de 2021, 10:22 PM
 */


#include"adc.h"
void ADCL_con(void){
    PIE1bits.ADIE = 1;
    ADCON0 = 0b10000001;
    ADCON1 = 0;
    
    
return;
}
