/* LIBRERIA TOMADA DE SONSIVRI
 * ADXL345 Accelerometer with Pic 16f877A CCS C Code and PicBasic Pro
 * File:   giros.h
 * Author: galic
 *
 * Created on 14 de marzo de 2021, 09:27 PM
 */

#ifndef GIROS_H
#define	GIROS_H
#include "I2C.h"

void adxl345_write(int add, int data);
int adxl345_read(int add);
void adxl345_init(void);

#endif	/* GIROS_H */

