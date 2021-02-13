/*
 * File:   LCD.c
 * Author: galic
 *
 * Created on 10 de febrero de 2021, 10:42 PM
 */

#include "lcd.h"


//LCD Functions Developed by electroSome
//obtenido de:https://electrosome.com/lcd-pic-mplab-xc8/


void Lcd_Port(char a)
{
    PORTD = a;
//	if(a & 1)
//		D0 = 1;
//	else
//		D0 = 0;
//
//	if(a & 2)
//		D1 = 1;
//	else
//		D1 = 0;
//
//	if(a & 4)
//		D2 = 1;
//	else
//		D2 = 0;
//
//	if(a & 8)
//		D3 = 1;
//	else
//		D3 = 0;
//    if(a & 16)
//        D4 = 1;
//    else
//        D4 = 0;
//    if(a & 32)
//        D5 = 1;
//    else
//        D5 = 0;
//    if(a & 64)
//        D6 = 1;
//    else
//        D6 = 0;
//    if(a & 128)
//        D7 = 1;
//    else
//        D7 = 0;
}
void Lcd_Cmd(char a)
{
	RS = 0;             // => RS = 0
	Lcd_Port(a);
	EN  = 1;             // => E = 1
        __delay_ms(4);
        EN  = 0;             // => E = 0
}

Lcd_Clear()
{
	Lcd_Cmd(0);
	Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b)
{
	char temp;//,z,y;
	if(a == 1)
	{
	  temp = 0x80 + b - 1;
//		z = temp>>4;
//		y = temp & 0x0F;
//		Lcd_Cmd(z);
		Lcd_Cmd(temp);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b - 1;
//		z = temp>>4;
//		y = temp & 0x0F;
//		Lcd_Cmd(z);
		Lcd_Cmd(temp);
	}
}

void Lcd_Init()
{
  Lcd_Port(0x00);
   __delay_ms(20);
  Lcd_Cmd(0x30);
	__delay_ms(5);
  Lcd_Cmd(0x30);
	__delay_ms(15);
  Lcd_Cmd(0x30);
  /////////////////////////////////////////////////////
  Lcd_Cmd(0x30);
  Lcd_Cmd(0x0C);
  Lcd_Cmd(0x01); // cmd de 8 bits
  Lcd_Cmd(0x06);
}

void Lcd_Write_Char(char a)
{
   char temp;//,y;
   temp = a&0xFF;
   //y = a&0xF0;
    //a= a&0xFF;
   RS = 1;             // => RS = 1
   //Lcd_Port(a>>4);             //Data transfer
   //EN = 1;
   //__delay_us(40);
   //EN = 0;
   //Lcd_Port(a);
   Lcd_Port(temp);
   EN = 1;
   __delay_us(40);
   EN = 0;
}

void Lcd_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right()
{
	Lcd_Cmd(0x01);
	Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left()
{
	Lcd_Cmd(0x01);
	Lcd_Cmd(0x08);
}
