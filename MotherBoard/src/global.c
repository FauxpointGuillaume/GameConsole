/**
  ******************************************************************************
  * @file    global.c
  * @author  Guillaume Fauxpoint
  * @version V0.1
  * @date    14-Mars-2014
  * @brief  Include the SD variable 
  ******************************************************************************
  */

	/**
  ******************************************************************************
	*	Includes
  ******************************************************************************
  */
	
	#include "global.h"
	
	/**
  ******************************************************************************
	*	Variable
  ******************************************************************************
  */
	
	FRESULT res;
	FIL fil;
	FATFS fs32;
	
	FRESULT resBmp;
	FIL filBmp;
	FATFS fs32Bmp;


	/**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */

	/**
  * @brief  Overload the putc function
  * @param  int ch : caractère
	* @param  FILE *f : fichier
  * @retval int ch
  */
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (u8)ch);
    
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    
    return ch;
}
	

