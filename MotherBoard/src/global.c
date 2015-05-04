/**
  ******************************************************************************
  * @file    global.c
  * @author  Jeremy LAUVIGE (4AE-SE) 
  * @version V0.1
  * @date    14-Mars-2014
  * @brief  Contient toutes les fonctions utiles au fonctionnement g�n�ral 
  ******************************************************************************
  */

/**
  ******************************************************************************
	*	Includes
  ******************************************************************************
  */
	
	#include "global.h"
	
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
  * @brief  red�finition de fputc pour afficher les caract�res envoy�s par le printf sur le port s�rie
  * @param  int ch : caract�re
	* @param  FILE *f : fichier
  * @retval int ch
  */
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (u8)ch);
    
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    
    return ch;
}
	
		/**
  * @brief  fonction de test du sdio
  * @param  FRESULT* res, FIL* fil, FATFS* fs32
  * @retval void
  */


