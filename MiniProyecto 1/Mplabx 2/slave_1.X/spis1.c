#include"spis1.h"

void spicon(void) {
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC5 = 0;
    TRISAbits.TRISA5 = 1;
    SSPCON = 0b00100100;
    SSPSTAT = 0;
    PIE1bits.SSPIE = 1;
    PIR1bits.SSPIF = 0;
}
