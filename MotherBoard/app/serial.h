/**
  ******************************************************************************
  * @file    serial.h
  * @author  Gerome (4AE-SE) 
  * @version V0.1
  * @date    03-April-2014
  * @brief   Gestion du port série
  ******************************************************************************
  */
	
	
	#ifndef __SERIAL_H
	#define __SERIAL_H
	
	/**
  ******************************************************************************
	*	Include
  ******************************************************************************
  */
	#include <stm32f4xx.h>
	
		
 /**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */
	
	void Init_Serial_Port(void);
	void NVIC_Configuration(void);
	void RCC_Configuration(void);
	void GPIO_Configuration(void);
	void USART1_Configuration(void);
	
	
	#endif
