#ifndef SD_H
#define SD_H
	
#include "global.h"
#include "interface.h"
#include "BmpConvertor.h"

	
	/**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */
	
	FRESULT initSD(FATFS* fs32);

	FRESULT openImageFileRead(char nom[100], FIL* fil);
	FRESULT openImageFileWrite(char nom[100], FIL* fil);

	FRESULT closeImageFile(FIL* fil);
	FRESULT readImageFiles(FIL* fil);
	
	FRESULT SD_LoadImage(GPU_Image *image, int dx, int dy, FIL* fil);
	FRESULT SD_LoadImageBmp(GPU_Image *image, char fileNameIn[100], GPU_Layer *layer, int dx, int dy, FRESULT* res, FIL* fil, FATFS* fs32);
	FRESULT SD_LoadImageToLayer(GPU_Layer *layer, int dx, int dy, FIL* fil, char nom[100]);
	
	
	FRESULT SD_StartConvertion(GPU_Image *image, char fileNameIn[100],
	FIL* filIn, FIL* filOut,
	uint8_t alphaBack, uint8_t red, uint8_t green, uint8_t blue, uint8_t alphaPixelOn);

	void SDIO_IRQHandler(void);
	void SD_SDIO_DMA_IRQHANDLER(void);

#endif
