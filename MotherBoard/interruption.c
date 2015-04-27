/**
  ******************************************************************************
  * @file    interruption.c
  * @author  Pierre-Louis TILAK (4AE-SE) 
  * @version V1.1
  * @date    04-Juin-2014
  * @brief   Gestion des interruptions
  ******************************************************************************
  */
	
/**
  ******************************************************************************
	*	Includes
  ******************************************************************************
  */
 #include "interruption.h"
 /**
  ******************************************************************************
	*	Initialisation des interruptions externes de la carte
  ******************************************************************************
  */
 void init_interrupt(void){

	EXTI_InitTypeDef EXTI_struct;
	NVIC_InitTypeDef NVIC_InitStructure;

/**************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);
	EXTI_StructInit(&EXTI_struct);
	EXTI_struct.EXTI_Line = EXTI_Line13;
	EXTI_struct.EXTI_Mode = EXTI_Mode_Interrupt; 	// Event mode
	EXTI_struct.EXTI_Trigger=EXTI_Trigger_Rising_Falling; // Falling
	EXTI_struct.EXTI_LineCmd=ENABLE;

	EXTI_Init(&EXTI_struct);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

//EXTI_GenerateSWInterrupt(EXTI_Line13);
		/**************************/
	}