#include "gpu_driver.h"
	

/**
  ******************************************************************************
	*	DRIVER
  ******************************************************************************
  */


/**** FSMC Initiailization Procedure ****/
void GPU_initFSMC(void){
	//1. Configuration structure declaration
	GPIO_InitTypeDef  GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef FSMC_ReadWriteTimingStructure;
	FSMC_NORSRAMTimingInitTypeDef FSMC_WriteTimingStructure;

	//2. Enable the clock
		// FSMC clokc activation
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
	
		// GPIO clock activation
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	//2. Mettre les pins en configuration FSMC
		// Address pins
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0, GPIO_AF_FSMC);	//RS
		// Data pins
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
	
	// Control pins
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);	// WE  (WR/SCL dans le cas du LCD)
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);	// OE	 (RD dans le cas LCD)
			
	// Chip Select pins
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource12, GPIO_AF_FSMC);  // Chip select NE


	/*============== GPIO Configuration ==============*/
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


	//FSMC Structure configuration

	//Configuration of the GPU interface as an aynchronous SRAM, mode 1 type write acces

	// ================= Structure initialization ========================= //
  FSMC_NORSRAMStructInit(&FSMC_NORSRAMInitStructure);
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = (FSMC_NORSRAMTimingInitTypeDef*)&FSMC_ReadWriteTimingStructure;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = (FSMC_NORSRAMTimingInitTypeDef*)&FSMC_WriteTimingStructure;
	
	// Signal structure configuration
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

	// Timing structure configuration
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

	//4. Initialize the FSMC structure
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

	//5. Enable the FSMC
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
}


// Configures the FSMC clock by dividing the system clock
// Argument is a power of 2 until 512 except for 32
void GPU_setClockFSMC(int a){
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
}
	
/**** Initialization of extra GPIO for the interface *****/
void GPU_init_GPIO_interface(void){	
	//On prend PC7 pour l'attente du passage à 0;
	// Initialisation du GPIO PB8 en mode GP in
	GPIO_InitTypeDef InitGPIOC;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_StructInit(&InitGPIOC);
	InitGPIOC.GPIO_Pin = GPIO_Pin_7;
	InitGPIOC.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_Init(GPIOB, &InitGPIOC );		
}
	

/**** Blocking wait procedure ****/
void wait(int delay){
	delay = (delay > 0) ? delay : 1000;
	while(delay--);
}

// Read busy signal to check whether the GPU is ready
uint8_t GPU_read_GPIO_busy(){
		return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7);
}
	
/**** Atomic read/write operations for accessing an address reading data/writing data *****/
void _gpu_access_addr(uint16_t addr){
	GPU_ADDR16 = addr;
}

void _gpu_write_data(uint16_t data){
	GPU_DATA16 = data;
}

uint16_t _gpu_read_data(){
	return GPU_DATA16;
}

/**** Procédure d'écriture et de lecture pour les registres *****/

void GPU_WriteReg(uint16_t addr, uint16_t data){
	while( GPU_read_GPIO_busy() !=0){};
	_gpu_access_addr(addr);
	while( GPU_read_GPIO_busy() !=0){};
	_gpu_write_data(data);
}

uint16_t GPU_ReadReg(uint16_t addr){
	while( GPU_read_GPIO_busy() !=0){};
	_gpu_access_addr(addr);
	while( GPU_read_GPIO_busy() !=0){};	
	return _gpu_read_data();
}
