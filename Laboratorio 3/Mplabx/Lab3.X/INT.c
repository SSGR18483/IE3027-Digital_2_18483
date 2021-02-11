/*
 * File:   INT.c
 * Author: galic
 *
 * Created on 10 de febrero de 2021, 10:43 PM
 */


#include <xc.h>

void main(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    return;
}
