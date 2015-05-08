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
  
	#include <RTL.h>
  
	#include "global.h"
	#include "interface.h"
	#include "Licorne.h"
	#include "StreetOfRage.h"
	#include "Zelda.h"
	
	
/* id1, will contain task identifications at run-time */
OS_TID id1;

/* Main program : Initialize the system and start the first task */
int main (void)
{	
	Initialize_Button(USER);
	Initialize_Button(TAMPER);

	Initialize_Led(LED1);
	Initialize_Led(LED2);
	Initialize_Led(LED3);
	Initialize_Led(LED4);
	
	Turn_Led(LED1,ON);
	GPU_Init();
	JOY_Init();	
	initSD(&fs32);
	
	wait(1000000);

	while(1)
	{
		// Start the task menu allow to choose the program
		// - GIF unicorn
		// - Street of rage
		// - Zelda		
		os_sys_init (taskMenu);
	}	
} //Fin main


/*----------------------------------------------------------------------------
 *   Task 1:  RTX Kernel starts this task with os_sys_init (taskMenu)
 *---------------------------------------------------------------------------*/
__task void taskMenu (void) 
{
	// Variable declaration
	GPU_Image background;	
	GPU_Color aColor;	
	int stateArrow = 0;
	uint32_t joystick;
	
	// Set the task priority
	id1 = os_tsk_self ();
  os_tsk_prio_self (1);
	
	// Configure the layer for the console menu
	GPU_ConfigureLayer(&Layer_1,LAYER1_START_ADDRESS,320,240);
	GPU_ConfigureLayer(&Layer_2,LAYER2_START_ADDRESS,320,240);
	
	Display_conf.Enable =1;
	Display_conf.Alpha_On =1;
	Display_conf.Plan_Enable = 0x3;
	Display_conf.Test_On=0;
	
	GPU_UpdateDisplayConfig();
	
	GPU_HScroll (&Layer_1, 0,1);
	GPU_VScroll (&Layer_1, 0,1);
	
	GPU_HScroll (&Layer_2, 0,1);
	GPU_VScroll (&Layer_2, 0,1);
			
	GPU_ConfigureOutput(MODE_VGA);
	
	GPU_ClearScreen(&Layer_1);
		GPU_ClearScreen(&Layer_2);
		aColor.R = 0;
	aColor.G = 0;
	aColor.B = 0;
	aColor.A = 0;
	GPU_FillRect (&Layer_2,0,0,320,240, aColor);

	
	// Load the image from the SD card to the graphic card
	GPU_NewImage(&background, 320, 240,"menu", 0x0500000);
	// SD_LoadImage(&background, Plane_One, 0, 0, &fil);
	GPU_BitBlitI2L(&background, 0, 0, 320, 240,&Layer_1, 0,0);



			
	// Display the selector to the first programm
	aColor.R = 7;
	aColor.G = 1;
	aColor.B = 15;
	aColor.A = 15;
	GPU_FillRect (&Layer_2,60,108,10,10, aColor);
	
	while(is_button_pressed(USER) && joystick != JOY_RIGHT)
	{
		joystick = JOY_GetKeys();
		if (joystick == JOY_UP)
		{
			if (stateArrow == 0)
			{
				stateArrow = 2;
			}
			else
			{
				stateArrow--;
			}
		}
		if (joystick == JOY_DOWN)
		{
			stateArrow++;
			stateArrow = stateArrow % 3;
		}
			// Update the position of the selector
			GPU_ClearScreen(&Layer_2);
			GPU_FillRect (&Layer_2,60 ,108 + 26*stateArrow,10,10, aColor);
		
		switch (stateArrow)
		{
			case 0:
			{
				Turn_Led(LED2,ON);
				Turn_Led(LED3,OFF);
				Turn_Led(LED4,OFF);
				break;
			}
			case 1:
			{
				Turn_Led(LED2,OFF);
				Turn_Led(LED3,ON);
				Turn_Led(LED4,OFF);
				break;
			}
			case 2:
			{
				Turn_Led(LED2,OFF);
				Turn_Led(LED3,OFF);
				Turn_Led(LED4,ON);
				break;
			}
		}		
		os_dly_wait(30);
	}
	
	// Start the task selected
	switch (stateArrow)
	{
		case 0:
		{
			os_tsk_create (taskUnicorn, 10);				
			break;
		}
		case 1:
		{
			os_tsk_create (taskSOR, 10);
			break;
		}
		case 2:
		{
			os_tsk_create (taskZelda, 10);
			break;
		}
	}
	
	// Destroy the task
	os_tsk_delete_self ();
	while (1){};
}

/*----------------------------------------------------------------------------
 *   Task 1:  RTX Kernel starts this task with os_sys_init (taskMenu)
 *---------------------------------------------------------------------------*/
/*__task void taskDemo (void) 
{}*/


