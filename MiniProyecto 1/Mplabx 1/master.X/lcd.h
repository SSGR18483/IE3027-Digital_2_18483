/**
    Header File for Module lcd.c

  Company:
    Microchip Technology Inc.

  File Name:
    lcd.h

  Summary:
    This file contains the function prototypes for LCD.

  Description:
    This file contains service prototype definition for LCD access on the PicDem 2 Plus demo board.
*/

/*
Copyright (c) 2013 - 2014 released Microchip Technology Inc.  All rights reserved.
*/

#ifndef _LCD_XC_H
#define	_LCD_XC_H
#define _XTAL_FREQ 8000000
/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
/**
 Section: Macro Definitions
*/
// set up the timing for the LCD delays
#define LCD_delay           5     // ~5mS
#define LCD_Startup         15    // ~15mS

// Command set for Hitachi LM016L LCD display controller
#define LCD_CLEAR           0x01
#define LCD_HOME            0x02
#define LCD_CURSOR_BACK     0x10
#define LCD_CURSOR_FWD      0x14
#define LCD_PAN_LEFT        0x18
#define LCD_PAN_RIGHT       0x1C
#define LCD_CURSOR_OFF      0x0C
#define LCD_CURSOR_ON       0x0E
#define LCD_CURSOR_BLINK    0x0F
#define LCD_CURSOR_LINE2    0xC0

// display controller setup commands from page 46 of Hitachi datasheet
#define FUNCTION_SET        0x38                         // 4 bit interface, 2 lines, 5x8 font
#define ENTRY_MODE          0x06                         // increment mode
#define DISPLAY_SETUP       0x0C                         // display on, cursor off, blink offd

#define LCDLine1()          LCDCmd(LCD_HOME)          // legacy support
#define LCDLine2()          LCDCmd(LCD_CURSOR_LINE2)  // legacy support
#define shift_cursor()      LCDCmd(LCD_CURSOR_FWD)    // legacy support
#define cursor_on()         LCDCmd(LCD_CURSOR_ON)     // legacy support
#define DisplayClr()        LCDCmd(LCD_CLEAR)         // Legacy support


//----------------------------------------------------------------------
// Definitions specific to the PICDEM 2 Plus
// These apply to the Black (2011) version.
//----------------------------------------------------------------------

// single bit for selecting command register or data register
#define instr        0
#define data         1

// These #defines create the pin connections to the LCD in case they are changed on a future demo board
#define LCD_PORT     PORTD
#define LCD_RS       PORTEbits.RE0                     // LCD register select line
#define LCD_EN       PORTEbits.RE1                      // LCD enable
#define LCD_RW       PORTEbits.RE2                      // LCD read/write line


#define NB_LINES    2                                   // Number of display lines
#define NB_COL      16                                  // Number of characters per line

// Function prototypes
/**
  @Summary
    initialize the LCD module

  @Description
    This routine initializes the LCD driver.
    This routine must be called before any other LCD routine is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
*/
void LCD_Initialize(void);
 
 /**
  @Summary
    Writes character to LCD at current cursor position

  @Description
    This function displays the specified ASCII character at current position on the LCD

  @Preconditions
    None

  @Param
    ASCII character to be displayed

  @Returns
    None
*/
void LCDChar(uint8_t ch);

/**
  @Summary
    send an ASCII command to the LCD in instruction mode

  @Description
    This routine writes character to LCD command register

  @Preconditions
    None

  @Param
    ASCII command 

  @Returns
    None
*/
void LCDCmd(uint8_t ch);

/**
  @Summary
    display a string

  @Description
    This routine writes string to LCD at current cursor position

  @Preconditions
    None

  @Param
    Pointer to string

  @Returns
    None
*/
void LCDStr(const char *);                         

/**
  @Summary
    Fuction to write a nibble

  @Description
    This function writes the specified nibble to the LCD.

  @Preconditions
    None

  @Param
    data byte to be written to display

  @Returns
    None
*/
void LCDWrite(uint8_t ch,uint8_t rs);

/**
  @Summary
    Initialization routine that takes inputs from the EUSART GUI.

  @Description
    This function positions the cursor at the specified Line and column.

  @Preconditions
    None

  @Param
    Column and line at which the cursor should be positioned at

  @Returns
    None

  @Comment
      0 <= pos <= 15
      0 <= ln <= 1
*/
void LCDGoto(uint8_t pos, uint8_t ln);

#endif	/* _LCD_XC_H */
