#ifndef BMP_CONVERTOR_H
#define BMP_CONVERTOR_H

/** MACRO DEFINITON **/

#include <stm32f4xx.h> // ajoute toutes les drivers (CAN, GPIO, I2C...)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ff.h"

/** MACRO DEFINITON **/

#define EMPLACEMENT_OFFSET_PIXEL 10
#define _OPAQUE 0xF0
#define _TRANSPARENT 0x0F
#define OFFSET_LARGEUR 0x12
#define OFFSET_LONGUEUR 0x16
#define COULEUR_TRANSPARENCE 0x00

/** STRUCTURE DEFINITON **/

struct pixel 
{
	uint16_t Red;
	uint16_t Green;
	uint16_t Blue;
	struct pixel * next;
}typedef pixel;

/** FUNCTION DEFINITION **/

struct pixel * new_pixel(uint16_t red, uint16_t green, uint16_t blue);
int Convertion(FIL *filIn, FIL *filOut, uint8_t alpha, pixel *transPixel, int alphaPixelOn);




#endif
