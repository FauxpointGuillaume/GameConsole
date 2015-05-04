#ifndef SOF_H
#define SOF_H

#include <RTL.h>

#include "interface.h"
#include "buttons.h"
#include "joystick.h"
#include "leds.h"


void initSOR(void);
void StreetOfRage(void);
void shortMovieEnding(GPU_Image *image);


__task void taskSOR (void);


#endif

