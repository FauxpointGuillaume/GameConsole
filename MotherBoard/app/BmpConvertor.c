
#include "BmpConvertor.h"

// Creation d'un nouveau pixel
struct pixel * new_pixel(uint16_t red, uint16_t green, uint16_t blue)
{
    struct pixel * pixel =(struct pixel*)malloc(sizeof(struct pixel*));
    pixel->Blue = blue;
    pixel->Red = red;
    pixel->Green = green;
    return pixel;
}

// Lancement de la convertion de l'image BMP en image utilisable par notre GPU
// filIn : Le nom du fichier de l'image BMP à convertir
// filOut : Le nom du fichier de sortie (copié sur la SD)
// alpha : Le niveau de transparence général
// transpixel : La couleur qui va être transparente
int Convertion(FIL *filIn, FIL *filOut, uint8_t alpha, pixel *transPixel, int alphaPixelOn)
{
	// Les trois couleurs d'un pixel
	uint8_t red, green, blue;
	// La somme résiduel des pixels calculés
	uint16_t resPixel;
	// Le nombre de bit qui reste à lire
	UINT byteRead;	
	
	// La sortie des fonctions de gestion de fichier
	FRESULT res;	

	// Variable permettant de verifier si il y a ou non du paading dans les data de l'image
	int padding = 0;
	int taille_padding = 0;

	// Variable permettant de savoir a quel octet on se situe dans le but de supprimer les octects de padding
	int octet_parcouru =0;

	// Variable servant de verification d'erreur
	int erreur = 0;
	int i =0;
	int offset_donnee = 0;
	unsigned int largeur = 0;
	unsigned int longueur = 0;
	int stateRecord = 0;
	
	int cursor = 0;
	int cursorLine = 0;

	// On se déplace au dixième caractere pour lire l'offset permettant d'atteindre les données
	f_lseek(filIn,EMPLACEMENT_OFFSET_PIXEL);
	f_read(filIn, &offset_donnee, 4, &byteRead);

	// On va lire la largeur du fichier image pour ignorer le padding si besoin
	f_lseek(filIn,OFFSET_LONGUEUR);
	f_read(filIn, &longueur, 4, &byteRead);

	// On va lire la largeur du fichier image pour ignorer le padding si besoin
	f_lseek(filIn,OFFSET_LARGEUR);
	f_read(filIn, &largeur, 4, &byteRead);// On va lire la largeur du fichier image pour ignorer le padding si besoin

	// On verifié la présence de padding ou non, on sait que la mémoire s'aligne sur 4 octet, on fait donc une simple division
	if ((largeur % 4) !=0)
	{
		padding = 1;
		taille_padding = 4-(largeur % 4);
	}

	//On Commence la conversion
	//On utilise l'offset préalablement calculé pour allez à la zone de donnée
	cursor = (longueur-1)*3*largeur + offset_donnee;
	
	f_lseek(filIn,cursor);
 
	while (cursor > 36)
	{
		if (stateRecord !=3)
		{
			if (cursorLine >= (largeur *3))
			{
				cursorLine = 0;
				cursor = cursor - 3*largeur;
				f_lseek(filIn,cursor);
			}		
			octet_parcouru ++;
			cursorLine++;		
			
			res = f_read(filIn, &erreur, 1, &byteRead);
		}
		// On verifie si on est dans les octets de padding s'il exite, on va faire avancer le curseur pour les ignorer
		if (padding == 1 && octet_parcouru >= (3*largeur+1))  
		{
			octet_parcouru =0;
			for (i=0;i<taille_padding;++i)
			{
				res = f_read(filIn, &erreur, 1, &byteRead);
			}
		}
		else
		{
			// On attend d'avoir parcouru un octect pour l'enregistrer
			switch (stateRecord)
			{
				case 0:
					blue = erreur;
					stateRecord = 1;
					break;

				case 1:
					green = erreur;
					stateRecord = 2;
					break;

				case 2:
					red = erreur;
					stateRecord = 3;
					break;
				case 3:
					// On va vérifié que la couleur lue n'est pas une couleur que l'on veut
					// transparente
				
					// 0xGRAB
					if ((transPixel->Red == red) && (transPixel->Blue == blue) && (transPixel->Green == green) && (alphaPixelOn == 1))
					{
						resPixel = 0;					
						f_write(filOut, &resPixel, 2, &byteRead);
					}
					else
					{
						red /= 16;
						green /= 16;
						blue /= 16;
						
						resPixel = ((uint16_t)alpha << 12) + ((uint16_t)blue << 8) + ((uint16_t)green << 4) + (uint16_t)red;
						
						f_write(filOut, &resPixel, 2, &byteRead);
					}					
					stateRecord = 0;
					
					break;
			}
		}
	}
	
	f_sync(filOut);
	return 0;
}







