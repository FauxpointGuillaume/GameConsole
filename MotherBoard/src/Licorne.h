#ifndef LICORNE_H
#define LICORNE_H

#include <RTL.h>

#include "interface.h"
#include "buttons.h"
#include "joystick.h"
#include "leds.h"
#include "global.h"

void initGIF(void);
void GIF(GPU_Layer *layer);

__task void taskUnicorn (void);

#endif
