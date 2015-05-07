#include "Licorne.h"

void initGIF()
{
		GPU_Color aColor;

	
	/*
			Pour test GIF unicorn
	*/
	GPU_ConfigureLayer(&Layer_1, LAYER1_START_ADDRESS, 320, 240);
	GPU_ConfigureLayer(&Layer_2, LAYER2_START_ADDRESS, 3200, 240);
	
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
}

void GIF(GPU_Layer *layer)
{	
	GPU_HScroll (layer, 320, 1);
	wait(5000000);
	
	GPU_HScroll (layer, 320, 1);
	wait(5000000);

	GPU_HScroll (layer, 320, 1);
	wait(5000000);
	
	GPU_HScroll (layer, 320, 1);
	wait(5000000);
	
	GPU_HScroll (layer, 320, 1);
	wait(5000000);
	
	GPU_HScroll (layer, 320, 1);
	wait(5000000);
	
	GPU_HScroll (layer, 320, 1);
	wait(5000000);
	
	GPU_HScroll (layer, 320, 1);
	wait(5000000);
	
	GPU_HScroll (layer, 320, 1);
	wait(5000000);
		
	GPU_HScroll (layer, 3200, 0);
	wait(5000000);
}

__task void taskUnicorn (void)
{
	// Initialize the GIF unicorn
	GPU_Image back;
	GPU_Image unicorn;
	
	uint8_t stateGif = 0;
	
	GPU_NewImage(&back, 320, 240, "back" ,Layer_1.addr);
	// SD_LoadImage(&back, Plane_One, 0, 0, &fil);
	GPU_NewImage(&unicorn, 3200, 240, "uni", Layer_2.addr);
	// SD_LoadImage(&unicorn, Plane_Two, 0, 0, &fil);
	
	initGIF();
	
	while(is_button_pressed(TAMPER))
	{
		Toggle_Led(LED3);
		stateGif++;
		
		if (stateGif == 10)
		{
				GPU_HScroll (&Layer_2, 3200, 0);
				stateGif = 0;
		}
		else
		{
				GPU_HScroll (&Layer_2, 320, 1);
		}	
		//wait(500000);
		os_dly_wait(20);

	}
	
	//rt_sem_send(Sem_Menu);
	os_tsk_create(taskMenu,15);
	os_tsk_delete_self ();
}

