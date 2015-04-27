/**
  ******************************************************************************
  * @file   fsmc.c
  * @author  Pierre-Louis TILAK (4AE-SE) 
  * @version V0.1
  * @date    7-Avril-2014
  * @brief  Contient les configurations du FSMC
  ******************************************************************************
  */

/**
  ******************************************************************************
	*	Includes
  ******************************************************************************
  */
	 #include "fsmc.h"
	
	/**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */
	
	/**
  * @brief  Initialise le FSMC pour la FLASH et la SRAM
  * @param 
  * @retval void
  */
		void initFSMC(){
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef FSMC_ReadWriteTimingStructure;
	FSMC_NORSRAMTimingInitTypeDef FSMC_WriteTimingStructure;
			
			
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
	
	/*==== Amène le signal de clock sur les ports nécessaires ====*/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	/*==== Connecte les pins pour l'alternate function ====*/

	// Pins d'adressages
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_FSMC);
	
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource2, GPIO_AF_FSMC);	
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource3, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource4, GPIO_AF_FSMC);	
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource5, GPIO_AF_FSMC);
	
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource15, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource13, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource12, GPIO_AF_FSMC);
	
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource3, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource2, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0, GPIO_AF_FSMC);

	// Pins de données
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
	
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_FSMC);
	
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
	
	// Pins de commande

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
	
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_FSMC);
	
	// Pins Chip Select 
		GPIO_PinAFConfig(GPIOG, GPIO_PinSource10, GPIO_AF_FSMC);
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);


	/*============== Configure les pins d'adressages ==============*/

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	// Port D
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_10 | GPIO_Pin_9 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_15 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_5 | GPIO_Pin_4 ;
	GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_7 ;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// PORT E
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4  ;
	GPIO_InitStructure.GPIO_Pin |=  GPIO_Pin_7|GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	// Port G
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_10;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	// Port F
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOF, &GPIO_InitStructure);


	/* ======================================== */
  /* 					SRAM Configuration  						*/
	/* ======================================== */

	// ================= Initialisation de la structure ========================= //
  FSMC_NORSRAMStructInit(&FSMC_NORSRAMInitStructure);
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = (FSMC_NORSRAMTimingInitTypeDef*)&FSMC_ReadWriteTimingStructure;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = (FSMC_NORSRAMTimingInitTypeDef*)&FSMC_WriteTimingStructure;
	
	// Configuration de la structure FSMC	
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;

	// Configuration de la structure de timings //

	FSMC_ReadWriteTimingStructure.FSMC_AddressSetupTime = 2;
	FSMC_ReadWriteTimingStructure.FSMC_AddressHoldTime = 1;
	FSMC_ReadWriteTimingStructure.FSMC_DataSetupTime = 2;
	FSMC_ReadWriteTimingStructure.FSMC_BusTurnAroundDuration = 1;
	FSMC_ReadWriteTimingStructure.FSMC_CLKDivision = 2;
	FSMC_ReadWriteTimingStructure.FSMC_DataLatency = 2;
	FSMC_ReadWriteTimingStructure.FSMC_AccessMode = FSMC_AccessMode_A; 
	FSMC_WriteTimingStructure.FSMC_AddressSetupTime = 2;
	FSMC_WriteTimingStructure.FSMC_AddressHoldTime = 1;
	FSMC_WriteTimingStructure.FSMC_DataSetupTime = 2;
	FSMC_WriteTimingStructure.FSMC_BusTurnAroundDuration = 1;
	FSMC_WriteTimingStructure.FSMC_CLKDivision = 2;
	FSMC_WriteTimingStructure.FSMC_DataLatency = 2;
	FSMC_WriteTimingStructure.FSMC_AccessMode = FSMC_AccessMode_A;

	// =============== Initialisation de la SRAM ================== //

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

	// =============== Enable the SRAM BANK ================== //

	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);

	#define __SRAM_Initialized
	
	
	
	
	/* ======================================== */
  /* 					FLASH NOR Configuration  				*/
	/* ======================================== */
	
	// Configuration de la structure FSMC	
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR ;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;

	// Configuration de la structure de timings //

	FSMC_ReadWriteTimingStructure.FSMC_AddressSetupTime = 2;
	FSMC_ReadWriteTimingStructure.FSMC_AddressHoldTime = 1;
	FSMC_ReadWriteTimingStructure.FSMC_DataSetupTime = 2;
	FSMC_ReadWriteTimingStructure.FSMC_BusTurnAroundDuration = 1;
	FSMC_ReadWriteTimingStructure.FSMC_CLKDivision = 2;
	FSMC_ReadWriteTimingStructure.FSMC_DataLatency = 2;
	FSMC_ReadWriteTimingStructure.FSMC_AccessMode = FSMC_AccessMode_A; 
	FSMC_WriteTimingStructure.FSMC_AddressSetupTime = 2;
	FSMC_WriteTimingStructure.FSMC_AddressHoldTime = 1;
	FSMC_WriteTimingStructure.FSMC_DataSetupTime = 2;
	FSMC_WriteTimingStructure.FSMC_BusTurnAroundDuration = 1;
	FSMC_WriteTimingStructure.FSMC_CLKDivision = 2;
	FSMC_WriteTimingStructure.FSMC_DataLatency = 2;
	FSMC_WriteTimingStructure.FSMC_AccessMode = FSMC_AccessMode_A;

	// =============== Initialisation de la FLASHNOR ================== //

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

	// =============== Enable the FLASHNOR BANK ================== //

	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);

	#define __FLASHNOR_Initialized
	
	
	
	

	/* The following sequence should be followed to configure the FSMC to interface with
	 SRAM, PSRAM, NOR or OneNAND memory connected to the NOR/SRAM Bank:
	 
		 1. Enable the clock for the FSMC and associated GPIOs using the following functions:
						RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
						RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);

		 2. FSMC pins configuration 
				 - Connect the involved FSMC pins to AF12 using the following function 
						GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_FSMC); 
				 - Configure these FSMC pins in alternate function mode by calling the function
						GPIO_Init();    
				 
		 3. Declare a FSMC_NORSRAMInitTypeDef structure, for example:
						FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
				and fill the FSMC_NORSRAMInitStructure variable with the allowed values of
				the structure member.
				
		 4. Initialize the NOR/SRAM Controller by calling the function
						FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

		 5. Then enable the NOR/SRAM Bank, for example:
						FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM2, ENABLE);

		 6. At this stage you can read/write from/to the memory connected to the NOR/SRAM Bank. */


	/*  TIMINGS
	tHCLK = 10 ns si CLK = 100Mhz, c'est la période ? 
	tWC = 10ns
	tPWE1 = 8 ns
	tAA = 10 ns
	tsu = 4 ns (pas sur .... )
	tv = 10 ns

	Formula 2: DATAST = tPWE1 / tHCLK = 0.8ns

	Formula 1: ( (ADDSET + 1) + (DATAST + 1) ) × tHCLK = max (tWC)
	ADDSET >= 0.2  ==> ADDSET = 1
	*/
}


