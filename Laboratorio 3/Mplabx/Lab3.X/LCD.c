/**
   LCD driver source file

  Company:
    Microchip Technology Inc.

  File Name:
    lcd.c
*/

/*
Copyright (c) 2013 - 2014 released Microchip Technology Inc.  All rights reserved.
*/

/**
  Section: Included Files
*/

#include "lcd.h"


void LCD_Initialize(void){
    // clear latches before enabling TRIS bits
    LCD_PORT = 0;

    TRISD = 0x00;

    // required by display controller to allow power to stabilize
    __delay_ms(LCD_Startup);

    // required by display initialization
    LCDCmd(0x32);

    // set interface size, # of lines and font
    LCDCmd(FUNCTION_SET);

    // turn on display and sets up cursor
    LCDCmd(DISPLAY_SETUP);
    
    DisplayClr();

    // set cursor movement direction
    LCDCmd(ENTRY_MODE);

}


void LCDWrite(uint8_t ch,uint8_t rs){

    // clear the LCD_PORT
    LCD_PORT = (LCD_PORT & 0x00);

    // move onto LCD_PORT
    LCD_PORT = (LCD_PORT | ch);

    // set data/instr bit to 0 = insructions; 1 = data
    LCD_RS = rs;

    // RW - set write mode
    LCD_RW = 0;

    // set up enable before writing nibble
    LCD_EN = 1;

    // turn off enable after write of nibble
    LCD_EN = 0;
}

void LCDChar(uint8_t ch){
    __delay_ms(LCD_delay);

    //Send higher nibble first
    LCDWrite(ch,data);
}

    
void LCDCmd(uint8_t ch){
    __delay_ms(LCD_delay);

    LCDWrite(ch,instr);
    
}

 
void LCDStr(const char *str){
    uint8_t i=0;
    
    // While string has not been fully traveresed
    while (str[i])
    {
        // Go display current char
        LCDChar(str[i++]);
    }
    
}

void LCDGoto(uint8_t pos,uint8_t ln){
    // if incorrect line or column
    if ((ln > (NB_LINES-1)) || (pos > (NB_COL-1)))
    {
        // Just do nothing
        return;
    }

    // LCD_Goto command
    LCDCmd((ln == 1) ? (0xC0 | pos) : (0x80 | pos));

    // Wait for the LCD to finish
    __delay_ms(LCD_delay);
}
/**
 End of File
*/


