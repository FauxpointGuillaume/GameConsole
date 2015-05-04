/**
  ******************************************************************************
  * @file    buttons.c
  * @author  Jeremy LAUVIGE (4AE-SE) 
  * @version V0.1
  * @date    03-April-2014
  * @brief   Gestion des boutons sur la carte
  ******************************************************************************
  */
	
	/**
  ******************************************************************************
	*	Includes
  ******************************************************************************
  */
	
	#include "leds.h"
	
	/**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */


	/**
  * @brief  Permet d'initialiser une led spécifiée
  * @param  Led LEDx : Led spécifiée
  * @retval void
  */
	void Initialize_Led(Led LEDx)
	{

		GPIO_InitTypeDef  InitGPIOG;
		GPIO_InitTypeDef  InitGPIOH;
		GPIO_InitTypeDef  InitGPIOI;
		
		GPIO_StructInit(&InitGPIOG);
		GPIO_StructInit(&InitGPIOH);
		GPIO_StructInit(&InitGPIOI);
		
		switch(LEDx){
			case LED1 :
				// PH03
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);				
				InitGPIOH.GPIO_Pin = GPIO_Pin_3;
				InitGPIOH.GPIO_Mode = GPIO_Mode_OUT;
				InitGPIOH.GPIO_Speed = GPIO_Speed_2MHz;
				InitGPIOH.GPIO_OType= GPIO_OType_PP;
				GPIO_Init(GPIOH, &InitGPIOH);
				break;
			
			case LED2 :
				// PH06
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);				
				InitGPIOH.GPIO_Pin = GPIO_Pin_6;
				InitGPIOH.GPIO_Mode = GPIO_Mode_OUT;
				InitGPIOH.GPIO_Speed = GPIO_Speed_2MHz;
				InitGPIOH.GPIO_OType= GPIO_OType_PP;
				GPIO_Init(GPIOH, &InitGPIOH);
				break;
			
			case LED3 :
				// PH07
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);				
				InitGPIOH.GPIO_Pin = GPIO_Pin_7;
				InitGPIOH.GPIO_Mode = GPIO_Mode_OUT;
				InitGPIOH.GPIO_Speed = GPIO_Speed_2MHz;
				InitGPIOH.GPIO_OType= GPIO_OType_PP;
				GPIO_Init(GPIOH, &InitGPIOH);
				break;
			
			case LED4 :
				// PI10
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
				InitGPIOI.GPIO_Pin = GPIO_Pin_10;
				InitGPIOI.GPIO_Mode = GPIO_Mode_OUT;
				InitGPIOI.GPIO_Speed = GPIO_Speed_2MHz;
				InitGPIOI.GPIO_OType= GPIO_OType_PP;
				GPIO_Init(GPIOI, &InitGPIOI);
				break;
			
			case LED5 :
				// PG06
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
				InitGPIOG.GPIO_Pin = GPIO_Pin_6;
				InitGPIOG.GPIO_Mode = GPIO_Mode_OUT;
				InitGPIOG.GPIO_Speed = GPIO_Speed_2MHz;
				InitGPIOG.GPIO_OType= GPIO_OType_PP;
				GPIO_Init(GPIOG, &InitGPIOG);
				break;
			
			case LED6 :
				// PG07
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
				InitGPIOG.GPIO_Pin = GPIO_Pin_7;
				InitGPIOG.GPIO_Mode = GPIO_Mode_OUT;
				InitGPIOG.GPIO_Speed = GPIO_Speed_2MHz;
				InitGPIOG.GPIO_OType= GPIO_OType_PP;
				GPIO_Init(GPIOG, &InitGPIOG);
				break;
			
			case LED7 :
				// PG08
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
				InitGPIOG.GPIO_Pin = GPIO_Pin_8;
				InitGPIOG.GPIO_Mode = GPIO_Mode_OUT;
				InitGPIOG.GPIO_Speed = GPIO_Speed_2MHz;
				InitGPIOG.GPIO_OType= GPIO_OType_PP;
				GPIO_Init(GPIOG, &InitGPIOG);
				break;
			
			case LED8 :
				// PH07
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);				
				InitGPIOH.GPIO_Pin = GPIO_Pin_2;
				InitGPIOH.GPIO_Mode = GPIO_Mode_OUT;
				InitGPIOH.GPIO_Speed = GPIO_Speed_2MHz;
				InitGPIOH.GPIO_OType= GPIO_OType_PP;
				GPIO_Init(GPIOH, &InitGPIOH);
				break;
			
		}
	}	
	
		/**
  * @brief  Permet d'allumer ou d'éteindre les LEDS
  * @param  Led LEDx : Led spécifiée
	* @param  Etat_Led etat : etat souhaité
  * @retval void
  */
	void Turn_Led (Led LEDx, Etat_Led etat)
	{
		switch(LEDx){
			case LED1 : //PH3
				if (etat == ON){
					GPIO_SetBits(GPIOH, GPIO_Pin_3);
				}else{
					GPIO_ResetBits(GPIOH, GPIO_Pin_3);
				}
				break;
			case LED2 : //PH6
				if (etat == ON){
					GPIO_SetBits(GPIOH, GPIO_Pin_6);
				}else{
					GPIO_ResetBits(GPIOH, GPIO_Pin_6);
				}			
				break;
			case LED3 : //PH7
				if (etat == ON){
					GPIO_SetBits(GPIOH, GPIO_Pin_7);
				}else{
					GPIO_ResetBits(GPIOH, GPIO_Pin_7);
				}			
				break;
			case LED4 : //PI10
				if (etat == ON){
					GPIO_SetBits(GPIOI, GPIO_Pin_10);
				}else{
					GPIO_ResetBits(GPIOI, GPIO_Pin_10);
				}			
				break;
			case LED5 : // PG6
				if (etat == ON){
					GPIO_SetBits(GPIOG, GPIO_Pin_6);
				}else{
					GPIO_ResetBits(GPIOG, GPIO_Pin_6);
				}			
				break;
			case LED6 : // PG7
				if (etat == ON){
					GPIO_SetBits(GPIOG, GPIO_Pin_7);
				}else{
					GPIO_ResetBits(GPIOG, GPIO_Pin_7);
				}			
				break;
			case LED7 : //PG8
				if (etat == ON){
					GPIO_SetBits(GPIOG, GPIO_Pin_8);
				}else{
					GPIO_ResetBits(GPIOG, GPIO_Pin_8);
				}			
				break;
			case LED8 : // PH2
				if (etat == ON){
					GPIO_SetBits(GPIOH, GPIO_Pin_2);
				}else{
					GPIO_ResetBits(GPIOH, GPIO_Pin_2);
				}			
				break;
		}
	}
	
	void Toggle_Led(Led LEDx)
	{
		static enum _Etat_Led preEtat = ON;
		Turn_Led(LEDx, preEtat);
		if (preEtat == ON)
		{
			preEtat = OFF;
		}
		else
		{
			preEtat = ON;
		}
	}
		

