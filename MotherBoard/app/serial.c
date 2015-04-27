/**
  ******************************************************************************
  * @file    serial.c
  * @author  Gerome (4AE-SE) 
  * @version V0.1
  * @date    03-April-2014
  * @brief   Gestion du port série
	Contient le code pour paramétrer l’usart1*/
	/*Il faut rajouter les fonctions :
	void NVIC_Configuration(void); (celui là est pas obligatoire il me semble. Mais mettez le dans le doute)
	void RCC_Configuration(void);
	void GPIO_Configuration(void);
	void USART1_Configuration(void);
	Puis redéfinir fputc
	*/
	/*Il s’utilise ensuite en faisant un simple printf()*/
	/*Il faut connecter un cable avec à la prise série du haut*/
	/*Les paramètres de la connection sont définies au début de la fonction 
	USART1_Configuration
  ******************************************************************************
  */
	
	/**
  ******************************************************************************
	*	Includes
  ******************************************************************************
  */
 #include "serial.h"
 
 /**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */
	
	
void Init_Serial_Port(void)
{
	NVIC_Configuration(); /* Interrupt Config */
	RCC_Configuration();
	GPIO_Configuration();
  USART1_Configuration();
}



//******************************************************************************

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


}

/**************************************************************************************/

void RCC_Configuration(void)
{
  /* --------------------------- System Clocks Configuration -----------------*/
  /* USART1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  /* GPIOA clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
}

/**************************************************************************************/

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*-------------------------- GPIO Configuration ----------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Connect USART pins to AF */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);  // USART1_TX
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);  // USART1_RX
}

/**************************************************************************************/

void USART1_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;

  /* USARTx configuration ------------------------------------------------------*/
  /* USARTx configured as follow:
        - BaudRate = 9600 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART1, &USART_InitStructure);

  USART_Cmd(USART1, ENABLE);
}




