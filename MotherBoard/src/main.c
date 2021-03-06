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

/* Demo task */
__task void taskDemo (void) ;

/* Credit task */
__task void taskCredit (void);

/* Main program : Initialize the system and start the first task */
int main (void)
{	
	Initialize_Button(USER);
	Initialize_Button(TAMPER);

	Initialize_Led(LED1);
	Initialize_Led(LED2);
	Initialize_Led(LED3);
	Initialize_Led(LED4);
	Initialize_Led(LED5);
	Initialize_Led(LED6);
	Initialize_Led(LED7);
	Initialize_Led(LED8);
	
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
	GPU_Color clearColor;
	int stateArrow = 0;
	uint8_t arrowX = 0;
	uint8_t arrowY = 0;
	
	uint32_t joystick;
	int stateOutput = 1;
	
	// Set the task priority
	id1 = os_tsk_self ();
  os_tsk_prio_self (1);
	
	// Configure the layer for the console menu
	GPU_ConfigureLayer(&Layer_1,LAYER1_START_ADDRESS,320,240);
	GPU_ConfigureLayer(&Layer_2,LAYER2_START_ADDRESS,320,240);
	GPU_ConfigureLayer(&Layer_3,LAYER3_START_ADDRESS,320,240);
	GPU_ConfigureLayer(&Layer_4,LAYER4_START_ADDRESS,320,240);

	Display_conf.Enable =1;
	Display_conf.Alpha_On =1;
	Display_conf.Plan_Enable = 0xF;
	Display_conf.Test_On=0;
	
	GPU_UpdateDisplayConfig();
	
	GPU_HScroll (&Layer_1, 0,1);
	GPU_VScroll (&Layer_1, 0,1);
	
	GPU_HScroll (&Layer_2, 0,1);
	GPU_VScroll (&Layer_2, 0,1);
	
	GPU_HScroll (&Layer_3, 0,1);
	GPU_VScroll (&Layer_3, 0,1);
	
	GPU_HScroll (&Layer_4, 0,1);
	GPU_VScroll (&Layer_4, 0,1);
						
	GPU_ConfigureOutput(MODE_VGA);
	
	GPU_ClearScreen(&Layer_1);
	GPU_ClearScreen(&Layer_2);
	clearColor.R = 0;
	clearColor.G = 0;
	clearColor.B = 0;
	clearColor.A = 0;
	GPU_FillRect (&Layer_2,0,0,320,240, clearColor);
	GPU_ClearScreen(&Layer_3);
	GPU_FillRect (&Layer_4,0,0,320,240, clearColor);
	GPU_ClearScreen(&Layer_4);
	
	// Load the image from the SD card to the graphic card
	GPU_NewImage(&background, 320, 240,"menu", 0x0500000);
	SD_LoadImage(&background, 320, 240, &fil);
	GPU_BitBlitI2L(&background, 0, 0, 320, 240,&Layer_1, 0,0);
	
	// Display the two optionnal menu
	aColor.R = 255;
	aColor.G = 255;
	aColor.B = 255;
	aColor.A = 255;
	GPU_WriteText(&Layer_3, 76, 188, "->  Demo", aColor);
	GPU_WriteText(&Layer_3, 40, 220, "Credits", aColor);
	GPU_WriteText(&Layer_3, 220, 220, "Output :", aColor);			
			
	// Display the selector to the first programm
	aColor.R = 7;
	aColor.G = 1;
	aColor.B = 15;
	aColor.A = 15;
	GPU_FillRect (&Layer_2,60,108,10,10, aColor);
	
	if ( stateOutput == 1)
	{
		GPU_WriteText(&Layer_4, 270, 220, "VGA", aColor);
	}
	else
	{
		GPU_WriteText(&Layer_4, 270, 220, "LCD", aColor);
	}
	
	while((is_button_pressed(USER) && joystick != JOY_RIGHT) || stateArrow == 5 )
	{
		joystick = JOY_GetKeys();
		if (joystick == JOY_UP)
		{
			if (stateArrow == 0)
			{
				stateArrow = 5;
			}
			else
			{
				stateArrow--;
			}
		}
		if (joystick == JOY_DOWN)
		{
			stateArrow++;
			stateArrow = stateArrow % 6;
		}
		
		if (stateArrow == 4)
		{
				arrowX = 20;
				arrowY = 215;
		}
		else if (stateArrow == 5)
		{
			arrowX = 200;
			arrowY = 215;					
		}
		else
		{
			arrowX = 60;
			arrowY = 108 + 26*stateArrow;
		}
		
			// Update the position of the selector
			GPU_ClearScreen(&Layer_2);
			GPU_FillRect (&Layer_2,arrowX ,arrowY,10,10, aColor);
		
		switch (stateArrow)
		{
			case 0:
			{
				Turn_Led(LED2,ON);
				Turn_Led(LED3,OFF);
				Turn_Led(LED4,OFF);
				Turn_Led(LED5,OFF);
				Turn_Led(LED6,OFF);
				Turn_Led(LED7,OFF);
				break;
			}
			case 1:
			{
				Turn_Led(LED2,OFF);
				Turn_Led(LED3,ON);
				Turn_Led(LED4,OFF);
				Turn_Led(LED5,OFF);
				Turn_Led(LED6,OFF);
				Turn_Led(LED7,OFF);
				break;
			}
			case 2:
			{
				Turn_Led(LED2,OFF);
				Turn_Led(LED3,OFF);
				Turn_Led(LED4,ON);
				Turn_Led(LED5,OFF);
				Turn_Led(LED6,OFF);
				Turn_Led(LED7,OFF);
				break;
			}
			case 3:
			{
				Turn_Led(LED2,OFF);
				Turn_Led(LED3,OFF);
				Turn_Led(LED4,OFF);
				Turn_Led(LED5,ON);
				Turn_Led(LED6,OFF);
				Turn_Led(LED7,OFF);
				break;
			}
			case 4:
			{
				Turn_Led(LED2,OFF);
				Turn_Led(LED3,OFF);
				Turn_Led(LED4,OFF);
				Turn_Led(LED5,OFF);
				Turn_Led(LED6,ON);
				Turn_Led(LED7,OFF);
				break;
			}
			case 5:
			{
				Turn_Led(LED2,OFF);
				Turn_Led(LED3,OFF);
				Turn_Led(LED4,OFF);
				Turn_Led(LED5,OFF);
				Turn_Led(LED6,OFF);
				Turn_Led(LED7,ON);
				break;
			}
		}

		if (stateArrow == 5 && !is_button_pressed(USER))
		{
			GPU_ClearScreen(&Layer_4);
			GPU_FillRect (&Layer_4,0,0,320,240, clearColor);
			if ( stateOutput == 1)
			{
				stateOutput = 0;
				GPU_WriteText(&Layer_4, 270, 220, "VGA", aColor);
				GPU_ConfigureOutput(MODE_VGA);
			}
			else
			{
				stateOutput = 1;
				GPU_WriteText(&Layer_4, 270, 220, "LCD", aColor);
				GPU_ConfigureOutput(MODE_LCD);
			}
			while(!is_button_pressed(USER));
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
		case 3:
		{
			os_tsk_create (taskDemo, 10);
			break;
		}
		case 4:
		{
			os_tsk_create (taskCredit, 10);
			break;
		}
		
	}
	
	// Destroy the task
	os_tsk_delete_self ();
	while (1){};
}

/*----------------------------------------------------------------------------
 *   Task 4:  Demo
 *---------------------------------------------------------------------------*/
int demo(void);

__task void taskDemo (void) 
{
	demo();
	
	// fin de la demo, pour relancer le menu
	os_tsk_create(taskMenu,15);
	os_tsk_delete_self ();
	while (1){};
	
}

int demo()
{
	int i;
	uint32_t touche;
	GPU_Color aColor;
	GPU_Image anImage;
	char message[25] = "Stay awhile and listen...";
	/**
	******************************************************************************
	*	Initialisation
	******************************************************************************
	*/	


	GPU_ConfigureLayer(&Layer_1, LAYER1_START_ADDRESS, 640, 480);
	GPU_ConfigureLayer(&Layer_2, LAYER2_START_ADDRESS, 320, 240);
	GPU_ConfigureLayer(&Layer_3, LAYER3_START_ADDRESS, 320, 240);
	GPU_ConfigureLayer(&Layer_4, LAYER4_START_ADDRESS, 320, 240);
		
	Display_conf.Enable =1;
	Display_conf.Alpha_On =1;
	Display_conf.Plan_Enable = 0x7;
	Display_conf.Test_On=0;
	
	GPU_UpdateDisplayConfig();
	
	GPU_HScroll (&Layer_1, 0,1);
	GPU_VScroll (&Layer_1, 0,1);
	
	GPU_HScroll (&Layer_2, 0,1);
	GPU_VScroll (&Layer_2, 0,1);
	
	GPU_HScroll (&Layer_3, 0,1);
	GPU_VScroll (&Layer_3, 0,1);
	
	GPU_HScroll (&Layer_4, 0,1);
	GPU_VScroll (&Layer_4, 0,1);
		
	GPU_ConfigureOutput(MODE_LCD);		

	wait(20000000);

	while(1)
	{
		if (!is_button_pressed(TAMPER))
		{	
			GPU_NewImage(&anImage ,70, 96, "Pikachu", Layer_3.addr);
			GPU_BitBlitL2L (&Layer_3, 0, 0, 96, 80, &Layer_2, 250, 20);			

			aColor.R = 7;
			aColor.G = 1;
			aColor.B = 15;
			aColor.A = 4;
			GPU_FillRect (&Layer_1,56,56,45,45, aColor);
	
			GPU_SetRectAlphaValue (&Layer_2,0,0,320,240,3);
			
			GPU_ClearRect(&Layer_1,0,0,50,50);	
			wait(100000);
			
			aColor.R = 8;
			aColor.G = 1;
			aColor.B = 2;
			aColor.A = 15;
			GPU_FillRect (&Layer_1,56,56,45,45, aColor);
	
			GPU_SetRectAlphaValue (&Layer_2,0,0,320,240,12);
			
			wait(100000);
		}
		
		if(!is_button_pressed(USER))
		{
			aColor.R = 15;
			aColor.G = 8;
			aColor.B = 2;
			aColor.A = 15;			
			GPU_DrawCircle(&Layer_3, 15, 90, 10, aColor);
			aColor.R = 8;
			aColor.G = 15;
			aColor.B = 12;
			aColor.A = 15;
			GPU_DrawLine(&Layer_3, 100, 100, 200, 200, aColor);
			
			wait(1000000);
			
			aColor.R = 15;
			aColor.G = 8;
			aColor.B = 2;
			aColor.A = 15;
			GPU_DrawLine(&Layer_3, 100, 100, 200, 200, aColor);
			aColor.R = 8;
			aColor.G = 15;
			aColor.B = 12;
			GPU_DrawCircle(&Layer_3, 15, 90, 10, aColor);
			GPU_ClearRect(&Layer_3,10,200,200,20);
			GPU_WriteText (&Layer_3, 10, 200, message, aColor);
		
		
			GPU_ClearRect(&Layer_1,200,10,320,240);
			while(!is_button_pressed(USER));
			while(is_button_pressed(USER));
			while(!is_button_pressed(USER));
					
			GPU_PreSendDataToLayer(200, 10, 320, 240, &Layer_1);
			GPU_DMAStartTransfer();	
			for(i=0; i<(320*240); i++){
				GPU_DATA16 = 0xf000|i;
			}
			GPU_DMAStopTransfer();	
			
			while(!is_button_pressed(USER));
			while(is_button_pressed(USER));
			while(!is_button_pressed(USER));
			
			GPU_ClearScreen(&Layer_1);
			
			while(!is_button_pressed(USER));
			while(is_button_pressed(USER));
			while(!is_button_pressed(USER));
			
			SD_LoadImageToLayer(&Layer_1, 640, 480, &fil, "zelda_bg.bin");
		}
		
		touche = JOY_GetKeys();
		if(touche&JOY_RIGHT){
			if (Layer_1.scrDx <= 320){
				GPU_HScroll (&Layer_1, 1, 1);
			}
		}
		if(touche&JOY_LEFT){
			if (Layer_1.scrDx > 0){
				GPU_HScroll (&Layer_1, 1, 0);
			}
		}
		if(touche&JOY_UP){
			if (Layer_1.scrDy > 0){
				GPU_VScroll (&Layer_1, 1, 0);
			}
		}
		if(touche&JOY_DOWN){
			if (Layer_1.scrDy <= 240){
				GPU_VScroll (&Layer_1, 1, 1);
			}
		}
		wait(1000000);
	} //Fin boucle principale

} //Fin demo













/*----------------------------------------------------------------------------
 *   Task 5:  Credit
 *---------------------------------------------------------------------------*/
__task void taskCredit (void) 
{
	GPU_Image credit;
	
	GPU_ConfigureLayer(&Layer_1,LAYER1_START_ADDRESS,320,240);

	Display_conf.Enable =1;
	Display_conf.Alpha_On =1;
	Display_conf.Plan_Enable = 0x1;
	Display_conf.Test_On=0;
	
	GPU_UpdateDisplayConfig();
	
	GPU_HScroll (&Layer_1, 0,1);
	GPU_VScroll (&Layer_1, 0,1);
	
	// Load the image from the SD card to the graphic card
	GPU_NewImage(&credit, 320, 240,"credit", 0x0500000);
	SD_LoadImage(&credit, 320, 240, &fil);
	GPU_BitBlitI2L(&credit, 0, 0, 320, 240,&Layer_1, 0,0);
	
	// Waiting the user to press the user button
	while(is_button_pressed(USER));	
	
	// fin de la demo, pour relancer le menu
	os_tsk_create(taskMenu,15);
	os_tsk_delete_self ();
	while (1){};
	
}



