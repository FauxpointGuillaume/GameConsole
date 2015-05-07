/**
  ******************************************************************************
  * @file    global.h
  * @author  Jeremy LAUVIGE (4AE-SE) 
  * @version V0.1
  * @date    14-Mars-2014
  * @brief  Contient toutes les structures, includes, variables... utiles
	*					au fonctionnement général du systeme 
  ******************************************************************************
  */
	
	#ifndef __GLOBAL_H
	#define __GLOBAL_H
	
	
	/**
  ******************************************************************************
	*	Includes
  ******************************************************************************
  */
	#include <stm32f4xx.h> // ajoute toutes les drivers (CAN, GPIO, I2C...)
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <RTL.h>
	
	/** Includes pour le SDIO **/
	#include "stm32f4_discovery_sdio_sd.h"
	#include "ff.h"
	#include "diskio.h"
	#include "serial.h"
	#include "interface.h"

	#include "sd.h"
	#include "buttons.h"
	#include "joystick.h"
	#include "leds.h"

	/**
  ******************************************************************************
	*	Define
  ******************************************************************************
  */
	
	#define F_CPU 72000000
	#define T_CPU (1/F_CPU)
	
	/**
  ******************************************************************************
	*	Variables
  ******************************************************************************
  */
	
	extern FRESULT res;
	extern FIL fil;
	extern FATFS fs32;
	
	extern FRESULT resBmp;
	extern FIL filBmp;
	extern FATFS fs32Bmp;
	
	extern OS_SEM Sem_Menu;
	
	__task void taskMenu (void);

	
	
	/**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */
	
	int  fputc(int ch, FILE *f);
	
	#endif
