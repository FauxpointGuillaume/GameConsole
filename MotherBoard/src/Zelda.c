
#include "Zelda.h"



// Mutex pour le mouvement du personnage
OS_ID Mutex_Movement;
movement linkMovement;
movement nextLinkMovement;

// Variable pour les images
GPU_Image LinkSprite;
GPU_Image backLink;
GPU_Image soldier;

// Variable de position de link
int16_t linkPosX = 140;
int16_t linkPosY = 100;

int16_t nextLinkPosX = 140;
int16_t nextLinkPosY = 100;


uint8_t linkDstX = 17;
uint8_t linkDstY = 11;

int8_t nbPixelMove = 1;

uint8_t stateAnim = 0;

// Variable de la position de la map
int16_t backPosX = 555;
int16_t backPosY = 1188;

int16_t nextBackPosX = 555;
int16_t nextBackPosY = 1188;

uint16_t backSizeX = 320;
uint16_t backSizeY = 240;

 
// Variable de taille de la map
uint32_t mapDstX = 1024;
uint32_t mapDstY = 1536;

uint16_t colorBlock = 0x000;

// Fichier contenant les chemins
FIL filPathFinding;

// Tache idle : Tache qui scrute les inputs pour décider du mouvement du personnage et
// fais évoluer la suite du jeu, met a jour a chaque input le type de mouvement,
// pensez a protoger ces variables globales avec des mutex
// Prio basse
__task void taskZelda (void)
{
	uint32_t touche;
	
	// Chargement des images du niveau de base
	
	// ouverture du fichier de pathfinding en lecture seule
	GPU_NewImage(&backLink, mapDstX, mapDstY, "back", 0x0200000);
	GPU_NewImage(&LinkSprite, 320, 240, "link", 0x0100000);
	
	GPU_ConfigureLayer(&Layer_1, LAYER1_START_ADDRESS, backSizeX, backSizeY);
	GPU_ConfigureLayer(&Layer_2, LAYER2_START_ADDRESS, 320, 240);
	
	Display_conf.Enable =1;
	Display_conf.Alpha_On =1;
	Display_conf.Plan_Enable = 0x3;
	Display_conf.Test_On=0;
	
	GPU_UpdateDisplayConfig();
	
	GPU_HScroll (&Layer_1, 0,1);
	GPU_VScroll (&Layer_1, 0,1);	
	
	GPU_HScroll (&Layer_2, 0,1);
	GPU_VScroll (&Layer_2, 0,1);
	
	GPU_ClearScreen(&Layer_2);
	GPU_ConfigureOutput(MODE_VGA);
	
	GPU_BitBlitI2L(&backLink, backPosX, backPosY, backSizeX, backSizeY,&Layer_1, 0,0);
	animLinkIdleDown();	
	
	openImageFileRead("path", &filPathFinding);
	
	while(1)
	{
		touche = JOY_GetKeys();
		Toggle_Led(LED4);
		
		switch (touche)
		{
			case JOY_UP:
			{
				nextLinkPosY -= nbPixelMove;
				nextBackPosY -= nbPixelMove;
				nextLinkMovement = MOVE_UP;
				break;
			}
			case JOY_DOWN:
			{
				nextLinkPosY += nbPixelMove;
				nextBackPosY += nbPixelMove;
				nextLinkMovement = MOVE_DOWN;
				break;
			}
			case JOY_LEFT:
			{
				nextLinkPosX -= nbPixelMove;
				nextBackPosX -= nbPixelMove;
				nextLinkMovement = MOVE_LEFT;
				break;
			}
			case JOY_RIGHT:
			{
				nextLinkPosX += nbPixelMove;
				nextBackPosX += nbPixelMove;
				nextLinkMovement = MOVE_RIGHT;
				break;
			}
			default:
			{
				nextLinkMovement = MOVE_IDLE;
				break;
			}
		}
		refreshScreen();		
		os_dly_wait(5);
	}
	
}
	
void refreshScreen()
{
	// On doit verifier dans l'ordre
	// Qu'on peut bouger : pas de mur, pas d'obstacle
	if (blockMovementLink() == 1)
	{
		// On met à jour la position de l'écran en verifiant 
		// qu'on est pas au bord, si c'est le cas on informe
		// le programme de faire uniquement avancer link
		updatePosBack();
				
		linkPosX = nextLinkPosX;
		linkPosY = nextLinkPosY;
		if (linkMovement == nextLinkMovement)
		{
			stateAnim++;
		}
		else
		{
			stateAnim =0;
		}
		linkMovement = nextLinkMovement;
		
		switch (linkMovement)
		{
			case MOVE_UP:
			{
				animLinkUp();
				break;
			}
			case MOVE_DOWN:
			{
				animLinkDown();
				break;
			}
			case MOVE_LEFT:
			{
				animLinkLeft();
				break;
			}
			case MOVE_RIGHT:
			{
				animLinkRight();
				break;
			}
			default:
			{
				//animLinkIdleDown();
				break;
			}
		}
	}
	else
	{	
		nextLinkPosX = linkPosX;
		nextLinkPosY = linkPosY;
		
		nextBackPosX = backPosX;		
		nextBackPosY = backPosY;		
	}
}

int updatePosBack()
{
	uint8_t move = 0;
	
	if (nextLinkMovement != MOVE_IDLE)
	{	
		if ((nextBackPosY >= 0 && (nextBackPosY + 240) <  mapDstY) && (nextBackPosY != backPosY)&& (linkPosY == 100))
		{
			backPosY = nextBackPosY;
			nextLinkPosY = 100;	
			move = 1;
		}
		else
		{
			nextBackPosY = backPosY;
		}
		if ((nextBackPosX >= 0 && (nextBackPosX + 320) <  mapDstX) && (nextBackPosX != backPosX) && (linkPosX == 140))
		{
				backPosX = nextBackPosX;
				nextLinkPosX = 140;
				move = 1;
		}
		else
		{
				nextBackPosX = backPosX;
		}
		if (move == 1)
		{
			GPU_BitBlitI2L(&backLink, backPosX, backPosY, backSizeX, backSizeY,&Layer_1, 0,0);	
		}
	}
	
	return move;
}

void animLink(uint16_t nbAnimLink, uint16_t offsetX, uint16_t offsetY, 
							uint16_t sizeX, uint16_t sizeY, uint16_t xDiff)
{
	uint16_t curOffsetX;
	
	if (stateAnim >= nbAnimLink)
	{
		stateAnim = 0;
	}
	curOffsetX = offsetX + stateAnim*30;

	GPU_ClearRect(&Layer_2,0,0,320,240);
	GPU_BitBlitI2L (&LinkSprite,curOffsetX,offsetY,sizeX,sizeY,&Layer_2,linkPosX,linkPosY);
}
	
void animLinkIdleDown()
{
	animLink(1, 11, 6, 20, 25 ,0);	
}

void animLinkIdleLeft()
{
	animLink(1, 41, 6, 20, 25 ,0);	
}

void animLinkIdleUp()
{
	animLink(1, 71, 6, 20, 25 ,0);	
}

void animLinkIdleRight()
{
	animLink(1, 101, 5, 20, 25 ,0);	
}

void animLinkDown()
{
	animLink(8, 11, 35, 20, 25 ,17);	
}

void animLinkUp()
{
	animLink(8, 11, 65, 20, 25 ,17);	
}

void animLinkLeft()
{
	animLink(6, 11, 100, 20, 25 ,17);	
}

void animLinkRight()
{
	animLink(6, 11, 135, 20, 25 ,17);	
}

void animLinkSwordDown()
{
	//animLink(6, 11, 125, 20, 25 ,17);	
}

void animLinkSwordUp()
{
	//animLink(6, 11, 125, 20, 25 ,17);	
}
	
void animLinkSwordLeft()
{
	//animLink(6, 11, 125, 20, 25 ,17);	
}

void animLinkSwordRight()
{
	//animLink(6, 11, 125, 20, 25 ,17);	
}
	
int blockMovementLink()
{
	uint32_t cpt = 0;	
	uint32_t mulCpt = 1;
	
	uint32_t linkDst;
	
	uint32_t offsetX = 0;
	uint32_t offsetY = 0;
	
	uint32_t cursorX = 0;
	uint32_t cursorY = 0;
	
	uint16_t readByte = 0;
	UINT byteToRead;
	
	switch (nextLinkMovement)
	{
		case MOVE_DOWN:
		{	
			cursorX = (nextLinkPosX + nextBackPosX + linkDstX/2); // 2 byte/pixel
			cursorY =  mapDstY*mapDstX - (nextLinkPosY + nextBackPosY + linkDstY + linkDstY)*mapDstX;
			break;
		}
		case MOVE_UP:
		{
			cursorX = (nextLinkPosX + nextBackPosX + linkDstX/2); // 2 byte/pixel
			cursorY =  mapDstY*mapDstX - (nextLinkPosY + nextBackPosY + 15)*mapDstX;
			break;
		}
		case MOVE_RIGHT:
		{
			cursorX = (nextLinkPosX + nextBackPosX + linkDstX); // 2 byte/pixel
			cursorY =  mapDstY*mapDstX - (nextLinkPosY + nextBackPosY + (15+22)/2)*mapDstX;
			break;
		}
		case MOVE_LEFT:
		{
			cursorX = (nextLinkPosX + nextBackPosX); // 2 byte/pixel
			cursorY =  mapDstY*mapDstX - (nextLinkPosY + nextBackPosY + (15+22)/2)*mapDstX;
			break;
		}
		default:
		{
			break;
		}
	}	
	
	f_lseek(&filPathFinding, cursorY + cursorX + cpt*mulCpt);
	f_read(&filPathFinding, &readByte, 1, &byteToRead);
	
	if (readByte == 0)
	{
		return 0;
	}
	
	
	return 1;		
}
	
	