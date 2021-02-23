#include "configurator.h"


void confi(void) {
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    PORTA = 0;
    TRISB = 0b00000011;
    PORTB = 0;
    TRISD = 0;
    PORTD = 0;
    TRISE = 0;
    PORTE = 0;
    TRISC = 0;
    PORTC = 0;

}

void int_portb(void) {
    //COSAS INTERRUPCIONES
    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;
    INTCONbits.PEIE = 1;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1; // ENTRADA B1 Y B0
}