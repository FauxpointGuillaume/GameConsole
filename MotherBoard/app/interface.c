#include "interface.h"

/**
  ******************************************************************************
	*	GLOBAL VARIABLES
  ******************************************************************************
  */

GPU_Display_conf Display_conf;

GPU_Layer Layer_1;
GPU_Layer Layer_2;
GPU_Layer Layer_3;
GPU_Layer Layer_4;

/**
  ******************************************************************************
	*	SERVICES
  ******************************************************************************
  */



/***** Groupe Init/Config *****/

	// Initialisation de la CG (Voir les registre mis en jeu)
	void GPU_Init(void){
		GPU_init_GPIO_interface();
		GPU_initFSMC();
		GPU_setClockFSMC((int) GPU_DIVISION_CLOCK_FSMC);
		
		GPU_InitLayer(&Layer_1,1);
		GPU_InitLayer(&Layer_2,2);
		GPU_InitLayer(&Layer_3,3);
		GPU_InitLayer(&Layer_4,4);
		
		/*GPU_ConfigureLayer(&Layer_1, 0, 0, 0);
		GPU_ConfigureLayer(&Layer_2, 0, 0, 0);
		GPU_ConfigureLayer(&Layer_3, 0, 0, 0);
		GPU_ConfigureLayer(&Layer_4, 0, 0, 0);

		GPU_HScroll (Plan_Un, 0,1);
		GPU_VScroll (Plan_Un, 0,1);
		GPU_HScroll (Plan_Deux, 0,1);
		GPU_VScroll (Plan_Deux, 0,1);
		GPU_HScroll (Plan_Trois, 0,1);
		GPU_VScroll (Plan_Trois, 0,1);
		GPU_HScroll (Plan_Quatre, 0,1);
		GPU_VScroll (Plan_Quatre, 0,1);
		*/
		
		Display_conf.Enable = 1;
		Display_conf.Alpha_On = 0;
		Display_conf.Plan_Enable = 0x0;
		Display_conf.Test_On = 0;
		GPU_UpdateDisplayConfig();

		GPU_ConfigureOutput(MODE_LCD);
	}


	// Choix du mode LCD ou VGA 
	void GPU_ConfigureOutput(uint8_t output){
		switch (output)
		{
			case MODE_VGA :
				GPU_WriteReg(DCMODE,MODE_VGA);
			break;
			
			case MODE_LCD :
				GPU_WriteReg(DCMODE,MODE_LCD);
			break;
			default :
			break;
		}
	}


	// Test de la CG
	void GPU_VideoSignalTest(uint8_t testOn){
		Display_conf.Test_On = testOn;
		GPU_UpdateDisplayConfig();
	}

/***** Creation d'un pixel de couleur *****/

	void GPU_NewColor(GPU_Color *color, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha){
		color->R = red;
		color->G = green;
		color->B = blue;
		color->A = alpha;
	}	
	
/***** Création d'une structure d'une image *****/
	void GPU_NewImage(GPU_Image *image, uint16_t width, uint16_t height, char * name, uint32_t addr){
		int i;
		for(i=0; i<31; i++){
				image->name[i] = name[i];
				if(name[i] == 0)
					break;
		}		
  	image->name[31] = 0;
		
		image->height = height;
		image->width = width;
		image->addr = addr;		
	}


	
/***** Send data for struct PLAN *****/
	void GPU_InitLayer(GPU_Layer* layer, uint8_t no){
		layer->no = no;
		layer->addr = 0;
		layer->width = 0;
		layer->height = 0;
		layer->scrDx = 0;
		layer->scrDy = 0;
		switch (layer->no)
		{
		case 1 :
			GPU_WriteReg(FBP1ADDR_L, 0x0000);
			GPU_WriteReg(FBP1ADDR_H, 0x0000);
			GPU_WriteReg(FBP1SIZE_L, 0x0000);
			GPU_WriteReg(FBP1SIZE_H, 0x0000);
			GPU_WriteReg(FBP1SCRL_L, 0x0000);
			GPU_WriteReg(FBP1SCRL_H, 0x0000);
			break;
		case 2 :
			GPU_WriteReg(FBP2ADDR_L, 0x0000);
			GPU_WriteReg(FBP2ADDR_H, 0x0000);
			GPU_WriteReg(FBP2SIZE_L, 0x0000);
			GPU_WriteReg(FBP2SIZE_H, 0x0000);
			GPU_WriteReg(FBP2SCRL_L, 0x0000);
			GPU_WriteReg(FBP2SCRL_H, 0x0000);
			break;
		case 3 :
			GPU_WriteReg(FBP3ADDR_L, 0x0000);
			GPU_WriteReg(FBP3ADDR_H, 0x0000);
			GPU_WriteReg(FBP3SIZE_L, 0x0000);
			GPU_WriteReg(FBP3SIZE_H, 0x0000);
			GPU_WriteReg(FBP3SCRL_L, 0x0000);
			GPU_WriteReg(FBP3SCRL_H, 0x0000);
			break;
		case 4 :
			GPU_WriteReg(FBP4ADDR_L, 0x0000);
			GPU_WriteReg(FBP4ADDR_H, 0x0000);
			GPU_WriteReg(FBP4SIZE_L, 0x0000);
			GPU_WriteReg(FBP4SIZE_H, 0x0000);
			GPU_WriteReg(FBP4SCRL_L, 0x0000);
			GPU_WriteReg(FBP4SCRL_H, 0x0000);
			break;
		}
	}

	//Configuration des différents plans
	void GPU_ConfigureLayer(GPU_Layer* layer, uint32_t layerAddr, uint16_t layerWidth, uint16_t layerHeight){
			layer->addr = layerAddr;
			layer->width = layerWidth;
			layer->height = layerHeight;
			switch (layer->no)
			{
			case 1 :
				GPU_WriteReg(FBP1ADDR_L,(layerAddr& 0xFFFF));
				GPU_WriteReg(FBP1ADDR_H,((layerAddr& 0xFFFF0000)>>16));
				GPU_WriteReg(FBP1SIZE_L,(layerWidth & 0xFFFF));
				GPU_WriteReg(FBP1SIZE_H,(layerHeight & 0xFFFF));
				break;
			case 2 :
				GPU_WriteReg(FBP2ADDR_L,(layerAddr& 0xFFFF));
				GPU_WriteReg(FBP2ADDR_H,((layerAddr& 0xFFFF0000)>>16));
				GPU_WriteReg(FBP2SIZE_L,(layerWidth & 0xFFFF));
				GPU_WriteReg(FBP2SIZE_H,(layerHeight & 0xFFFF));
				break;
			case 3 :
				GPU_WriteReg(FBP3ADDR_L,(layerAddr& 0xFFFF));
				GPU_WriteReg(FBP3ADDR_H,((layerAddr& 0xFFFF0000)>>16));
				GPU_WriteReg(FBP3SIZE_L,(layerWidth & 0xFFFF));
				GPU_WriteReg(FBP3SIZE_H,(layerHeight & 0xFFFF));
				break;
			case 4 :
				GPU_WriteReg(FBP4ADDR_L,(layerAddr& 0xFFFF));
				GPU_WriteReg(FBP4ADDR_H,((layerAddr& 0xFFFF0000)>>16));
				GPU_WriteReg(FBP4SIZE_L,(layerWidth & 0xFFFF));
				GPU_WriteReg(FBP4SIZE_H,(layerHeight & 0xFFFF));
				break;
			}	
	}

	void GPU_UpdateDisplayConfig(void){
		uint16_t data;
		data = (Display_conf.Enable & 0x1) + ((Display_conf.Test_On & 0x1) << 1) 
				 + ((Display_conf.Plan_Enable & 0xF) << 2) + ((Display_conf.Alpha_On & 0x1) << 6);
		GPU_WriteReg(FBCTRL,data);
	}


/***** Group : Display control *****/

	// Activation des différents plans
	void GPU_EnableLayers (uint8_t layerFlags){
		Display_conf.Plan_Enable = layerFlags;
		
		GPU_UpdateDisplayConfig();	
	}

	// Choix du mode de transparence
	void GPU_TransparencyMode (uint8_t AlphaNBinary){
		Display_conf.Alpha_On = AlphaNBinary;
		
		GPU_UpdateDisplayConfig();
	}
	
	// Mis à jour du scrolling horizontal
	void GPU_HScroll (GPU_Layer* layer, uint16_t dX, uint8_t dir){
		if (dir == 1){
			if ((dX + layer->scrDx) > (layer->width - SCREEN_WIDTH)){
				layer->scrDx = layer->width - SCREEN_WIDTH;
			} else{
				layer->scrDx += dX;
			}
		} else {
			if (dX > layer->scrDx){
				layer->scrDx = 0;
			} else{
				layer->scrDx -= dX;
			}
		}
		switch (layer->no)
		{
			case 1 :
				GPU_WriteReg(FBP1SCRL_L, (layer->scrDx&0xFFFF));
				break;
			case 2 :
				GPU_WriteReg(FBP2SCRL_L, (layer->scrDx&0xFFFF));
				break;
			case 3 :
				GPU_WriteReg(FBP3SCRL_L, (layer->scrDx&0xFFFF));
				break;
			case 4 :
				GPU_WriteReg(FBP4SCRL_L, (layer->scrDx&0xFFFF));
				break;
		}
	}
				
	// Mis à jour du scrollong vertical
	void GPU_VScroll (GPU_Layer* layer, uint16_t dY, uint8_t dir){
		if (dir == 1){
			if ((dY + layer->scrDy) > (layer->height - SCREEN_HEIGTH)){
				layer->scrDy = layer->height - SCREEN_HEIGTH;
			} else{
				layer->scrDy += dY;
			}
		} else {
			if (dY > layer->scrDy){
				layer->scrDy = 0;
			} else{
				layer->scrDy -= dY;
			}
		}
		switch (layer->no)
		{
			case 1 :
				GPU_WriteReg(FBP1SCRL_H, (layer->scrDy&0xFFFF));
				break;
			case 2 :
				GPU_WriteReg(FBP2SCRL_H, (layer->scrDy&0xFFFF));
				break;
			case 3 :
				GPU_WriteReg(FBP3SCRL_H, (layer->scrDy&0xFFFF));
				break;
			case 4 :
				GPU_WriteReg(FBP4SCRL_H, (layer->scrDy&0xFFFF));
				break;
		}	
	}



/***** Configuration du LCD *****/

	int GPU_LCD_AjustContrast(uint32_t lol){
		if ( lol > 0x1F){
			GPU_WriteReg(LCDCON,0x08);
		}	else{
		GPU_WriteReg(LCDCON,lol);
		}
		
		GPU_WriteReg(LCDCTRL,1);
		return 0;
	}

	int GPU_LCD_AjusteBrightness(uint32_t lol){
		if ( lol > 0x1F){
		GPU_WriteReg(LCDBRI,0x040);
		}	else{
		GPU_WriteReg(LCDBRI,lol);
		}
			
		GPU_WriteReg(LCDCTRL,1);
		return 0;
	}

	int GPU_LCD_AjusteHS(uint32_t hue,uint32_t sat){
		uint32_t data = 0;
		if ( hue > 0x0F){
			data = 0x08 << 4;
		}	else{
			data = (hue & 0xF) << 4;
		}
		if ( sat > 0x0F){
			data += 0x08;
		}	else{
			data += (sat & 0xF);
		}
		GPU_WriteReg(LCDHS,data);
		GPU_WriteReg(LCDCTRL,1);
		return 0;
	}

	int GPU_LCD_AjusteSubBri(uint32_t red,uint32_t blue){
		uint32_t data = 0;
		if ( red > 0x3F){
			data = 0x20;
		}	else{
			data = (red & 0x3F);
		}
		if ( blue > 0x3F){
			data += (0x20 << 6);
		}	else{
			data += ((blue & 0x3F)<< 6);
		}
		GPU_WriteReg(LCDSBRI,data);
		GPU_WriteReg(LCDCTRL,1);
		return 0;
	}

/***** Group : Plan modification *****/
	
	// On verifie que le BPU est en pause avec de lancer quoique ce soit
	uint8_t GPU_checkBPU(void){
		return (GPU_ReadReg(BPUCTRL)& 0x1);
	}

	// On clear l'écran tout entier
	void GPU_ClearScreen (GPU_Layer* layer){
		GPU_ClearRect(layer, 0, 0, layer->height, layer->width);
	}


	// On rempli une zone d'une couleur donné
	void GPU_FillRect (GPU_Layer* layer, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY, GPU_Color color){
		uint32_t adresse_dest = layer->addr + x0 + y0*layer->width;
		uint16_t fill_col = ((color.R & 0xF) + ((color.G & 0xF) << 4) + ((color.B & 0xF) << 8)+ ((color.A & 0xF) << 12));

		while( GPU_checkBPU() != 0){};	
		
		GPU_WriteReg(BPUDSTADDR_L,(adresse_dest&0xFFFF));
		GPU_WriteReg(BPUDSTADDR_H,((adresse_dest&0xFFFF0000)>>16));
			
		GPU_WriteReg(BPUPICSIZE_H, (0xFFFF & layer->width));

		GPU_WriteReg(BPUSIZE_L, (dX & 0x3FF));		
		GPU_WriteReg(BPUSIZE_H, (dY & 0x3FF));		

		GPU_WriteReg(BPUFILCOL, fill_col);
		
		GPU_WriteReg(BPUCTRL,0x0009); // Informe le BPU de l'opération à faire	
	}

	// On clear une zone spécifique d'un des plans
	void GPU_ClearRect(GPU_Layer* layer, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY){
		uint32_t adresse_dest = layer->addr + x0 + y0*layer->width;

		while( GPU_checkBPU() != 0){};	
		
		GPU_WriteReg(BPUDSTADDR_L,(adresse_dest&0xFFFF));
		GPU_WriteReg(BPUDSTADDR_H,((adresse_dest&0xFFFF0000)>>16));
			
		GPU_WriteReg(BPUPICSIZE_H, (0xFFFF & layer->width));

		GPU_WriteReg(BPUSIZE_L, (dX & 0x3FF));		
		GPU_WriteReg(BPUSIZE_H, (dY & 0x3FF));		

		GPU_WriteReg(BPUFILCOL, 0);
			
		GPU_WriteReg(BPUCTRL, 0x011); // Informe le BPU de l'opération à faire
	}

		
	void GPU_SetRectAlphaValue (GPU_Layer* layer, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY, uint8_t alpha){
		uint32_t adresse_dest = layer->addr + x0 + y0*layer->width;
		
		while( GPU_checkBPU() != 0){};

		GPU_WriteReg(BPUDSTADDR_L,(adresse_dest&0xFFFF));
		GPU_WriteReg(BPUDSTADDR_H,((adresse_dest&0xFFFF0000)>>16));
					
		GPU_WriteReg(BPUPICSIZE_H, (0xFFFF & layer->width));
		
		GPU_WriteReg(BPUSIZE_L, (dX & 0x3FF));		
		GPU_WriteReg(BPUSIZE_H, (dY & 0x3FF));		
			
		GPU_WriteReg(BPUSAR,alpha);
		
		GPU_WriteReg(BPUDUMADDR_L,(ADRESSE_TAMPON&0xFFFF));
		GPU_WriteReg(BPUDUMADDR_H,((ADRESSE_TAMPON&0xFFFF0000)>>16));
					
		GPU_WriteReg(BPUCTRL,0x0021); // Informe le BPU de l'opération à faire
	}	


	// On lance une opération de bitblit depuis un layer à un autre
	void GPU_BitBlitL2L(GPU_Layer* layer, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY, 
											GPU_Layer* destLayer, uint16_t dstX, uint16_t dstY){
		uint32_t adresse_dest = destLayer->addr + dstX + dstY*destLayer->width;
		uint32_t adresse_source = layer->addr + x0 + y0*layer->width;
		
		while( GPU_checkBPU() != 0){};

		GPU_WriteReg(BPUDSTADDR_L,(adresse_dest&0xFFFF));
		GPU_WriteReg(BPUDSTADDR_H,((adresse_dest&0xFFFF0000)>>16));
		
		GPU_WriteReg(BPUSRCADDR_L,(adresse_source&0xFFFF));
		GPU_WriteReg(BPUSRCADDR_H,((adresse_source&0xFFFF0000)>>16));
		
		GPU_WriteReg(BPUPICSIZE_L, (0xFFFF & layer->width));
		GPU_WriteReg(BPUPICSIZE_H, (0xFFFF & destLayer->width));	
			
		GPU_WriteReg(BPUSIZE_L, (dX & 0x3FF));		
		GPU_WriteReg(BPUSIZE_H, (dY & 0x3FF));		
			
		GPU_WriteReg(BPUDUMADDR_L,(ADRESSE_TAMPON&0xFFFF));
		GPU_WriteReg(BPUDUMADDR_H,((ADRESSE_TAMPON&0xFFFF0000)>>16));
			
		GPU_WriteReg(BPUCTRL,0x0003); // Informe le BPU de l'opération à faire
	}


	// On lance une opération de bitblit depuis une image à un layer
	void GPU_BitBlitI2L(GPU_Image *image, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY, 
											GPU_Layer* destLayer, uint16_t dstX, uint16_t dstY){
		uint32_t adresse_dest = destLayer->addr + dstX + dstY*destLayer->width;
		uint32_t adresse_source = image->addr + x0 + y0*image->width;
		
		while( GPU_checkBPU() != 0){};

		GPU_WriteReg(BPUDSTADDR_L,(adresse_dest&0xFFFF));
		GPU_WriteReg(BPUDSTADDR_H,((adresse_dest&0xFFFF0000)>>16));
		
		GPU_WriteReg(BPUSRCADDR_L,(adresse_source&0xFFFF));
		GPU_WriteReg(BPUSRCADDR_H,((adresse_source&0xFFFF0000)>>16));
		
		GPU_WriteReg(BPUPICSIZE_L, (0xFFFF & image->width));
		GPU_WriteReg(BPUPICSIZE_H, (0xFFFF & destLayer->width));	
			
		GPU_WriteReg(BPUSIZE_L, (dX & 0x3FF));		
		GPU_WriteReg(BPUSIZE_H, (dY & 0x3FF));		
			
		GPU_WriteReg(BPUDUMADDR_L,(ADRESSE_TAMPON&0xFFFF));
		GPU_WriteReg(BPUDUMADDR_H,((ADRESSE_TAMPON&0xFFFF0000)>>16));
			
		GPU_WriteReg(BPUCTRL,0x0003); // Informe le BPU de l'opération à faire
	}

	
	// On lance une opération de move depuis un layer à un autre
	void GPU_MoveL2L (GPU_Layer* layer, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY, 
										GPU_Layer* destLayer, uint16_t dstX, uint16_t dstY){
		uint32_t adresse_dest = destLayer->addr + dstX + dstY*destLayer->width;
		uint32_t adresse_source = layer->addr + x0 + y0*layer->width;
		
		while( GPU_checkBPU() != 0){};

		GPU_WriteReg(BPUDSTADDR_L,(adresse_dest&0xFFFF));
		GPU_WriteReg(BPUDSTADDR_H,((adresse_dest&0xFFFF0000)>>16));
		
		GPU_WriteReg(BPUSRCADDR_L,(adresse_source&0xFFFF));
		GPU_WriteReg(BPUSRCADDR_H,((adresse_source&0xFFFF0000)>>16));
		
		GPU_WriteReg(BPUPICSIZE_L, (0xFFFF & layer->width));
		GPU_WriteReg(BPUPICSIZE_H, (0xFFFF & destLayer->width));	
			
		GPU_WriteReg(BPUSIZE_L, (dX & 0x3FF));		
		GPU_WriteReg(BPUSIZE_H, (dY & 0x3FF));		
			
		GPU_WriteReg(BPUDUMADDR_L,(ADRESSE_TAMPON&0xFFFF));
		GPU_WriteReg(BPUDUMADDR_H,((ADRESSE_TAMPON&0xFFFF0000)>>16));
			
		GPU_WriteReg(BPUCTRL,0x0005); // Informe le BPU de l'opération à faire
	}

	// On lance une opération de move depuis une image à un layer (attention! image sera modifié)
	void GPU_MoveI2L (GPU_Image *image, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY, 
										GPU_Layer* destLayer, uint16_t dstX, uint16_t dstY){
		uint32_t adresse_dest = destLayer->addr + dstX + dstY*destLayer->width;
		uint32_t adresse_source = image->addr + x0 + y0*image->width;
		
		while( GPU_checkBPU() != 0){};
			
		GPU_WriteReg(BPUDSTADDR_L,(adresse_dest&0xFFFF));
		GPU_WriteReg(BPUDSTADDR_H,((adresse_dest&0xFFFF0000)>>16));
	
		GPU_WriteReg(BPUSRCADDR_L,(adresse_source&0xFFFF));
		GPU_WriteReg(BPUSRCADDR_H,((adresse_source&0xFFFF0000)>>16));
		
		GPU_WriteReg(BPUPICSIZE_L, (0xFFFF & image->width));
		GPU_WriteReg(BPUPICSIZE_H, (0xFFFF & destLayer->width));	
			
		GPU_WriteReg(BPUSIZE_L, (dX & 0x3FF));		
		GPU_WriteReg(BPUSIZE_H, (dY & 0x3FF));		
			
		GPU_WriteReg(BPUDUMADDR_L,(ADRESSE_TAMPON&0xFFFF));
		GPU_WriteReg(BPUDUMADDR_H,((ADRESSE_TAMPON&0xFFFF0000)>>16));
			
		GPU_WriteReg(BPUCTRL,0x0005); // Informe le BPU de l'opération à faire
	}						


	

void GPU_Move1(GPU_Layer*  srcLayer,GPU_Image *image,GPU_Layer* destLayer,uint32_t dstX,uint32_t dstY,GPU_Color Color){
	
	/*uint32_t adresse_dest;
	uint32_t adresse_source;
	
	while( GPU_checkBPU() != 0){};
	
	adresse_dest = destPlane.Addr + dstX + dstY*destPlane.Plane_Width;
	adresse_source = image->Adresse;
	
	image->Adresse = adresse_dest;

	
	GPU_WriteReg(BPUPICSIZE, (0xFFFF0000 & (srcPlane.Plane_Width << 16 )));


	GPU_WriteReg(BPUSRCADDR,adresse_source);

	GPU_WriteReg(BPUDSTADDR,adresse_dest);
	
	GPU_WriteReg(BPUDUMADDR,ADRESSE_TAMPON);	

	GPU_WriteReg(BPUSIZE, (image->Width & 0x3FF) + ((image->Height & 0x3FF) << 16 ));		
	
	GPU_WriteReg(BPUFILCOL,(uint32_t) ((Color.R & 0xF) + ((Color.G & 0xF) << 4) + ((Color.B & 0xF) << 8)+ ((Color.A & 0xF) << 12)));
	
	GPU_WriteReg(BPUCTRL,0x0041); // Informe le BPU de l'opération à faire
			*/
}	

void GPU_SetA1(uint32_t adresse_source,uint32_t adresse_dest, uint32_t taille_horizontal, uint32_t taille_vertical, uint16_t couleur, uint16_t alpha)
{
	/*while( GPU_checkBPU() != 0){};
		
	GPU_WriteReg(BPUDSTADDR,adresse_dest);
	GPU_WriteReg(BPUSRCADDR,adresse_source);
		
	GPU_WriteReg(BPUSIZE, (taille_horizontal & 0x3FF) + ((taille_vertical & 0x3FF) << 10 ));		
	
	//GPU_WriteReg(BPUPICSIZE, (0xFF00 & (plane.Plane_Width << 16 )));

		
	GPU_WriteReg(BPUFILCOL,couleur);
	
	GPU_WriteReg(BPUSAR,alpha);
		
	GPU_WriteReg(BPUCTRL,0x0081); // Informe le BPU de l'opération à faire*/
			
}


	

/***** Group : PGU modification *****/	
	uint8_t GPU_checkPGU(void){
		return (GPU_ReadReg(PGUCTRL)&0x1) ;
	}
	

// On met un pixel particulier d'un plan à une certaine couleur
void GPU_SetPixel (GPU_Layer* layer, uint16_t X, uint16_t Y, GPU_Color color){
	uint16_t col = ((color.R & 0xF) + ((color.G & 0xF) << 4) + ((color.B & 0xF) << 8)+ ((color.A & 0xF) << 12));
	
	while ( GPU_checkPGU() != 0) {}
	
	GPU_WriteReg(PGULC1R_L, (uint16_t) X);
	GPU_WriteReg(PGULC1R_H, (uint16_t) Y);
		
	GPU_WriteReg(PGUDSTLEN,layer->width);
		
	GPU_WriteReg(PGUDSTADDR_L,(layer->addr&0xFFFF));
	GPU_WriteReg(PGUDSTADDR_H,((layer->addr&0xFFFF0000)>>16));		
		
	GPU_WriteReg(PGUCOLOR, (uint16_t) col);
	
	GPU_WriteReg(PGUCTRL,0x3);
}

// On clear un pixel particulier
void GPU_ClearPixel (GPU_Layer* layer, uint16_t X, uint16_t Y){	
	while ( GPU_checkPGU() != 0) {}

	GPU_WriteReg(PGULC1R_L, (uint16_t) X);
	GPU_WriteReg(PGULC1R_H, (uint16_t) Y);
		
	GPU_WriteReg(PGUDSTLEN,layer->width);
		
	GPU_WriteReg(PGUDSTADDR_L,(layer->addr&0xFFFF));
	GPU_WriteReg(PGUDSTADDR_H,((layer->addr&0xFFFF0000)>>16));	
		
	GPU_WriteReg(PGUCOLOR, 0);
	
	GPU_WriteReg(PGUCTRL,0x3);
}


void GPU_DrawLine (GPU_Layer* layer, uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, GPU_Color color){
	uint16_t Coord = 0;
	uint16_t col = ((color.R & 0xF) + ((color.G & 0xF) << 4) + ((color.B & 0xF) << 8)+ ((color.A & 0xF) << 12));

	if(X2 < X1){
		Coord = X2;
		X2 = X1;
		X1 = Coord;

		Coord = Y2;
		Y2 = Y1;
		Y1 = Coord;
	}
	
	while ( GPU_checkPGU() != 0) {}
	
	GPU_WriteReg(PGULC1R_L, (uint16_t) X1);
	GPU_WriteReg(PGULC1R_H, (uint16_t) Y1);
	
	GPU_WriteReg(PGULC2R_L, (uint16_t) X2);
	GPU_WriteReg(PGULC2R_H, (uint16_t) Y2);
		
	GPU_WriteReg(PGUDSTLEN,layer->width);
		
	GPU_WriteReg(PGUDSTADDR_L,(layer->addr&0xFFFF));
	GPU_WriteReg(PGUDSTADDR_H,((layer->addr&0xFFFF0000)>>16));	
		
	GPU_WriteReg(PGUCOLOR, (uint16_t) col);
	
	GPU_WriteReg(PGUCTRL,0x5);
}
						
void GPU_DrawCircle (GPU_Layer* layer, uint16_t X, uint16_t Y, uint16_t R, GPU_Color color){
	uint16_t col = ((color.R & 0xF) + ((color.G & 0xF) << 4) + ((color.B & 0xF) << 8)+ ((color.A & 0xF) << 12));

	if(R <= X && R<=Y){
	
		while ( GPU_checkPGU() != 0) {}

		GPU_WriteReg(PGULC1R_L, (uint16_t) X);
		GPU_WriteReg(PGULC1R_H, (uint16_t) Y);
		
		GPU_WriteReg(PGULC2R_L, (uint16_t) X+R);
		GPU_WriteReg(PGULC2R_H, (uint16_t) Y);
			
		GPU_WriteReg(PGUDSTLEN,layer->width);
			
		GPU_WriteReg(PGUDSTADDR_L,(layer->addr&0xFFFF));
		GPU_WriteReg(PGUDSTADDR_H,((layer->addr&0xFFFF0000)>>16));	
		
		GPU_WriteReg(PGUCOLOR, (uint16_t) col);
		
		GPU_WriteReg(PGUCTRL,0x21);
	}
}
						

void GPU_WriteChar (GPU_Layer* layer, uint16_t X, uint16_t Y, char c, GPU_Color color){
	uint16_t col = ((color.R & 0xF) + ((color.G & 0xF) << 4) + ((color.B & 0xF) << 8)+ ((color.A & 0xF) << 12));

	if(c>' ' && c<= 127){
	
		while ( GPU_checkPGU() != 0) {}
			
		GPU_WriteReg(PGULC1R_L, (uint16_t) X);
		GPU_WriteReg(PGULC1R_H, (uint16_t) Y);
			
		GPU_WriteReg(PGUCHAR, (uint16_t) (c-32));
			
		GPU_WriteReg(PGUDSTLEN,layer->width);
			
		GPU_WriteReg(PGUDSTADDR_L,(layer->addr&0xFFFF));
		GPU_WriteReg(PGUDSTADDR_H,((layer->addr&0xFFFF0000)>>16));	

		GPU_WriteReg(PGUCOLOR, (uint16_t) col);
		
		GPU_WriteReg(PGUCTRL,0x09);
	}
}	

void GPU_WriteText (GPU_Layer* layer, uint16_t X, uint16_t Y, char* str, GPU_Color color){
	int x_char;
	int i = 0;
	x_char = X;
	
	while(x_char < layer->width && str[i]!=0 ){
		GPU_WriteChar (layer, x_char,  Y,  str[i], color);
		i++;
		x_char += 6;
	}
}

void GPU_DrawRect (GPU_Layer* layer, uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, GPU_Color color){
	GPU_DrawLine (layer, X1, Y1, X2, Y1, color);
	GPU_DrawLine (layer, X2, Y1, X2, Y2, color);
	GPU_DrawLine (layer, X2, Y2, X1, Y2, color);
	GPU_DrawLine (layer, X1, Y2, X1, Y1, color);
}


/***** Group : DMA control *****/

uint8_t GPU_checkDMA (void)
{
	return (GPU_ReadReg(DMACTRL) & 0x2);
}

void GPU_PreSendDataToLayer(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy, GPU_Layer* layer)
{
	uint32_t addr = layer->addr + x + y*layer->width;
	
	GPU_WriteReg(DMADSTADDR_L,addr&0xFFFF);
	GPU_WriteReg(DMADSTADDR_H,(addr&0xFFFF0000)>>16);
	
	GPU_WriteReg(DMAIMGSIZE_L, dx);
	GPU_WriteReg(DMAIMGSIZE_H, dy);
	
	GPU_WriteReg(DMADSTSIZER,layer->width);
	
	GPU_WriteReg(DMACTRL,0x1);
}
	
