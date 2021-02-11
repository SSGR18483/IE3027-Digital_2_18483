/*
 * File:   adc.c
 * Author: galic
 *
 * Created on 10 de febrero de 2021, 10:22 PM
 */


#include <xc.h>
#include<stdint.h>
void ADCL_int(void){
    PIE1bits.ADIE = 1;
    ADCON0 = 0b10000001;
    ADCON1 = 0;
    var1 = 0;
    
return;
}
