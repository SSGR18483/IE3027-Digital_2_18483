/*
 * File:   INT.c
 * Author: galic
 *
 * Created on 10 de febrero de 2021, 10:43 PM
 */



#include"INT.h"

void intr(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.RCIE = 1;
    PIE1bits.TXIE = 1;
    

    return;
}
