**
  ******************************************************************************
  * @file    read_me.txt
  * @authors  Jeremy LAUVIGE - Pierre-Louis Tilak - Fr�d�ric Nau - G�rome Burlats (4AE-SE)
  * @version V0.5_beta
  * @date    10-Avril-2014
  * @brief   
  *	Ce fichier doit contient les explications concernant les changements apport�s aux fichiers du projet.
  *	Sans une mise � jour correcte de ce fichier, on ne s'en sortira jamais dans les versions.
  *
  * Quelques r�gles qui doivent �tre respect�es � chaque modification, :
  *
  * - Veuillez incr�menter (manuelement) la version du projet 
  *		= nom du dossier contenant tous les fichiers
  *	- Pensez a noter la date de modification et la nouvelle version sur les fichiers modifi�s (en-t�te)
  *	- Notez (de mani�re succinte) dans ce fichier "read_me.txt" les modifications apport�es (fichiers, fonctions modifi�s) 
  *		Cela permetera d'avoir un historique des dernieres modifications et facilitera grandement la mise en commun des codes
  *	- Lors de la cr�ation d'un fichier, pensez � utiliser la m�me forme que pour les autres (balises d'en-t�te, d'include...)
  *
  * Une fois les modifications apport�es, il est necessaire de compresser le projet 
  * par exemple "Console_v0.1.rar" et de l'importer sur le DRIVE
  *
  * Note : Un projet qui contient l'extension beta est un projet qui comporte des erreurs (non bloquantes) !
  *
  ***************************************************************************************************************************
	31-Mai-2014	  :   -	Nom du projet : Console_v1.1
					  - Ajout du joystick
					  - Ajout des fonctions d'import des images et de transfert au fpga pour l'�cran (partie int�gration)
	
	30-Mai-2014	  :   -	Nom du projet : Console_v1.0
					  - L'os s'initialise, transfert l'ex�cutable et lui passe la main, celui-ci s'ex�cute normalement
	
	28-Mai-2014	  :   -	Nom du projet : Console_v0.96
					  - Initialisation de l'OS
					  - Saut sur le jeu mis en m�moire
					  - Ex�cution du jeu sans erreur
					  
	13-Mai-2014   :	  - Nom du projet en cours : Console_v0.92 (encore !)
					  - La table de fonction fonctionne (ahaha !!)
					  - Elle est maintenant presente dans api.c, et indiquee dans le startup
	
	06-Mai-2014   :   - Nom du projet en cours : Console_v0.9
					  - La table des fonctions avance ! Elle est presente dans system_stm32f4xx ou elle est initialisee. Les fonctions 
					  qui l'utilisent sont definient dans api.c
					  #### Gros probleme de place, il faut arriver � compiler avec GCC absolument !!
					  -  L'appel des fonctions via la table fonctionne (avec passage d'argument sans retour)
					  -  Il faut definir les fichies minimaux pour permettre de faire un nouveau projet pour le jeu.

	30-Avril-2014 : - Nom du projet en cours : Console_v0.81
							- Le driver graphique a �t� ajout� !

	30-Avril-2014 : - Nom du projet en cours : Console_v0.8
							- Le SDIO de la version 0.6 ne marchait pas. Le code a �t� un peu modifi� et maintenant cela fonctionne !
	
	10-Avril-2014 : - Nom du projet en cours : Console_v0.7
							- Ajout des fichiers d'init du FSMC et des tests fonctionnels de la SRAM.
	
	10-Avril-2014 : - Nom du projet en cours : Console_v0.6_beta		
							- Ajout des fichiers de configuration de la carte sd (compile mais non test� en r�el)=

							
	08-Avril-2014 : - Nom du projet en cours : Console_v0.5_beta		
							- Cr�ation des fichiers serial.c et serial.h. 
							- Un simple printf permet d'envoyer un texte sur le port s�rie. 
									(include du global et de includ_app est necessaire)
							- Utile au d�bug
							- Fonctionne parfaitement. 
							- Beta : Bug de la ram

	07-Avril-2014 : - Nom du projet en cours : Console_v0.4_beta
							- Cr�ation de fichier SRAM pour la ram, nouvelle fonction InitFSMC
							- Bug : On peut �crire dans la ram mais � l'�tape d'apr�s c'est effac� ! :(

	04-Avril-2014 : -Nom du projet en cours : Console_v0.4

							- Cr�ation du r�pertoire app qui contient tous les fichiers .c et .h pour l'application
									(gestion des boutons de la carte, des leds de la carte, du potentiometre...)
							- Cr�ation des fichiers buttons, leds et potentiometer qui proposent des fonctions
									d'initialisation et d'utilisation des boutons, des leds et du potentiometre de la carte
							- Modification du main.c pour effectuer un test de ces fonctions
							- Etat : 	- Compile avec des warnings sans importance
										- Fonctionne en r�el
							- Note : penser a ajouter tous les includes des app dans "include_app.h"
										fichier inclus par tous ceux qui ont besoin d'au moins un application

	
	14-Mars-2014 : 	- Cr�ation du projet contenant les librairies
							- Cr�ation des fichiers main.c \ global.c \global.h
							- Etat : 	- Projet compile. Warnings dus aux fonctions vides 
							- Pas d'�x�cution

