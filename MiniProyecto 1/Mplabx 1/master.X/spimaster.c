#include "spimaster.h"

void spiconm(void){
    TRISCbits.TRISC3=0;
    TRISCbits.TRISC5=0;
    SSPCON = 0B00100000;
    SSPSTAT =0;
}
