/*
 * File:   Lab2_18483.c
 * Author: galic
 *
 * Created on 1 de febrero de 2021, 11:53 AM
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include<stdint.h>
//#include"ADC.h"
//#include"multiplex.h"
//Variables
#define _XTAL_FREQ 8000000
#define RB1 PORTBbits.RB1
#define RB0 PORTBbits.RB0
#define RA0 PORTAbits.RA0
unsigned char var1;
unsigned char CONTL;
void Setup(void);
void __interrupt() inte(void);
//############################################
//Setup
//############################################

void Setup(void) {
    ANSEL = 0b00000001;
    ANSELH = 0;
    TRISA = 0b00000001;
    PORTA = 0;
    TRISB = 0b00000011;
    PORTB = 0;
    TRISD = 0;
    PORTD = 0;
    TRISE = 0;
    PORTE = 0;
    TRISC = 0;
    PORTC = 0;
    
    //VAR1
    //COSAS INTERRUPCIONES
    //ei();
    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.T0IE = 1;
    INTCONbits.T0IF = 0;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1; // ENTRADA B1 Y B0
    PIE1bits.ADIE = 1;
    CONTL = 0;
    ADCON0 = 0b10000001;
    ADCON1 = 0;
    var1 = 0;
    //OPTION_REG = 0b00000101; //1:32

}
//############################################
//Interrupcion
//############################################

void __interrupt() inte(void) {
    PORTEbits.RE0 = 0;
    if (INTCONbits.RBIF == 1) {

        if (RB1 == 1) {
            CONTL--;
        } else if (RB0 == 1) {
            CONTL++;
        }
        INTCONbits.RBIF = 0;
    }
    //parte 2 obtener el valor del ADC en una variable
    if (ADCON0bits.GO == 0) {// reviso que el bit go done termine de convertir
        var1 = ADRESH; //muevo los valores a una variable para luego usarlo
        __delay_us(25);
        PIR1bits.ADIF = 0;
        ADCON0bits.GO_DONE = 1; //espero despues para poder realizar otra conversion
    }
    return;
    //restadc();
}

void main(void) {
    Setup();
    __delay_us(25);
    ADCON0bits.GO_DONE = 1;
    while (1) {
        PORTD = CONTL;
        //ccomparacion para la alarma 
        if (var1 <= CONTL) {
            PORTE = 0b00000001;
        } else {
            PORTE = 0b00000000;
        }
    }
    return;
}
