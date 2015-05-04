/**
  ******************************************************************************
  * @file    leds.h
  * @author  Jeremy LAUVIGE (4AE-SE) 
  * @version V0.1
  * @date    03-April-2014
  * @brief  Contient toutes les structures, includes, variables... utiles
	*					au fonctionnement des leds
  ******************************************************************************
  */
	#ifndef __LEDs_H
	#define __LEDs_H
	
	/**
  ******************************************************************************
	*	Includes
  ******************************************************************************
  */
  #include <stm32f4xx.h>
	
	
	/**
  ******************************************************************************
	*	Enumérations
  ******************************************************************************
  */
	enum _Led { LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8 }typedef Led; // de gauche a droite
	enum _Etat_Led { ON, OFF } typedef Etat_Led;
	
	/**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */
	void Initialize_Led(Led Ld);
	void Turn_Led (Led Ld, Etat_Led etat);
	void Toggle_Led(Led LEDx);

	
	#endif
