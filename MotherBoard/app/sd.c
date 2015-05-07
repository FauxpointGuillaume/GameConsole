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

FRESULT initSD(FATFS* fs32)
{
	FRESULT res;
	
	SDIO_IRQHandler();
	SD_SDIO_DMA_IRQHANDLER();
	
	memset(fs32, 0, sizeof(FATFS));
	res = f_mount(0, fs32);
	
	return res;
}

	
FRESULT openImageFileRead(char nom[100], FIL* fil)
{		
	FRESULT res;

	memset(fil, 0, sizeof(FIL));

	res = FR_INT_ERR;
	res = f_open(fil, nom , FA_READ );

	while(res != FR_OK)
	{
		res = f_open(fil, nom , FA_READ );
	}

	return res;
}

FRESULT openImageFileWrite(char nom[100], FIL* fil)
{			
	FRESULT res;

	memset(fil, 0, sizeof(FIL));

	res = FR_INT_ERR;
	res = f_open(fil, nom , FA_WRITE | FA_CREATE_NEW);

	while(res != FR_OK)
	{
		res = f_open(fil, nom , FA_WRITE | FA_CREATE_NEW );
		if (res == FR_EXIST)
		{
			res = f_open(fil, nom , FA_WRITE);
		}
	}	
	
	return res;
}

FRESULT closeImageFile(FIL* fil)
{
	return f_close(fil);
}
	
FRESULT readImageFiles(FIL* fil)
{
	static UINT BytesToRead; // nombre d'octets à lire
	UINT BytesRead; // nombre d'octet lus en une fois
	UINT AllBytesRead = 0; // nombre d'octet lus en tout
	
	FRESULT res;

	uint16_t buffer = 0;// = (uint16_t*) CG_RAM; // variable qui va recevoir les données. Adresse a préciser
	BytesToRead = fil->fsize; //pour avoir la taille en octet du fichier
	
	while (AllBytesRead<BytesToRead)
	{
		res = FR_INT_ERR;
		res = f_read(fil, &buffer, 2 , &BytesRead); 

	while(res != FR_OK)
	{
		BytesRead = 0;
		res = f_read(fil, &buffer, 2 , &BytesRead); // pour read et write, penser a modifier le ffconf.h pour les activer				
	}

	//*((uint16_t *) CG_RAM) = buffer;	

	AllBytesRead = AllBytesRead + BytesRead ;
	}

	return res;
}	

FRESULT SD_LoadImage(GPU_Image *image, GPU_Layer *layer, int dx, int dy, FIL* fil)
{
	FRESULT res;
	
/*	if ((res = openImageFileRead(image->name, fil)) != FR_OK)
	{
		return res;
	}*/
	
	GPU_PreSendData(image, dx, dy, layer);
	
	if ((res = readImageFiles(fil)) != FR_OK)
	{
		return res;
	}
	if ((res = closeImageFile(fil)) != FR_OK)
	{
		return res;
	}	
	return res;
}


// Changez cette fonction pour prendre en compte le nom
// du fichier de sortie de l'image
FRESULT SD_StartConvertion(GPU_Image *image, char fileNameIn[100],
	FIL* filIn, FIL* filOut,
	uint8_t alphaBack, uint8_t red, uint8_t green, uint8_t blue, uint8_t alphaPixelOn)
{
	FRESULT res;
	pixel * pixelTransparent = new_pixel(red, green, blue);	
	
	// Ouverture de l'image au format BMP à transferer
	if ((res = openImageFileRead(fileNameIn, filIn)) != FR_OK)
	{
		return res;
	}	
	// Ouverture de l'image qui va être convertit
/*	if ((res = openImageFileWrite(image->name, filOut)) != FR_OK)
	{
		return res;
	}	*/
	
	// Convertion de l'image BMP
	Convertion(filIn, filOut, alphaBack, pixelTransparent, alphaPixelOn);	
	
	// Fermeture des fichiers
	if ((res = closeImageFile(filIn)) != FR_OK)
	{
		return res;
	}
	if ((res = closeImageFile(filOut)) != FR_OK)
	{
		return res;
	}
	
	return res;
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
