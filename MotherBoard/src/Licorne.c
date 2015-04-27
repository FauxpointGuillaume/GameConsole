#include "Licorne.h"

void initGIF(){
	/*
			Pour test GIF unicorn
	*/
	GPU_ConfigurePlane(Plane_One,START_ADRESSE_DATA_PLANE1,320,240);
	GPU_ConfigurePlane(Plane_Two,START_ADRESSE_DATA_PLANE2,3200,240);
	GPU_ConfigurePlane(Plane_Three,START_ADRESSE_DATA_PLANE3,320,240);
	GPU_ConfigurePlane(Plane_Four,START_ADRESSE_DATA_PLANE4,320,240);

	PLANE.Enable =1;
	PLANE.Alpha_On =1;
	PLANE.Plan_Enable = 0x3;
	PLANE.Test_On=0;
	
	GPU_MAJ_PLAN();
}


void GIF(GPU_Plane plane)
{	
	GPU_HScroll (plane, 320, 1);
	Wait(5000000);
	
	GPU_HScroll (plane, 320, 1);
	Wait(5000000);

	GPU_HScroll (plane, 320, 1);
	Wait(5000000);
	
	GPU_HScroll (plane, 320, 1);
	Wait(5000000);
	
	GPU_HScroll (plane, 320, 1);
	Wait(5000000);
	
	GPU_HScroll (plane, 320, 1);
	Wait(5000000);
	
	GPU_HScroll (plane, 320, 1);
	Wait(5000000);
	
	GPU_HScroll (plane, 320, 1);
	Wait(5000000);
	
	GPU_HScroll (plane, 320, 1);
	Wait(5000000);
		
	GPU_HScroll (plane, 3200, 0);
	Wait(5000000);
}


