#include "StreetOfRage.h"

void initSOR(){
	/* 
		Configure the plane
	*/
	GPU_ConfigureLayer(&Layer_1, LAYER1_START_ADDRESS, 960, 240);
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
}

void shortMovieEnding(GPU_Image *image)
{
	GPU_Color Couleur;	
	char mess[30] = "YOU WIN !!";
	
	GPU_ClearRect(&Layer_3,0,0,320,240);
	wait(100000);
	GPU_BitBlitI2L(image, 275,170,40,65,&Layer_3,160,100);
	wait(100000);
	GPU_ClearRect(&Layer_3,0,0,320,240);
	wait(100000);
	GPU_BitBlitI2L (image,185,170,80,60,&Layer_3,160,110);
	wait(100000);
	GPU_ClearRect(&Layer_3,0,0,320,240);
	wait(100000);
	GPU_BitBlitI2L (image,115,170,80,55,&Layer_3,160,115);
	wait(100000);
	GPU_ClearRect(&Layer_3,0,0,320,240);
	wait(100000);
	GPU_BitBlitI2L (image,115,170,80,60,&Layer_3,160,115);
	wait(100000);
	GPU_ClearRect(&Layer_3,0,0,320,240);
	wait(100000);
	GPU_BitBlitI2L (image,115,170,60,60,&Layer_3,160,115);
	wait(100000);
	GPU_ClearRect(&Layer_3,0,0,320,240);
	wait(100000);
	GPU_BitBlitI2L (image,115,170,60,60,&Layer_3,160,115);
	wait(800000);
	GPU_ClearRect(&Layer_3,0,0,320,240);
	wait(100000);
	GPU_BitBlitI2L (image,115,170,60,60,&Layer_3,160,115);
	wait(800000);
	GPU_ClearRect(&Layer_3,0,0,320,240);
	wait(100000);
	GPU_NewColor(&Couleur,255,0,0,255);
	GPU_FillRect (&Layer_3,110,40,120,50,Couleur);
	wait(100000);
	GPU_NewColor(&Couleur,0,0,0,255);
	GPU_DrawRect (&Layer_3,113,43,110+116,40+46,Couleur);
	wait(100000);
	GPU_DrawRect (&Layer_3,113,43,110+116,40+46,Couleur);
	wait(100000);
	GPU_DrawRect (&Layer_3,113,43,110+116,40+46,Couleur);
	wait(100000);
	GPU_DrawRect (&Layer_3,113,43,110+116,40+46,Couleur);
	wait(100000);
	GPU_NewColor(&Couleur,0,0,0,255);	
	GPU_WriteText (&Layer_3, 140, 60, mess, Couleur);
	wait(100000);
	GPU_WriteText (&Layer_3, 140, 60, mess, Couleur);
	wait(100000);
	GPU_WriteText (&Layer_3, 140, 60, mess, Couleur);
	
	wait(100000);
	
}



void StreetOfRage()
{
	int etat_a =0;
	int etat_m =0;
//	int etat_j =0;
	int event_boss = 0;
	int st = 0;
	int go_boss = 1;
	int boss_ready = 0;
	int boss_hit = 0;

	uint32_t touche;
	
	uint32_t base = 0x0100000;
	uint32_t base_b = 0x0300000;

	GPU_Image Axel;
	GPU_Image Blaze;
		
	GPU_NewImage(&Axel,320,240,"axel",base);
	SD_LoadImage(&Axel, 0, 0, &fil);
	GPU_NewImage(&Blaze,320,240,"blaze",base_b);
	SD_LoadImage(&Blaze, 0, 0, &fil);
	
	GPU_ClearRect(&Layer_2,0,0,320,240);

	wait(100000);
	GPU_ClearRect(&Layer_3,0,0,320,240);

	wait(100000);
	GPU_BitBlitI2L (&Axel,0,15,50,75,&Layer_2,120,100);
	
	while(1)
	{
		Toggle_Led(LED1);	
		touche = JOY_GetKeys();
		
		if (boss_hit == 1)
		{
			shortMovieEnding(&Blaze);
			boss_hit = 0;
			return;
		}
		
		if (event_boss == 1 && go_boss == 1)
		{
			GPU_ClearRect(&Layer_3,0,0,320,240);
			wait(100000);
			GPU_BitBlitI2L (&Blaze,280,15,40,75,&Layer_3,290,100);
			wait(8000000);
			GPU_ClearRect(&Layer_3,0,0,320,240);
			wait(100000);
			GPU_BitBlitI2L (&Blaze,235,15,40,75,&Layer_3,270,100);
			wait(8000000);
			GPU_ClearRect(&Layer_3,0,0,320,240);
			wait(100000);
			GPU_BitBlitI2L (&Blaze,195,15,40,75,&Layer_3,250,100);
			wait(8000000);
			GPU_ClearRect(&Layer_3,0,0,320,240);
			wait(100000);
			GPU_BitBlitI2L (&Blaze,150,15,50,75,&Layer_3,230,100);
			wait(8000000);
			GPU_ClearRect(&Layer_3,0,0,320,240);
			wait(100000);
			GPU_BitBlitI2L (&Blaze,280,15,40,75,&Layer_3,210,100);
			wait(8000000);
			GPU_ClearRect(&Layer_3,0,0,320,240);
			wait(100000);
			GPU_BitBlitI2L (&Blaze,235,15,40,75,&Layer_3,190,100);
			wait(8000000);
			GPU_ClearRect(&Layer_3,0,0,320,240);
			wait(100000);
			GPU_BitBlitI2L (&Blaze,195,15,40,75,&Layer_3,170,100);
			wait(8000000);
			GPU_ClearRect(&Layer_3,0,0,320,240);
			wait(100000);
			GPU_BitBlitI2L (&Blaze,150,15,50,75,&Layer_3,150,100);
			wait(8000000);
			GPU_ClearRect(&Layer_3,0,0,320,240);
			wait(100000);
			GPU_BitBlitI2L (&Blaze,280,90,50,75,&Layer_3,150,100);
			go_boss = 0;
			boss_ready = 1;
			
		}
		
		
		switch(touche)
		{
			case JOY_RIGHT :
				if (Layer_1.scrDx <= 620 && event_boss ==0)
					{
					st = 0;
					GPU_ClearRect(&Layer_2,0,0,320,240);
					wait(100000);

					switch (etat_a)
						{
						case 0:
							GPU_BitBlitI2L (&Axel,0,90,50,75,&Layer_2,120,100);
							GPU_HScroll (&Layer_1, 5, 1);
							etat_a ++;
							break;
						case 1:
							GPU_BitBlitI2L (&Axel,45,90,50,75,&Layer_2,120,100);
							GPU_HScroll (&Layer_1, 5, 1);
							etat_a ++;
							break;
						case 2:
							GPU_BitBlitI2L (&Axel,100,90,45,75,&Layer_2,120,100);
							GPU_HScroll (&Layer_1, 5, 1);
							etat_a ++;
							break;
						case 3:
							GPU_BitBlitI2L (&Axel,145,90,50,75,&Layer_2,120,100);
							GPU_HScroll (&Layer_1, 5, 1);
							etat_a =0;
							break;
						}
					wait(4000000);
					}
					else
					{
						event_boss = 1;
					}
					break;
			case JOY_CENTER :
					if ( st == 0)
					{
						GPU_ClearRect(&Layer_2,0,0,320,240);
						wait(100000);
						GPU_BitBlitI2L (&Axel,0,15,50,75,&Layer_2,120,100);
						st = 1;
					}
				break;
			case JOY_LEFT :
				if (Layer_1.scrDx >= 1 && event_boss ==0)
					{
						st = 0;
						GPU_ClearRect(&Layer_2,0,0,320,240);
						wait(100000);

						switch (etat_m)
						{
							case 0:
								GPU_BitBlitI2L (&Axel,0,90,50,75,&Layer_2,120,100);
								GPU_HScroll (&Layer_1, 5, 0);
								etat_m ++;
								break;
							case 1:
								GPU_BitBlitI2L (&Axel,45,90,50,75,&Layer_2,120,100);
								GPU_HScroll (&Layer_1, 5, 0);
								etat_m ++;
								break;
							case 2:
								GPU_BitBlitI2L (&Axel,100,90,45,75,&Layer_2,120,100);
								GPU_HScroll (&Layer_1, 5, 0);
								etat_m ++;
								break;
							case 3:
								GPU_BitBlitI2L (&Axel,145,90,50,75,&Layer_2,120,100);
								GPU_HScroll (&Layer_1, 5, 0);
								etat_m =0;
								break;
						}
					wait(4000000);
					}
				break;
		}
			
				
	
		if(!is_button_pressed(USER))
		{
			GPU_ClearRect(&Layer_2,120,100,80,75);
			wait(100000);
			GPU_BitBlitI2L (&Axel,60,15,80,75,&Layer_2,120,100);
			wait(10000000);
			while (!is_button_pressed(USER)) {}

			GPU_ClearRect(&Layer_2,120,100,80,75);
			wait(100000);
			GPU_BitBlitI2L (&Axel,0,15,50,75,&Layer_2,120,100);
			if (boss_ready == 1)
			{
				boss_hit =1;
				boss_ready = 0;
			}
		}
		
		if(!is_button_pressed(TAMPER))
		{
			GPU_ClearRect(&Layer_2,120,100,80,75);
			wait(100000);
			GPU_BitBlitI2L (&Axel,190,15,80,75,&Layer_2,120,100);
			wait(10000000);
			while (!is_button_pressed(TAMPER)) {}

			GPU_ClearRect(&Layer_2,120,100,80,75);
			wait(100000);
			GPU_BitBlitI2L (&Axel,0,15,50,75,&Layer_2,120,100);
			if (boss_ready == 1)
			{
				boss_hit =1;
				boss_ready = 0;
			}				
		}		
	}
}

__task void taskSOR (void)
{
	initSOR();
	
	Toggle_Led(LED2);		
	StreetOfRage();
	
	os_dly_wait(100);
	
	os_tsk_create(taskMenu,15);
	os_tsk_delete_self ();
	
}
