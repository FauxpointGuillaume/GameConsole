/**
  ******************************************************************************
  * @file    sd.c
  * @author  Jeremy LAUVIGE (4AE-SE) 
  * @version V0.1
  * @date    14-Mars-2014
  * @brief  Contient toutes les fonctions utiles au fonctionnement général 
  ******************************************************************************
  */

/**
  ******************************************************************************
	*	Includes
  ******************************************************************************
  */
	#include "sd.h"

		/**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */



	/**
  * @brief  Envoie une image sur le FPGA
	* @param  char nom[20] : nom du fichier à transferer
  * @param  FRESULT* res
	* @param  FIL* fil
	* @param  FATFS* fs32
  * @retval void
  */
void openImageFiles(char nom[20], FRESULT* res, FIL* fil, FATFS* fs32)
{
			
		SDIO_IRQHandler();
		SD_SDIO_DMA_IRQHANDLER();
		
		memset(fs32, 0, sizeof(FATFS));
		*res = f_mount(0, fs32);

		memset(fil, 0, sizeof(FIL));
	
		*res = FR_INT_ERR;
		*res = f_open(fil, nom , FA_READ );
	
		while(*res != FR_OK)
		{
			*res = f_open(fil, nom , FA_READ );
		}
		
}
	
void readImageFiles(FRESULT* res, FIL* fil, FATFS* fs32)
{
	static UINT BytesToRead; // nombre d'octets à lire
	UINT BytesRead; // nombre d'octet lus en une fois
	UINT AllBytesRead = 0; // nombre d'octet lus en tout

	uint16_t buffer = 0;// = (uint16_t*) CG_RAM; // variable qui va recevoir les données. Adresse a préciser
	BytesToRead = fil->fsize; //pour avoir la taille en octet du fichier
	AllBytesRead = 0;


	while (AllBytesRead<BytesToRead)
	{
		*res = FR_INT_ERR;
		*res = f_read(fil, &buffer, 2 , &BytesRead); 

	while(*res != FR_OK)
	{
		BytesRead = 0;
		*res = f_read(fil, &buffer, 2 , &BytesRead); // pour read et write, penser a modifier le ffconf.h pour les activer				
	}

	*((uint16_t *) CG_RAM) = buffer;
	
	Wait(1000);
	GPU_MAJ_PLAN();

	AllBytesRead = AllBytesRead + BytesRead ;

	}		
}	



	
	
		/**
  * @brief  Interruption sur détection de la carte SD
  * @param  void
  * @retval void
  */
void SDIO_IRQHandler(void)
{
	SD_ProcessIRQSrc();
}

		/**
  * @brief  Interruption sur la fin du transfert de la SD
  * @param  void
  * @retval void
  */
void SD_SDIO_DMA_IRQHANDLER(void)
{
	SD_ProcessDMAIRQ();
}
