#include "interface.h"

/**
  ******************************************************************************
	*	VARIABLE GLOBALE
  ******************************************************************************
  */

 GPU_Plane_conf PLANE;

 GPU_Plane Plane_One;
 GPU_Plane Plane_Two;
 GPU_Plane Plane_Three;
 GPU_Plane Plane_Four;
	

/**
  ******************************************************************************
	*	DRIVERS
  ******************************************************************************
  */
	
/**** Procedure d'attente ****/

void Wait(int delay)
{
	delay = (delay > 0) ? delay : 1000;
	while(delay--);
}
		

/**** Procedure d'initialisation du FSMC ****/

int GPU_initFSMC()
{
	
//3. Declaration de la structure de configuration
	GPIO_InitTypeDef  GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef FSMC_ReadWriteTimingStructure;
	FSMC_NORSRAMTimingInitTypeDef FSMC_WriteTimingStructure;

//1. Enable the clock
	
	// Activation de la clock du FSMC
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
	
	// Activation des clocks des GPIOs utilisés par le FSMC
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	
//2. Mettre les pins en configuration FSMC
	
	// Pins d'addressage
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0, GPIO_AF_FSMC);	// A0   OU RS dans le cas du LCD

	// Pins de données
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);	// D15
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);	// D14
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);	// D13
	
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FSMC);	// D12
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FSMC);	// D11
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FSMC);	// D10
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FSMC);	// D9
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FSMC);	// D8
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FSMC);	// D7
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_FSMC);	// D6
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_FSMC);	// D5
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_FSMC);	// D4
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);	// D3
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);	// D2
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);	// D1
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);	// D0
	
	// Pins de commande

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);	// WE  (WR/SCL dans le cas du LCD)
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);	// OE	 (RD dans le cas LCD)
	
		
	// Pins Chip Select 

	GPIO_PinAFConfig(GPIOG, GPIO_PinSource12, GPIO_AF_FSMC);  // Chip select du LCD, NE


	/*============== Configure les pins d'adressages ==============*/

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	// Port D

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_15 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_5 | GPIO_Pin_4 ;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// PORT E
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4  ;
	GPIO_InitStructure.GPIO_Pin |=  GPIO_Pin_7|GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	// Port G
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  // Rajout de la pin 12 pour prendre en compte le LCD
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	// Port F
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOF, &GPIO_InitStructure);


//5. Configuration de la structure du FSMC

//Configuration de l'interface CG comme une SRAM en mode asynchrone, mode 1 write ace*cesses


	// ================= Initialisation de la structure ========================= //
  FSMC_NORSRAMStructInit(&FSMC_NORSRAMInitStructure);
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = (FSMC_NORSRAMTimingInitTypeDef*)&FSMC_ReadWriteTimingStructure;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = (FSMC_NORSRAMTimingInitTypeDef*)&FSMC_WriteTimingStructure;
	
	// Configuration de la structure FSMC	
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4; // LCD = BANK 1 sous banque 4
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable; 					//Bit 15 A voir si utilisable
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;									//Bit 14
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;											//Bit 19

	// Configuration de la structure de timings //
	
	FSMC_ReadWriteTimingStructure.FSMC_AddressSetupTime = GPU_FSMC_ADDSET;
	FSMC_ReadWriteTimingStructure.FSMC_AddressHoldTime = 1; // Don't care
	FSMC_ReadWriteTimingStructure.FSMC_DataSetupTime = GPU_FSMC_DATAST;
	FSMC_ReadWriteTimingStructure.FSMC_BusTurnAroundDuration = GPU_FSMC_BUSTURN;
	FSMC_ReadWriteTimingStructure.FSMC_CLKDivision = 1; // Don't care
	FSMC_ReadWriteTimingStructure.FSMC_DataLatency = 1; // Don't care
	FSMC_ReadWriteTimingStructure.FSMC_AccessMode = FSMC_AccessMode_A; // Don't care
	 

	FSMC_WriteTimingStructure.FSMC_AddressSetupTime = GPU_FSMC_ADDSET;
	FSMC_WriteTimingStructure.FSMC_AddressHoldTime = 1; // Don't care
	FSMC_WriteTimingStructure.FSMC_DataSetupTime = GPU_FSMC_DATAST;
	FSMC_WriteTimingStructure.FSMC_BusTurnAroundDuration = GPU_FSMC_BUSTURN;
	FSMC_WriteTimingStructure.FSMC_CLKDivision = 1; // Don't care
	FSMC_WriteTimingStructure.FSMC_DataLatency = 1; // Don't care
	FSMC_WriteTimingStructure.FSMC_AccessMode = FSMC_AccessMode_A; // Don't care

//4. Initialisation de cette structure

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

//5. Enable de cette structure 

	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);

	return 0;
}


// Permet la configuration de la clock du FSMC en fonction de celle du system
// Prend en argument les puissances de 2 jusqu'a 512 execpté 32

int GPU_setClockFSMC(int a)
{
 	switch (a)
	{
		case 1 :
			RCC_HCLKConfig(RCC_SYSCLK_Div1);
			break ;
		case 2 :
			RCC_HCLKConfig(RCC_SYSCLK_Div2);
			break ;
		case 4 :
			RCC_HCLKConfig(RCC_SYSCLK_Div4);
			break ;
		case 8 :
			RCC_HCLKConfig(RCC_SYSCLK_Div8);
			break ;
		case 16 :
			RCC_HCLKConfig(RCC_SYSCLK_Div16);
			break ;
		case 64 :
			RCC_HCLKConfig(RCC_SYSCLK_Div64);
			break ;
		case 128 :
			RCC_HCLKConfig(RCC_SYSCLK_Div128);
			break ;
		case 256 :
			RCC_HCLKConfig(RCC_SYSCLK_Div256);
			break ;
		case 512 :
			RCC_HCLKConfig(RCC_SYSCLK_Div512);
			break ;
	
	}
	
	return 0;
}


/**** Procédure SD *****/



int GPU_init_SD()
{
	//Init_Serial_Port();		
	//envoyer_donnees_fpga("Sof.bin", &res, &fil, &fs32);
	
	/*NVIC_InitTypeDef NVIC_InitStructure;
	
	SD_Init(); // Initialization Step as described in section A
	
	// SDIO Interrupt ENABLE
	NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// DMA2 STREAMx Interrupt ENABLE
	NVIC_InitStructure.NVIC_IRQChannel = SD_SDIO_DMA_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
		//- Add the SDIO and DMA2 StreamX (3 or 6) IRQ Handlers:*/

	return 0;
}

/*
void SDIO_IRQHandler(void)
{
	 SD_ProcessIRQSrc();
 }
 void SD_SDIO_DMA_IRQHANDLER(void)
 {
	 SD_ProcessDMAIRQ();
 }*/
int GPU_SD_TO_US (int name_file)
{
	int Status;
	
	// Read operation as described in Section B
		
	Status = SD_ReadBlock((uint8_t *)CG_RAM, 0x0000000, 512);
	Status = SD_WaitReadOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);

	/*Status = SD_ReadMultiBlocks(buffer, address, 512, NUMBEROFBLOCKS);
	Status = SD_WaitReadOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);*/
	
	return Status;
}
	
								 
	
	
	
/**** Procédure DMA *****/	

// Configuration de DMA

int GPU_init_DMA()
{
	DMA_InitTypeDef DMA_InitStructure; 

	
	// cf Page 1016
	
	// Partie une
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
	// Partie deux; Configurer le LCD pour qu'il soit CO au DMA, SD + FSMC
	
	// Nothing
	
	// Partie trois configuration des paramètres	
	

  DMA_DeInit(DMA2_Stream3);
  while(DMA_GetCmdStatus(DMA2_Stream3) != DISABLE);

  DMA_InitStructure.DMA_Channel = DMA_Channel_4;
  DMA_InitStructure.DMA_PeripheralBaseAddr = SDIO_FIFO_ADDRESS;
  DMA_InitStructure.DMA_Memory0BaseAddr = CG_RAM;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = (uint32_t) (32);
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_INC8;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_INC8;

  DMA_Init(DMA2_Stream3, &DMA_InitStructure);

  /* 4. Enable the NVIC and the corresponding interrupt(s)
   using the function DMA_ITConfig() if you need to use DMA interrupts.*/
  DMA_ITConfig(DMA2_Stream3, DMA_IT_TC, ENABLE);

  /* 5. Optionally, if the Circular mode is enabled, you can use the
  Double buffer by configuring the second Memory address and the
  first Memory to be used through the function DMA_DoubleBufferModeConfig().
  Then enable the Double buffer mode through the function
  DMA_DoubleBufferModeCmd(). These operations must be done before step 6.*/

  /* 6. Enable the DMA stream using the DMA_Cmd() function. */
  DMA_Cmd(DMA2_Stream3, ENABLE);
	
	return 0;
}
	
/**** Procédure de lecture des GPIOS necessaire au transfert *****/

//On prend PC7 pour l'attente du passage à 0;

int GPU_init_GPIO_interface() // Pour l'instant n'init que les GPIOS, à voir si séparation du bloc init fsmc
{
	
	// Initialisation du GPIO PB8 en mode GP in
	GPIO_InitTypeDef InitGPIOC;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_StructInit(&InitGPIOC);
	
	InitGPIOC.GPIO_Pin = GPIO_Pin_7;
	InitGPIOC.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOB, &InitGPIOC );
		
	return 0;
}
	
// Signal Busy mettant en attente le transfert

uint8_t GPU_read_GPIO_busy()
	{
		return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7);
	}
	
/**** Procédure d'écriture et de lecture d'un champ de DATA pour les registre et la RAM *****/

int ecriture_registre(uint16_t data)
	{
	volatile uint16_t *ptr;
	ptr = (uint16_t *)CG_REG;
		
	*ptr = data;	
	//CG_REG16 = data;

	
	return 0;
}
	
uint16_t lecture_registre()
	{
	volatile uint16_t *ptr;
	uint16_t data;	
		
	
	ptr = (uint16_t *)CG_REG;
	
	data = ptr[0];
	
	return data;
}

/**** Procédure d'écriture et de lecture pour les registres *****/

int GPU_WriteReg(uint16_t registre, uint32_t data)
{
	while( GPU_read_GPIO_busy() !=0){};
	// Cycle Adresse, Wait BG, Data, Data
	ecriture_registre(registre);
	while( GPU_read_GPIO_busy() !=0){};
	ecriture_registre( (uint16_t) (data & 0x0000FFFF));
	while( GPU_read_GPIO_busy() !=0){};
	ecriture_registre( (uint16_t) ((data & 0xFFFF0000) >> 16));
			
	return 0;
	
}



uint32_t GPU_ReadReg(uint16_t registre)
{
	uint32_t data = 0x00000000;

	while( GPU_read_GPIO_busy() !=0){};
	// Cycle Adresse, Wait BG, Data, Data
	ecriture_registre(registre);
	while( GPU_read_GPIO_busy() !=0){};	
	// Lecture des 16 premiers bits de poids faible
	data = lecture_registre();
	while( GPU_read_GPIO_busy() !=0){};
			// Lecture des 16 premiers bits de poids fort
	data |= lecture_registre()  << 16;
		

	return data;
}




/**
  ******************************************************************************
	*	SERVICES
  ******************************************************************************
  */

/***** Création d'une structure d'une image *****/

int GPU_NewImage(GPU_Image * image,uint32_t Width,uint32_t Height, char * nom,uint32_t Addr)
{
	//uint32_t addr = Addr + Width + Height*addr;
	
	image->Nom = (char *)malloc(sizeof(strlen(nom)));
	strcpy(image->Nom,(const char *) nom);
	
	image->Height = Height;
	image->Width = Width;
	image->Adresse = Addr;
		
	return 0;
}



/***** Creation d'un pixel de couleur *****/


int GPU_NewColor(GPU_Color *color,int rouge, int vert, int bleu, int alpha)
{
	color->R = rouge;
	color->G = vert;
	color->B = bleu;
	color->A = alpha;
	
	return 0;
}



/***** Send data for struct PLAN *****/

int GPU_InitPlan(int NumPlan)
{
	switch (NumPlan)
	{
		case 1 :
			Plane_One.numero = 1;
			Plane_One.Addr = 0;
			Plane_One.Plane_Width = 0;
			Plane_One.Plane_Height = 0;
			Plane_One.ScrollDx = 0;
			Plane_One.ScrollDy = 0;
			break;
		case 2 :
			Plane_Two.numero = 2;
			Plane_Two.Addr = 0;
			Plane_Two.Plane_Width = 0;
			Plane_Two.Plane_Height = 0;
			Plane_Two.ScrollDx = 0;
			Plane_Two.ScrollDy = 0;
			break;
		case 3 :
			Plane_Three.numero = 3;
			Plane_Three.Addr = 0;
			Plane_Three.Plane_Width = 0;
			Plane_Three.Plane_Height = 0;
			Plane_Three.ScrollDx = 0;
			Plane_Three.ScrollDy = 0;
			break;
		case 4 :
			Plane_Four.numero = 4;
			Plane_Four.Addr = 0;
			Plane_Four.Plane_Width = 0;
			Plane_Four.Plane_Height = 0;
			Plane_Four.ScrollDx = 0;
			Plane_Four.ScrollDy = 0;
			break;
		default :
			break;
	}
	return 0;
}

int GPU_MAJ_PLAN()
{
	uint32_t data;
	
	data = (PLANE.Enable & 0x1) + ((PLANE.Test_On & 0x1) << 1) + ((PLANE.Plan_Enable & 0xF) << 2) + ((PLANE.Alpha_On & 0x1) << 6);
	
	GPU_WriteReg(FBCTRL,data);
	
	return 0;
}




/***** Groupe Init/Config *****/

	// Initialisation de la CG (Voir les registre mis en jeu)

int GPU_Init()
{
	GPU_init_GPIO_interface();
	GPU_initFSMC();
	//GPU_init_SD();
	
	GPU_setClockFSMC((int) GPU_DIVISION_CLOCK_FSMC);
	
	GPU_InitPlan(1);
	GPU_InitPlan(2);
	GPU_InitPlan(3);
	GPU_InitPlan(4);

	GPU_MAJ_PLAN();
	
	GPU_HScroll (Plane_One, 0,1);
	GPU_VScroll (Plane_One, 0,1);
	
	GPU_HScroll (Plane_Two, 0,1);
	GPU_VScroll (Plane_Two, 0,1);
	
	GPU_HScroll (Plane_Three, 0,1);
	GPU_VScroll (Plane_Three, 0,1);
	
	GPU_HScroll (Plane_Four, 0,1);
	GPU_VScroll (Plane_Four, 0,1);
		
	
	return 0;
}


// Configuration des différents plans

int GPU_ConfigurePlane (GPU_Plane plane, uint32_t planeBaseAddr, uint32_t planeWidth, uint32_t planeHeight)
{
		
	
		switch (plane.numero)
		{
		case 1 :
			Plane_One.Addr = planeBaseAddr;
			Plane_One.Plane_Width = planeWidth;
			Plane_One.Plane_Height = planeHeight;
		
			GPU_WriteReg(FBP1ADDR,planeBaseAddr);
			GPU_WriteReg(FBP1SIZE,(planeWidth & 0xFFFF) + ((planeHeight & 0xFFFF) << 16));
			break;
		case 2 :
			Plane_Two.Addr = planeBaseAddr;
			Plane_Two.Plane_Width = planeWidth;
			Plane_Two.Plane_Height = planeHeight;
		
			GPU_WriteReg(FBP2ADDR,planeBaseAddr);
			GPU_WriteReg(FBP2SIZE,(planeWidth & 0xFFFF) + ((planeHeight & 0xFFFF) << 16));
			break;
		case 3 :
			Plane_Three.Addr = planeBaseAddr;
			Plane_Three.Plane_Width = planeWidth;
			Plane_Three.Plane_Height = planeHeight;
		
			GPU_WriteReg(FBP3ADDR,planeBaseAddr);
			GPU_WriteReg(FBP3SIZE,(planeWidth & 0xFFFF) + ((planeHeight & 0xFFFF) << 16));
			break;
		case 4 :
			Plane_Four.Addr = planeBaseAddr;
			Plane_Four.Plane_Width = planeWidth;
			Plane_Four.Plane_Height = planeHeight;
		
			GPU_WriteReg(FBP4ADDR,planeBaseAddr);
			GPU_WriteReg(FBP4SIZE,(planeWidth & 0xFFFF) + ((planeHeight & 0xFFFF) << 16));
			break;
		}
	
				
		return 0;
	
}
	
	// Choix du mode LCD ou VGA 

int GPU_ConfigureOutput(int choix) //VGA = 1, LCD = 0
{
	switch (choix)
	{
		case MODE_VGA :
			GPU_WriteReg(DCMODE,MODE_VGA);
		break;
		
		case MODE_LCD :
			GPU_WriteReg(DCMODE,MODE_LCD);
		break;
		
		default :
		break;
	}
	
	return 0;
}

// Test de la CG

int GPU_VideoSignalTest (uint32_t testOn)
{
	PLANE.Test_On = testOn;
	
	GPU_MAJ_PLAN();
	
	return 0;
}


/***** Group : Display control *****/

int disable_FB()
{
	GPU_WriteReg(FBCTRL,0x00000000);
	
	return 0;
}

// Activation des différents plans

int GPU_PlaneeEnable (uint32_t planeFlags)
{
	PLANE.Plan_Enable = planeFlags;
	
	GPU_MAJ_PLAN();
	
	return 0;
	
}

// Mis à jour du scrolling horizontal

int GPU_HScroll (GPU_Plane plane, uint32_t dX, int sens)
{
	
	switch (plane.numero)
	{
		case 1 :
			if ((dX + Plane_One.ScrollDx > Plane_One.Plane_Width - SCREEN_WIDTH) && sens == 1)
			{
				Plane_One.ScrollDx = Plane_One.Plane_Width - SCREEN_WIDTH;
			}
			else
			{
				if ((dX > Plane_One.ScrollDx ) && sens == 0)
				{
					Plane_One.ScrollDx = 0;
				}
				else
				{
					if (sens == 1)
					{
						Plane_One.ScrollDx = Plane_One.ScrollDx + dX;
					}
					else
					{
						Plane_One.ScrollDx = Plane_One.ScrollDx - dX;
					}
				}
			}
		
			GPU_WriteReg(FBP1SCRL ,(Plane_One.ScrollDx & 0xFFFF));
			break;
		case 2 :
			if ((dX + Plane_Two.ScrollDx > Plane_Two.Plane_Width - SCREEN_WIDTH) && sens == 1)
			{
				Plane_Two.ScrollDx = Plane_Two.Plane_Width - SCREEN_WIDTH;
			}
			else
			{
				if ((dX > Plane_Two.ScrollDx ) && sens == 0)
				{
					Plane_Two.ScrollDx = 0;
				}
				else
				{
					if (sens == 1)
					{
						Plane_Two.ScrollDx = Plane_Two.ScrollDx + dX;
					}
					else
					{
						Plane_Two.ScrollDx = Plane_Two.ScrollDx - dX;
					}
				}
			}
			 
			GPU_WriteReg(FBP2SCRL ,(Plane_Two.ScrollDx & 0xFFFF));
			break;
		case 3 :
			if ((dX + Plane_Three.ScrollDx > Plane_Three.Plane_Width - SCREEN_WIDTH) && sens == 1)
			{
				Plane_Three.ScrollDx = Plane_Three.Plane_Width - SCREEN_WIDTH;
			}
			else
			{
				if ((dX > Plane_Three.ScrollDx ) && sens == 0)
				{
					Plane_Three.ScrollDx = 0;
				}
				else
				{
					if (sens == 1)
					{
						Plane_Three.ScrollDx = Plane_Three.ScrollDx + dX;
					}
					else
					{
						Plane_Three.ScrollDx = Plane_Three.ScrollDx - dX;
					}
				}
			}
			
			GPU_WriteReg(FBP3SCRL ,(Plane_Three.ScrollDx & 0xFFFF));
			break;
		case 4 :
			if ((dX + Plane_Four.ScrollDx > Plane_Four.Plane_Width - SCREEN_WIDTH) && sens == 1)
			{
				Plane_Four.ScrollDx = Plane_Four.Plane_Width - SCREEN_WIDTH;
			}
			else
			{
				if ((dX > Plane_Four.ScrollDx ) && sens == 0)
				{
					Plane_Four.ScrollDx = 0;
				}
				else
				{
					if (sens == 1)
					{
						Plane_Four.ScrollDx = Plane_Four.ScrollDx + dX;
					}
					else
					{
						Plane_Four.ScrollDx = Plane_Four.ScrollDx - dX;
					}
				}
			}
			
			GPU_WriteReg(FBP4SCRL ,(Plane_Four.ScrollDx & 0xFFFF));
			break;
	}
					
	return 0;
}

// Mis à jour du scrollong vertical

int GPU_VScroll (GPU_Plane plane, uint32_t dY, int sens)
{
	
	switch (plane.numero)
	{
		case 1 :
			if (dY + Plane_One.ScrollDy > Plane_One.Plane_Height - SCREEN_HEIGTH)
			{
				Plane_One.ScrollDy = Plane_One.Plane_Height - SCREEN_HEIGTH;
			}
			else
			{
				if (dY + Plane_One.ScrollDy <= 0)
				{
					Plane_One.ScrollDy = 0;
				}
				else
				{
					Plane_One.ScrollDy += dY;
				}
			}
			GPU_WriteReg(FBP1SCRL ,((Plane_One.ScrollDy & 0xFFFF) << 16));
			break;
		case 2 :
			if (dY + Plane_Two.ScrollDy > Plane_Two.Plane_Height - SCREEN_HEIGTH)
			{
				Plane_Two.ScrollDy = Plane_Two.Plane_Height - SCREEN_HEIGTH;
			}
			else
			{
				if (dY + Plane_Two.ScrollDy <= 0)
				{
					Plane_Two.ScrollDy = 0;
				}
				else
				{
					Plane_Two.ScrollDy += dY;
				}
			}
			GPU_WriteReg(FBP2SCRL ,((Plane_Two.ScrollDy & 0xFFFF) << 16));
			break;
		case 3 :
			if (dY + Plane_Three.ScrollDy > Plane_Three.Plane_Height - SCREEN_HEIGTH)
			{
				Plane_Three.ScrollDy = Plane_Three.Plane_Height - SCREEN_HEIGTH;
			}
			else
			{
				if (dY + Plane_Three.ScrollDy <= 0)
				{
					Plane_Three.ScrollDy = 0;
				}
				else
				{
					Plane_Three.ScrollDy += dY;
				}
			}
			GPU_WriteReg(FBP3SCRL ,((Plane_Three.ScrollDy & 0xFFFF) << 16));
			break;
		case 4 :
			if (dY + Plane_Four.ScrollDy > Plane_Four.Plane_Height - SCREEN_HEIGTH)
			{
				Plane_Four.ScrollDy = Plane_Four.Plane_Height - SCREEN_HEIGTH;
			}
			else
			{
				if (dY + Plane_Four.ScrollDy <= 0)
				{
					Plane_Four.ScrollDy = 0;
				}
				else
				{
					Plane_Four.ScrollDy += dY;
				}
			}
			GPU_WriteReg(FBP4SCRL ,((Plane_Four.ScrollDy & 0xFFFF) << 16));
			break;
	}
	
	return 0;
}

// Choix du mode de transparence

int GPU_TransparenceMode (uint32_t AlphaNBinary)
{
	PLANE.Alpha_On = AlphaNBinary;
		
	GPU_MAJ_PLAN();
	
	return 0;
}

/***** Configuration du LCD *****/

int GPU_LCD_AjustContrast(uint32_t lol)
{
	if ( lol > 0x1F)
	{
		GPU_WriteReg(LCDCON,0x08);
	}
	else
	{
	GPU_WriteReg(LCDCON,lol);
	}
	
	GPU_WriteReg(LCDCTRL,1);
	
	return 0;
}

int GPU_LCD_AjusteBrightness(uint32_t lol)
{
	if ( lol > 0x1F)
	{
	GPU_WriteReg(LCDBRI,0x040);
	}
	else
	{
	GPU_WriteReg(LCDBRI,lol);
	}
		
	GPU_WriteReg(LCDCTRL,1);
	
	return 0;
}

int GPU_LCD_AjusteHS(uint32_t hue,uint32_t sat)
{
	uint32_t data = 0;
	
	if ( hue > 0x0F)
	{
		data = 0x08 << 4;
	}
	else
	{
		data = (hue & 0xF) << 4;
	}
	
	if ( sat > 0x0F)
	{
		data += 0x08;
	}
	else
	{
		data += (sat & 0xF);
	}
				
	GPU_WriteReg(LCDHS,data);
	
	GPU_WriteReg(LCDCTRL,1);
	
	return 0;
}



int GPU_LCD_AjusteSubBri(uint32_t red,uint32_t blue)
{
	uint32_t data = 0;

		
	if ( red > 0x3F)
	{
		data = 0x20;
	}
	else
	{
		data = (red & 0x3F);
	}
	
	if ( blue > 0x3F)
	{
		data += (0x20 << 6);
	}
	else
	{
		data += ((blue & 0x3F)<< 6);
	}
				
	GPU_WriteReg(LCDSBRI,data);
	
	GPU_WriteReg(LCDCTRL,1);
	
	return 0;
}

/***** Group : Plan modification *****/

// On verifie que le BPU est en pause avec de lancer quoique ce soit

int GPU_verif_status() 
{
	uint32_t status;
	status = GPU_ReadReg(BPUCTRL);
	status = status & 0x00000001;
	
	return status ;
}

// On clear l'écran tout entier

int GPU_ClearScreen (GPU_Plane plane)
{
	GPU_ClearRect(plane,0,0,plane.Plane_Height,plane.Plane_Width);
	
	return 0; // Appel de l'instruction clear mais sur tout l'écran
}

// On rempli une zone d'une couleur donné

int GPU_FillRect (GPU_Plane plane,uint32_t X0,uint32_t Y0,uint32_t dX,uint32_t dY,GPU_Color Color) 
{
	
	
	uint32_t adresse_dest;
	uint16_t fill_col = ((Color.R & 0xF) + ((Color.G & 0xF) << 4) + ((Color.B & 0xF) << 8)+ ((Color.A & 0xF) << 12));
	while( GPU_verif_status() != 0){};	

	adresse_dest = ADRESSE_TEMPON;
		
	GPU_WriteReg(BPUDSTADDR,adresse_dest);
		
	GPU_WriteReg(BPUPICSIZE, (0xFFFF0000 & (plane.Plane_Width << 16 )));

	GPU_WriteReg(BPUSIZE, (dX & 0x3FF) + ((dY & 0x3FF) << 16 ));		

	GPU_WriteReg(BPUFILCOL,(uint32_t) fill_col);
	
	GPU_WriteReg(BPUCTRL,0x0009); // Informe le BPU de l'opération à faire
		
		
	while( GPU_verif_status() != 0){};
	
	adresse_dest = plane.Addr + X0 + Y0*plane.Plane_Width;
		
	GPU_WriteReg(BPUDSTADDR,adresse_dest);
		
	GPU_WriteReg(BPUPICSIZE, (0xFFFF0000 & (plane.Plane_Width << 16 )));

	GPU_WriteReg(BPUSIZE, (dX & 0x3FF) + ((dY & 0x3FF) << 16 ));		

	GPU_WriteReg(BPUFILCOL,(uint32_t) fill_col);
		
	GPU_WriteReg(BPUCTRL,0x0009); // Informe le BPU de l'opération à faire
	
	return 0;
}

// On clear une zone spécifique d'un des plans

int GPU_ClearRect(GPU_Plane plane,uint32_t X0,uint32_t Y0,uint32_t dX,uint32_t dY)
	{
	uint32_t adresse_dest;

	while( GPU_verif_status() != 0){};	

	adresse_dest = ADRESSE_TEMPON;
		
	GPU_WriteReg(BPUDSTADDR,adresse_dest);
		
	GPU_WriteReg(BPUPICSIZE, (0xFFFF0000 & (plane.Plane_Width << 16 )));

	GPU_WriteReg(BPUSIZE, (dX & 0x3FF) + ((dY & 0x3FF) << 16 ));		

	GPU_WriteReg(BPUCTRL, 0x0009); // Informe le BPU de l'opération à faire

	GPU_WriteReg(BPUFILCOL, 0);
		
	while( GPU_verif_status() != 0){};
	
	adresse_dest = plane.Addr + X0 + Y0*plane.Plane_Height;

	GPU_WriteReg(BPUFILCOL, 0);		

	GPU_WriteReg(BPUPICSIZE, (0xFFFF0000 & (plane.Plane_Width << 16 )));
			
	GPU_WriteReg(BPUDSTADDR,adresse_dest);

	GPU_WriteReg(BPUSIZE, (dX & 0x3FF) + ((dY & 0x3FF) << 16 ));		
		
	GPU_WriteReg(BPUCTRL, 0x0009); // Informe le BPU de l'opération à faire
	
	return 0;
}

int GPU_SetRectAlphaValue (GPU_Plane plane,uint32_t X0,uint32_t Y0,uint32_t dX,uint32_t dY, uint32_t alpha)
{
	uint32_t adresse_dest;
	
	while( GPU_verif_status() != 0){};
	
	adresse_dest = plane.Addr + X0 + Y0*plane.Plane_Height;
				
	GPU_WriteReg(BPUDSTADDR,adresse_dest);
		
	GPU_WriteReg(BPUPICSIZE, (0xFFFF0000 & (plane.Plane_Width << 16 )));
	
	GPU_WriteReg(BPUSIZE, (dX & 0x3FF) + ((dY & 0x3FF) << 16 ));		
	
	GPU_WriteReg(BPUSAR,alpha);
	
	GPU_WriteReg(BPUDUMADDR,ADRESSE_TEMPON);	
		
	GPU_WriteReg(BPUCTRL,0x0021); // Informe le BPU de l'opération à faire
	
	return 0;
}	

// On lance une opération de bitblit

int GPU_BitBlitRect (GPU_Plane srcPlane,GPU_Image *image,GPU_Plane destPlane,uint32_t dstX,uint32_t dstY) 
{
	uint32_t adresse_dest;
	uint32_t adresse_source;
	
	//while( GPU_verif_status() != 0){};
	
	adresse_dest = destPlane.Addr + dstX + dstY*destPlane.Plane_Width;
	adresse_source = image->Adresse;
	
	image->Adresse = adresse_dest;

	GPU_WriteReg(BPUPICSIZE,((0x0000FFFF & (srcPlane.Plane_Width)) + (0xFFFF0000 & (destPlane.Plane_Width << 16 ))));
		
	GPU_WriteReg(BPUDSTADDR,adresse_dest);
	GPU_WriteReg(BPUSRCADDR,adresse_source);


	GPU_WriteReg(BPUSIZE, (image->Width & 0x3FF) + ((image->Height & 0x3FF) << 16 ));		
	
	GPU_WriteReg(BPUDUMADDR,ADRESSE_TEMPON);	
		
	GPU_WriteReg(BPUCTRL,0x0003); // Informe le BPU de l'opération à faire
			
	return 0;
}

int GPU_BitBlitRectV2 (uint32_t x,uint32_t y,uint32_t dx,uint32_t dy, GPU_Image *image,GPU_Plane destPlane,uint32_t dstX,uint32_t dstY) 
{
	uint32_t adresse_dest;
	uint32_t adresse_source;
	
	//while( GPU_verif_status() != 0){};
	
	adresse_dest = destPlane.Addr + dstX + dstY*destPlane.Plane_Width;
	adresse_source = image->Adresse + x + y*image->Width;

	GPU_WriteReg(BPUPICSIZE,((0x0000FFFF & (image->Width)) + (0xFFFF0000 & (destPlane.Plane_Width << 16 ))));
		
	GPU_WriteReg(BPUDSTADDR,adresse_dest);
	GPU_WriteReg(BPUSRCADDR,adresse_source);


	GPU_WriteReg(BPUSIZE, (dx & 0x3FF) + ((dy & 0x3FF) << 16 ));		
	
	GPU_WriteReg(BPUDUMADDR,ADRESSE_TEMPON);	
		
	GPU_WriteReg(BPUCTRL,0x0003); // Informe le BPU de l'opération à faire
			
	return 0;
}

int GPU_MoveRect (GPU_Plane srcPlane,GPU_Image *image,GPU_Plane destPlane,uint32_t dstX,uint32_t dstY) 
{

	uint32_t adresse_dest;
	uint32_t adresse_source;
	
	while( GPU_verif_status() != 0){};
	
	adresse_dest = destPlane.Addr + dstX + dstY*destPlane.Plane_Width;
	adresse_source = image->Adresse;
	
	image->Adresse = adresse_dest;

		
	GPU_WriteReg(BPUDSTADDR,adresse_dest);
	GPU_WriteReg(BPUSRCADDR,adresse_source);
		
	GPU_WriteReg(BPUPICSIZE,((0x0000FFFF & (srcPlane.Plane_Width)) + (0xFFFF0000 & (destPlane.Plane_Width << 16 ))));



	GPU_WriteReg(BPUSIZE, (image->Width & 0x3FF) + ((image->Height & 0x3FF) << 16 ));		
	
	GPU_WriteReg(BPUDUMADDR,ADRESSE_TEMPON);
		
	GPU_WriteReg(BPUCTRL,0x0005); // Informe le BPU de l'opération à faire
	
	return 0;
}

int GPU_Move1_bpu(GPU_Plane srcPlane,GPU_Image *image,GPU_Plane destPlane,uint32_t dstX,uint32_t dstY,GPU_Color Color)
{
	
	/*uint32_t adresse_dest;
	uint32_t adresse_source;
	
	while( GPU_verif_status() != 0){};
	
	adresse_dest = destPlane.Addr + dstX + dstY*destPlane.Plane_Width;
	adresse_source = image->Adresse;
	
	image->Adresse = adresse_dest;

	
	GPU_WriteReg(BPUPICSIZE, (0xFFFF0000 & (srcPlane.Plane_Width << 16 )));


	GPU_WriteReg(BPUSRCADDR,adresse_source);

	GPU_WriteReg(BPUDSTADDR,adresse_dest);
	
	GPU_WriteReg(BPUDUMADDR,ADRESSE_TEMPON);	

	GPU_WriteReg(BPUSIZE, (image->Width & 0x3FF) + ((image->Height & 0x3FF) << 16 ));		
	
	GPU_WriteReg(BPUFILCOL,(uint32_t) ((Color.R & 0xF) + ((Color.G & 0xF) << 4) + ((Color.B & 0xF) << 8)+ ((Color.A & 0xF) << 12)));
	
	GPU_WriteReg(BPUCTRL,0x0041); // Informe le BPU de l'opération à faire
			*/
	return 0;
}	

int seta1_bpu(uint32_t adresse_source,uint32_t adresse_dest, uint32_t taille_horizontal, uint32_t taille_vertical, uint16_t couleur, uint16_t alpha)
{
	/*while( GPU_verif_status() != 0){};
		
	GPU_WriteReg(BPUDSTADDR,adresse_dest);
	GPU_WriteReg(BPUSRCADDR,adresse_source);
		
	GPU_WriteReg(BPUSIZE, (taille_horizontal & 0x3FF) + ((taille_vertical & 0x3FF) << 10 ));		
	
	//GPU_WriteReg(BPUPICSIZE, (0xFF00 & (plane.Plane_Width << 16 )));

		
	GPU_WriteReg(BPUFILCOL,couleur);
	
	GPU_WriteReg(BPUSAR,alpha);
		
	GPU_WriteReg(BPUCTRL,0x0081); // Informe le BPU de l'opération à faire*/
			
	return 0;
}

/***** Group : DMA control *****/

int GPU_EtatDMA ()
{
	return (GPU_ReadReg(DMACTRL) & 0x2);
}

int GPU_PreSendData(GPU_Image *image, uint32_t dx, uint32_t dy, GPU_Plane plan)
{
	uint32_t addr = plan.Addr + dx + dy*plan.Plane_Width;
	
	image->Adresse = addr;
	
	GPU_WriteReg(DMADSTADDR,addr);
	
	GPU_WriteReg(DMAIMGSIZE,(image->Width) + ((image->Height) << 16));
	
	GPU_WriteReg(DMADSTSIZER,plan.Plane_Width);
	
	GPU_WriteReg(DMACTRL,0x1);
	
	return 0;
}
	
	

/***** Group : PGU modification *****/	
	
	int GPU_verif_statusPGU() 
{
	uint32_t status;
	
	status = GPU_ReadReg(PGUCTRL);
	status = status & 0x00000001;
	
	return status ;
}
	

// On met un pixel particulier d'un plan à une certaine couleur

int GPU_SetPixel (GPU_Plane plane, int X, int Y, GPU_Color color)
{
	uint32_t Coord = 0;
	uint16_t col = ((color.R & 0xF) + ((color.G & 0xF) << 4) + ((color.B & 0xF) << 8)+ ((color.A & 0xF) << 12));

	Coord = (uint16_t) X;
	Coord |= (((uint16_t) Y) << 16) ;
	
	while ( GPU_verif_statusPGU() != 0) {}

	GPU_WriteReg(PGULC1R,Coord);
			
	GPU_WriteReg(PGUDSTLEN,plane.Plane_Width);
		
	GPU_WriteReg(PGUDSTADDR,plane.Addr);

	GPU_WriteReg(PGUCOLOR, (uint16_t) col);
	
	GPU_WriteReg(PGUCTRL,0x3);
	
	return 0;
}

// On clear un pixel particulier

int GPU_ClearPixel (GPU_Plane plane, int X, int Y)
{
	uint32_t Coord = 0;

	Coord = (uint16_t) X;
	Coord |= (((uint16_t) Y) << 16) ;
	
	while ( GPU_verif_statusPGU() != 0) {}
	
	GPU_WriteReg(PGULC1R,Coord);
			
	GPU_WriteReg(PGUDSTLEN,plane.Plane_Width);
		
	GPU_WriteReg(PGUDSTADDR,plane.Addr);

	GPU_WriteReg(PGUCOLOR, 0);
	
	GPU_WriteReg(PGUCTRL,0x3);
	return 0;
}



int GPU_DrawLine (GPU_Plane plane, int X1, int Y1, int X2, int Y2, GPU_Color color)
{
	uint32_t Coord = 0;
	uint16_t col = ((color.R & 0xF) + ((color.G & 0xF) << 4) + ((color.B & 0xF) << 8)+ ((color.A & 0xF) << 12));

	if(X2 < X1){
		Coord = X2;
		X2 = X1;
		X1 = Coord;

		Coord = Y2;
		Y2 = Y1;
		Y1 = Coord;
	}
	
	while ( GPU_verif_statusPGU() != 0) {}
	
	Coord = (uint16_t) X1;
	Coord |= (((uint16_t) Y1) << 16) ;	
	GPU_WriteReg(PGULC1R,Coord);

	Coord = (uint16_t) X2;
	Coord |= (((uint16_t) Y2) << 16) ;	
	GPU_WriteReg(PGULC2R,Coord);
		
	GPU_WriteReg(PGUDSTLEN,plane.Plane_Width);
		
	GPU_WriteReg(PGUDSTADDR,plane.Addr);

	GPU_WriteReg(PGUCOLOR, (uint16_t) col);
	
	GPU_WriteReg(PGUCTRL,0x5);

	return 0;	
}
						

int GPU_DrawCircle (GPU_Plane plane, int X, int Y, int R, GPU_Color color)
{
	uint32_t Coord = 0;
	uint16_t col = ((color.R & 0xF) + ((color.G & 0xF) << 4) + ((color.B & 0xF) << 8)+ ((color.A & 0xF) << 12));

	if(R <= X && R<=Y){
	
		while ( GPU_verif_statusPGU() != 0) {}
		
		Coord = (uint16_t) X;
		Coord |= (((uint16_t) Y) << 16) ;	
		GPU_WriteReg(PGULC1R,Coord);

		Coord = (uint16_t) X+R;
		Coord |= (((uint16_t) Y) << 16) ;	
		GPU_WriteReg(PGULC2R,Coord);
			
		GPU_WriteReg(PGUDSTLEN,plane.Plane_Width);
			
		GPU_WriteReg(PGUDSTADDR,plane.Addr);

		GPU_WriteReg(PGUCOLOR, (uint16_t) col);
		
		GPU_WriteReg(PGUCTRL,0x21);

	}
	
	return 0;		
}
						

int GPU_WriteChar (GPU_Plane plane, int X, int Y, char c, GPU_Color color){

	uint32_t Coord = 0;
	uint16_t col = ((color.R & 0xF) + ((color.G & 0xF) << 4) + ((color.B & 0xF) << 8)+ ((color.A & 0xF) << 12));

	if(c>' ' && c<= 127){
	
		while ( GPU_verif_statusPGU() != 0) {}
		
		Coord = (uint16_t) X;
		Coord |= (((uint16_t) Y) << 16) ;	
		GPU_WriteReg(PGULC1R,Coord);
			
		GPU_WriteReg(PGUCHAR, (uint16_t) (c-32));
			
		GPU_WriteReg(PGUDSTLEN,plane.Plane_Width);
			
		GPU_WriteReg(PGUDSTADDR,plane.Addr);

		GPU_WriteReg(PGUCOLOR, (uint16_t) col);
		
		GPU_WriteReg(PGUCTRL,0x09);
	
	}
	
	return 0;	
}	

int GPU_WriteText (GPU_Plane plane, int X, int Y, char* str, GPU_Color color){
	int x_char;
	int i = 0;
	x_char = X;
	
	while(x_char < plane.Plane_Width && str[i]!=0 ){
		GPU_WriteChar (plane, x_char,  Y,  str[i], color);
		i++;
		x_char += 6;
	}
	
	return 0;		
}


int GPU_DrawRect (GPU_Plane plane, int X1, int Y1, int X2, int Y2, GPU_Color color){
	GPU_DrawLine (plane, X1, Y1, X2, Y1, color);
	Wait(100);
	GPU_DrawLine (plane, X2, Y1, X2, Y2, color);
	Wait(100);
	GPU_DrawLine (plane, X2, Y2, X1, Y2, color);
	Wait(100);
	GPU_DrawLine (plane, X1, Y2, X1, Y1, color);
	Wait(100);
	
	return 0;
}
