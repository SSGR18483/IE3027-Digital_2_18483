/*
 * File:   Lab_1_18483.c
 * Author: galic
 *
 * Created on 31 de enero de 2021, 09:46 PM
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
//Variables
#define _XTAL_FREQ 8000000
//clock a 8MHz como en proteus
#define VER PORTBbits.RB2
#define Yel PORTBbits.RB1
#define Red PORTBbits.RB0
#define RA0 PORTAbits.RA0
#define RA1 PORTAbits.RA1
#define RA2 PORTAbits.RA2
int Win = 0;
int J1 = 1;
int J2 = 1;
int Cont(unsigned int Con);
//Definir las funciones
void Setup(void);
void Iniciador(void);
//añado el setup

void Setup(void) {
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0b00000111; //inputs analogicos
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
}

//Parte 1 funcionalidad del semaforo de inicio

void Iniciador(void) {
    J1 = 1;
    J2 = 1;
    Win = 0;
    Red = 1;
    __delay_ms(500);
    Yel = 1;
    __delay_ms(500);
    VER = 1;
    __delay_ms(500);
    Red = 0;
    Yel = 0;
    VER = 0;

}
//Parte 2 Incremento contador

int Cont(unsigned int Con) {
    if (Con == 1) {
        while (1) {
            if (RA1 == 1) {
                __delay_ms(25);
                if (RA1 == 0) {
                    PORTC = J1;
                    J1 = J1 << 1;
                    if (J1 == 0) {
                        return (1);
                    } else {
                    }


                } else {
                }
            } else {
            }
            if (RA2 == 1) {
                __delay_ms(25);
                if (RA2 == 0) {
                    PORTD = J2;
                    J2 = J2 << 1;
                    if (J2 == 0) {
                        return (2);
                    } else {
                    }

                } else {
                }
            } else {
            }

        }

    } else {
    }




}
//Programa Principal // parte 3 xd

void main(void) {
    Setup();
    while (1) {
        if (RA0 == 1) {
            __delay_ms(10);
            if (RA0 == 0) {
                Iniciador();
                Win = Cont(1);
                if (Win == 1) {
                    PORTEbits.RE0 = 1;
                } else if (Win == 2) {
                    PORTEbits.RE1 = 1;
                } else {
                    PORTE = 0b00000011;
                }
            } else {
            }
        } else {
        }
    }

}
