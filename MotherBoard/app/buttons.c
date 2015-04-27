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
 #include "buttons.h"
 
	
	/**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */
	
	/**
  * @brief  Initialise le bouton spécifié
  * @param  Button But : bouton spécifié
  * @retval void
  */
	void Initialize_Button(Button But)
	{
		GPIO_InitTypeDef  InitGPIOC;
		GPIO_InitTypeDef  InitGPIOG;
		
		switch(But)
		{
			case USER :
				
				// Activation des clocks
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
				GPIO_StructInit(&InitGPIOG);
				
				// PG15
				InitGPIOG.GPIO_Pin = GPIO_Pin_15;
				InitGPIOG.GPIO_Mode = GPIO_Mode_IN;
				InitGPIOG.GPIO_Speed = GPIO_Speed_2MHz;
				InitGPIOG.GPIO_PuPd = GPIO_PuPd_DOWN;
				GPIO_Init(GPIOG, &InitGPIOG);
			
				break;
			case TAMPER :
				
				// Activation des clocks
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
				GPIO_StructInit(&InitGPIOC);
			
				// PC13
				InitGPIOC.GPIO_Pin = GPIO_Pin_13;
				InitGPIOC.GPIO_Mode = GPIO_Mode_IN;
				InitGPIOC.GPIO_Speed = GPIO_Speed_2MHz;
				InitGPIOC.GPIO_PuPd = GPIO_PuPd_DOWN;
				GPIO_Init(GPIOC, &InitGPIOC);
				
				break;
		}
	}
	
	/**
  * @brief  Utile pour savoir si le bouton spécifié est appuyé ou non
  * @param  Button But : bouton spécifié
  * @retval Boolean : TRUE si le bouton est appuyé, FALSE sinon
  */
	_Boolean_button is_button_pressed(Button But)
	{	
		switch(But){
			case TAMPER :
				if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0){
					return TRUE;
				}else{
					return FALSE;
				}
			case USER :
				if (GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_15) == 0){
					return TRUE;
				}else{
					return FALSE;
				}
		}
		return FALSE;
	}

