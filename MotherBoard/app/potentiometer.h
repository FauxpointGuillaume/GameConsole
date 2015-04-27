/**
  ******************************************************************************
  * @file    ADCs.h
  * @author  Jeremy LAUVIGE (4AE-SE) 
  * @version V0.1
  * @date    03-April-2014
  * @brief  Contient toutes les structures, includes, variables... utiles
	*					au fonctionnement des ADCs
  ******************************************************************************
  */
	
	#ifndef __POTENTIOMETER_H
	#define __POTENTIOMETER_H

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
	
	/**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */

	void Potentiometer_Init(void);
	void Potentiometer_Start_Conversion(void);
	uint16_t Potentiometer_Get_Conversion_Value(void);
	
	#endif
