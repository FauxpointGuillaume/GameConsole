/**
  ******************************************************************************
  * @file    ads.c
  * @author  Jeremy LAUVIGE (4AE-SE) 
  * @version V0.1
  * @date    03-April-2014
  * @brief   Gestion des ADCs sur la carte
  ******************************************************************************
  */
	
	/**
  ******************************************************************************
	*	Includes
  ******************************************************************************
  */
 #include "potentiometer.h"
 
 /**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */
	
	/**
  * @brief  Initialise le potentiometre pour qu'il soit prêt a être utilisé
  * @retval void
  */
	void Potentiometer_Init()
	{
		GPIO_InitTypeDef InitGPIOF;
		
		// Enable the ADC interface clock 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE); 

		// Enable the clock for the ADC GPIOs
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		
		GPIO_StructInit(&InitGPIOF);
				
		// Configure this ADC pin (PF9) in analog mode
		InitGPIOF.GPIO_Pin = GPIO_Pin_9;
		InitGPIOF.GPIO_Mode = GPIO_Mode_AN;
	
		GPIO_Init(GPIOF, &InitGPIOF);
		
		ADC3->SQR1   =   0;
		ADC3->SQR2   =   0;
		ADC3->SQR3   =  (7UL <<  0);          /* SQ1 = channel 7                    */
		ADC3->SMPR1  =  (7UL <<  6);          /* Channel 12 sample time is 480 cyc. */
		ADC3->SMPR2  =   0;                   /* Clear register                     */
		ADC3->CR1    =  (1UL <<  8);          /* Scan mode on                       */

		ADC3->CR2   |=  ( 1UL <<  3);         /* Initialize calibration registers   */
		while (ADC3->CR2 & (1UL << 3));       /* Wait for initialization to finish  */
		ADC3->CR2   |=  ( 1UL <<  2);         /* Start calibration                  */
		while (ADC3->CR2 & (1UL << 2));       /* Wait for calibration to finish     */
		
		ADC_EOCOnEachRegularChannelCmd(ADC3, ENABLE);
		ADC_Cmd(ADC3,ENABLE);
	}
	
	/**
  * @brief  Démarre la convertion de l'ADC lié au potentiometre
  * @retval void
  */
	void Potentiometer_Start_Conversion()
	{
	ADC_SoftwareStartConv(ADC3);
	}
	
	/**
  * @brief  Récuprere la valeur calculée par l'ADC
  * @retval uint16_t : valeur convertie
  */
	uint16_t Potentiometer_Get_Conversion_Value()
	{
		return ADC_GetConversionValue(ADC3);
	}
