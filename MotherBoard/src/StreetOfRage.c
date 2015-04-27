#include "StreetOfRage.h"

void initSOR(){
	/* 
		Pour test Street of rage
	*/
	GPU_ConfigurePlane(Plane_One,START_ADRESSE_DATA_PLANE1,960,240);
	GPU_ConfigurePlane(Plane_Two,START_ADRESSE_DATA_PLANE2,320,240);
	GPU_ConfigurePlane(Plane_Three,START_ADRESSE_DATA_PLANE3,320,240);
	GPU_ConfigurePlane(Plane_Four,START_ADRESSE_DATA_PLANE4,320,240);
	
	
	PLANE.Enable =1;
	PLANE.Alpha_On =1;
	PLANE.Plan_Enable = 0x7;
	PLANE.Test_On=0;
	
	GPU_MAJ_PLAN();
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

	Etat_Led state = ON;

	GPU_Color Couleur;
	
	char mess[30] = "YOU WIN !!";

	uint32_t touche;
		
	uint32_t base = 0x0100000;
	
	uint32_t base_b = 0x0300000;

	GPU_Image Axel;
	GPU_Image Blaze;
		
	GPU_NewImage(&Axel,320,240,"axel",base);
	GPU_NewImage(&Blaze,320,240,"Blaze",base_b);
	
	GPU_ClearRect(Plane_Two,0,0,320,240);

	Wait(100000);
	GPU_ClearRect(Plane_Three,0,0,320,240);

	Wait(100000);


	GPU_BitBlitRectV2 (0,15,50,75,&Axel,Plane_Two,120,100);
	


	
	while(1)
	{
		Turn_Led(LED1,state);	
		if (state == ON)
		{
			state = OFF;
		}
		else
		{
			state = ON;
		}
		
		
		touche = JOY_GetKeys();
		
		if (boss_hit == 1)
		{
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (275,170,40,65,&Blaze,Plane_Three,160,100);
			Wait(10000000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (185,170,80,60,&Blaze,Plane_Three,160,110);
			Wait(10000000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (115,170,80,55,&Blaze,Plane_Three,160,115);
			Wait(10000000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(1000000);
			GPU_BitBlitRectV2 (115,170,80,60,&Blaze,Plane_Three,160,115);
			Wait(5000000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(500000);
			GPU_BitBlitRectV2 (115,170,60,60,&Blaze,Plane_Three,160,115);
			Wait(800000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (115,170,60,60,&Blaze,Plane_Three,160,115);
			Wait(800000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (115,170,60,60,&Blaze,Plane_Three,160,115);
			Wait(800000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			boss_hit = 0;
			
	
			

			GPU_NewColor(&Couleur,255,0,0,255);

			GPU_FillRect (Plane_Three,110,40,120,50,Couleur);
						Wait(100000);

			GPU_NewColor(&Couleur,0,0,0,255);

			GPU_DrawRect (Plane_Three,113,43,110+116,40+46,Couleur);
			Wait(100000);
			GPU_DrawRect (Plane_Three,113,43,110+116,40+46,Couleur);
			Wait(100000);
			GPU_DrawRect (Plane_Three,113,43,110+116,40+46,Couleur);
			Wait(100000);
			GPU_DrawRect (Plane_Three,113,43,110+116,40+46,Couleur);
			Wait(100000);
			GPU_NewColor(&Couleur,0,0,0,255);

			
			GPU_WriteText (Plane_Three, 140, 60, mess, Couleur);
			Wait(100000);

			GPU_WriteText (Plane_Three, 140, 60, mess, Couleur);
			Wait(100000);

			GPU_WriteText (Plane_Three, 140, 60, mess, Couleur);


	
		}
		
		if (event_boss == 1 && go_boss == 1)
		{
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (280,15,40,75,&Blaze,Plane_Three,290,100);
			Wait(8000000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (235,15,40,75,&Blaze,Plane_Three,270,100);
			Wait(8000000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (195,15,40,75,&Blaze,Plane_Three,250,100);
			Wait(8000000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (150,15,50,75,&Blaze,Plane_Three,230,100);
			Wait(8000000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (280,15,40,75,&Blaze,Plane_Three,210,100);
			Wait(8000000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (235,15,40,75,&Blaze,Plane_Three,190,100);
			Wait(8000000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (195,15,40,75,&Blaze,Plane_Three,170,100);
			Wait(8000000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (150,15,50,75,&Blaze,Plane_Three,150,100);
			Wait(8000000);
			GPU_ClearRect(Plane_Three,0,0,320,240);
			Wait(100000);
			GPU_BitBlitRectV2 (280,90,50,75,&Blaze,Plane_Three,150,100);
			go_boss = 0;
			boss_ready = 1;
			
		}
		
		
		switch(touche)
		{
			case JOY_RIGHT :
				if (Plane_One.ScrollDx <= 620 && event_boss ==0)
					{
					st = 0;
					GPU_ClearRect(Plane_Two,0,0,320,240);
					Wait(100000);

					switch (etat_a)
						{
						case 0:
							GPU_BitBlitRectV2 (0,90,50,75,&Axel,Plane_Two,120,100);
							GPU_HScroll (Plane_One, 5, 1);
							etat_a ++;
							break;
						case 1:
							GPU_BitBlitRectV2 (45,90,50,75,&Axel,Plane_Two,120,100);
							GPU_HScroll (Plane_One, 5, 1);
							etat_a ++;
							break;
						case 2:
							GPU_BitBlitRectV2 (100,90,45,75,&Axel,Plane_Two,120,100);
							GPU_HScroll (Plane_One, 5, 1);
							etat_a ++;
							break;
						case 3:
							GPU_BitBlitRectV2 (145,90,50,75,&Axel,Plane_Two,120,100);
							GPU_HScroll (Plane_One, 5, 1);
							etat_a =0;
							break;
						}
					Wait(4000000);
					}
					else
					{
						event_boss = 1;
					}
					break;
			case JOY_CENTER :
					if ( st == 0)
					{
						GPU_ClearRect(Plane_Two,0,0,320,240);
						Wait(100000);
						GPU_BitBlitRectV2 (0,15,50,75,&Axel,Plane_Two,120,100);
						st = 1;
					}
				break;
			case JOY_LEFT :
				if (Plane_One.ScrollDx >= 1 && event_boss ==0)
					{
						st = 0;
						GPU_ClearRect(Plane_Two,0,0,320,240);
						Wait(100000);

						switch (etat_m)
						{
							case 0:
								GPU_BitBlitRectV2 (0,90,50,75,&Axel,Plane_Two,120,100);
								GPU_HScroll (Plane_One, 5, 0);
								etat_m ++;
								break;
							case 1:
								GPU_BitBlitRectV2 (45,90,50,75,&Axel,Plane_Two,120,100);
								GPU_HScroll (Plane_One, 5, 0);
								etat_m ++;
								break;
							case 2:
								GPU_BitBlitRectV2 (100,90,45,75,&Axel,Plane_Two,120,100);
								GPU_HScroll (Plane_One, 5, 0);
								etat_m ++;
								break;
							case 3:
								GPU_BitBlitRectV2 (145,90,50,75,&Axel,Plane_Two,120,100);
								GPU_HScroll (Plane_One, 5, 0);
								etat_m =0;
								break;
						}
					Wait(4000000);
					}
				break;
		}
			
				
	
		if(!is_button_pressed(USER))
		{
			GPU_ClearRect(Plane_Two,120,100,80,75);
			Wait(100000);
			GPU_BitBlitRectV2 (60,15,80,75,&Axel,Plane_Two,120,100);
			Wait(10000000);
			while (!is_button_pressed(USER)) {}

			GPU_ClearRect(Plane_Two,120,100,80,75);
			Wait(100000);
			GPU_BitBlitRectV2 (0,15,50,75,&Axel,Plane_Two,120,100);
			if (boss_ready == 1)
			{
				boss_hit =1;
				boss_ready = 0;
			}
		}
		
		if(!is_button_pressed(TAMPER))
		{
			GPU_ClearRect(Plane_Two,120,100,80,75);
			Wait(100000);
			GPU_BitBlitRectV2 (190,15,80,75,&Axel,Plane_Two,120,100);
			Wait(10000000);
			while (!is_button_pressed(TAMPER)) {}

			GPU_ClearRect(Plane_Two,120,100,80,75);
			Wait(100000);
			GPU_BitBlitRectV2 (0,15,50,75,&Axel,Plane_Two,120,100);
			if (boss_ready == 1)
			{
				boss_hit =1;
				boss_ready = 0;
			}	
		
			
		}
		
	}

}
