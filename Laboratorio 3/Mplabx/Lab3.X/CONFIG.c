/*
 * File:   CONFIG.c
 * Author: galic
 *
 * Created on 10 de febrero de 2021, 10:55 PM
 */


#include"CONFIG.h"

void setup(void) {
    ANSEL = 0b00000011;
    ANSELH = 0;
    TRISA = 0b000000011;
    TRISE =0;
    TRISB = 0;
    TRISD = 0;
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;
    PORTE = 0;


    return;
}
