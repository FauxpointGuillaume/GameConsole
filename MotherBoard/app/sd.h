	/**
  ******************************************************************************
  * @file    sd.h
  * @author  Jeremy LAUVIGE (4AE-SE) 
  * @version V0.1
  * @date    12-May-2014
  * @brief  Contient toutes les références des fonctions utiles concernant la carte SD 
  ******************************************************************************
  */

#ifndef sd
#define sd

#include "interface.h"
#include "global.h"

		
		//const uint32_t addr_jeu = 0x08008000;
		
		/* Bargraph position definitions */
		#define BAR_ST      (8*6+3)
		#define BAR_LEN     (217)
		#define BAR_HGT     (20)
		#define BAR_LN(ln)  ((ln)*24)
		
/**
  ******************************************************************************
	*	Structures
  ******************************************************************************
  */
	struct _SD_Ressources {
		
	char ** liste_img ; // tableau qui contient le nom des images a récupérer sur la carte SD
	int nb_img;

} typedef SD_Ressources;
	
	/**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */
	

  void openImageFiles(char nom[20], FRESULT* res, FIL* fil, FATFS* fs32);
	void readImageFiles(FRESULT* res, FIL* fil, FATFS* fs32);


	void SDIO_IRQHandler(void);
	void SD_SDIO_DMA_IRQHANDLER(void);

#endif

