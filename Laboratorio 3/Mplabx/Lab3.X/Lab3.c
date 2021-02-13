/*
 * File:   Lab3.c
 * Author: galic
 *
 * Created on 10 de febrero de 2021, 10:10 PM
 */

#include <xc.h>

#define _XTAL_FREQ 8000000
#include "confb.h"
#include"INT.h"
#include"adc.h"
#include "CONFIG.h"
#include "lcd.h"


void main(void) {
    setup();
    intr();
    ADCL_con();
    __delay_us(25);
    Lcd_Init();
    __delay_ms(11);
    Lcd_Write_String("hola mundo");

}
