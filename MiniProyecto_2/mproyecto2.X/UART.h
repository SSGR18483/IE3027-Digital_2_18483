/* 
 * File:   UART.h
 * Author: galic
 *
 * Created on 6 de marzo de 2021, 04:23 PM
 */

#ifndef UART_H
#define	UART_H
#define _XTAL_FREQ 8000000

#include<xc.h>
#include<stdint.h>
#include <stdio.h>

void COM_EUSART(const long int baudrate);
#endif	/* UART_H */

