
#include "Zelda.h"



// Mutex pour le mouvement du personnage
OS_ID Mutex_Movement;
movement linkMovement;

// Variable pour les images
GPU_Image Link;
GPU_Image back;
GPU_Image soldier;

// Variable de position de link
uint32_t linkPosX = 0;
uint32_t linkPosY = 0;

uint32_t linkDstX = 17;
uint32_t linkDstY = 11;

uint32_t nbPixelMove = 4;

// Variable de taille de la map
uint32_t mapDstX = 1024;
uint32_t mapDstY = 1536;

uint16_t colorBlock = 0x000;

// Fichier contenant les chemins
FIL filPathFinding;

// Variable pour stocker les endroits ou link ne peut aller
//uint8_t pixelBlock[1536][1024];


// Tache idle : Tache qui scrute les inputs pour décider du mouvement du personnage et
// fais évoluer la suite du jeu, met a jour a chaque input le type de mouvement,
// pensez a protoger ces variables globales avec des mutex
// Prio basse
__task void taskZelda (void)
{
	// Chargement des images du niveau de base
	
	// ouverture du fichier de pathfinding en lecture seule
	
	rt_mut_init(Mutex_Movement);
	
}
	
// Tache afficher : Lance la tâche qui en fonction du mouvement fais évoluer l'affichage
// ou lance le chargement d'un nouveau niveau au cas ou il arrive en fin de map toutes les 
// 1/60 seconde pour avoir un affichage tjs fluide
// PRIo haute
__task void taskZeldaDisplay (void)
{
	// On verifie que peut faire le mouvement
	int canMove;
	
	// On bloque le programme en attendant d'avoir
	// de mettre à jour l'affichage
	while(1)
	{
		rt_mut_wait(Mutex_Movement, 0xFFFF);		
		switch (linkMovement)
		{
			case MOVE_RIGHT:
			{
				// bitblit pour l'animation de link
				if (blockMovementLink(linkPosX + nbPixelMove,linkPosY) == 1)
				{
					
				}
				break;
			}
			case MOVE_LEFT:
			{
				// fonction pour bouger a gauche
				break;
			}
			case MOVE_UP:
			{
				// fonction pour bouger a droite
				break;
			}
			case MOVE_DOWN:
			{
				// fonction pour bouger a droite
				break;
			}
			case MOVE_SWORD:
			{
				// fonction pour montrer le coup d'épée
				break;
			}
			case MOVE_HIT:
			{
				// fonction pour bouger a droite
				break;
			}
			case MOVE_IDLE:
			{
				// Remettre le perso en position init
			}
		}	
		rt_mut_release(Mutex_Movement);
		os_dly_wait(200);
	}
}


int blockMovementLink(int nextLinkPosX, int nextLinkPosY)
{
	int block;	
	int cptX = 0;
	int cptY = 0;
	
	int cursorX = nextLinkPosX*2; // 2 byte/pixel
	int cursorY = nextLinkPosY*2*mapDstX;
	
	uint16_t readByte = 0;
	UINT byteToRead;
	
	// verifie qu'on ne vas pas hors map
	if ((cursorX >= mapDstX) || (cursorY >= mapDstY))
	{
		return 0;
	}
	
	for (cptY = 0 ; cptY < linkDstY ; ++cptY)
	{
		for (cptX = 0 ; cptX < linkDstX ; ++cptX)
		{
			f_lseek(&filPathFinding, cursorY + cptY*2 + cursorX*2 + cptX);
			f_read(&filPathFinding, &readByte, 2, &byteToRead);
			if (readByte == colorBlock)
			{
				return 0;
			}
		}
	}
		
	return 1;		
	}
	
	
	
}
	
	

// Tache chargement du fond d'écran en attente d'un semaphore
// Modifier le nom du niveau à charger (Deux niveaux seront disponibles)
