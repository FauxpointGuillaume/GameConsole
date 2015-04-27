/**
  ******************************************************************************
  * @file    main.c
  * @author  Jeremy LAUVIGE (4AE-SE) 
  * @version V0.1
  * @date    18-Mars-2014
  * @brief   test des gpios et leds et potar
  ******************************************************************************
  */

/**
  ******************************************************************************
	*	Includes
  ******************************************************************************
  */
	#include "global.h"
	#include "interface.h"
	#include "Licorne.h"
	#include "StreetOfRage.h"
	
	

	
	
int main (void)
{
	
	/**
	******************************************************************************
	*	Initialisation
	******************************************************************************
	*/
	
		GPU_Image background;


	Initialize_Button(USER);
	Initialize_Button(TAMPER);

	Initialize_Led(LED1);
	Turn_Led(LED1,ON);
	GPU_Init();
	JOY_Init();	
	
	Wait(1000000);

	GPU_ConfigureOutput(MODE_VGA);		

	initSOR();	
	
	GPU_ClearRect(Plane_One,0,0,920,240);
	
	GPU_NewImage(&background, 920, 240, "back", START_ADRESSE_DATA_PLANE1);

	openImageFiles("back" , &res, &fil, &fs32);
	GPU_PreSendData(&background, 0, 0, Plane_One);
	readImageFiles(&res, &fil, &fs32);
	

	while(1)
	{			
		StreetOfRage();		
	}
	
} //Fin main









