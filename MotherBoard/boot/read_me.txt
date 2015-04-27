**
  ******************************************************************************
  * @file    read_me.txt
  * @authors  Jeremy LAUVIGE - Pierre-Louis Tilak - Frédéric Nau - Gérome Burlats (4AE-SE)
  * @version V0.5_beta
  * @date    10-Avril-2014
  * @brief   
  *	Ce fichier doit contient les explications concernant les changements apportés aux fichiers du projet.
  *	Sans une mise à jour correcte de ce fichier, on ne s'en sortira jamais dans les versions.
  *
  * Quelques règles qui doivent être respectées à chaque modification, :
  *
  * - Veuillez incrémenter (manuelement) la version du projet 
  *		= nom du dossier contenant tous les fichiers
  *	- Pensez a noter la date de modification et la nouvelle version sur les fichiers modifiés (en-tête)
  *	- Notez (de manière succinte) dans ce fichier "read_me.txt" les modifications apportées (fichiers, fonctions modifiés) 
  *		Cela permetera d'avoir un historique des dernieres modifications et facilitera grandement la mise en commun des codes
  *	- Lors de la création d'un fichier, pensez à utiliser la même forme que pour les autres (balises d'en-tête, d'include...)
  *
  * Une fois les modifications apportées, il est necessaire de compresser le projet 
  * par exemple "Console_v0.1.rar" et de l'importer sur le DRIVE
  *
  * Note : Un projet qui contient l'extension beta est un projet qui comporte des erreurs (non bloquantes) !
  *
  ***************************************************************************************************************************
	31-Mai-2014	  :   -	Nom du projet : Console_v1.1
					  - Ajout du joystick
					  - Ajout des fonctions d'import des images et de transfert au fpga pour l'écran (partie intégration)
	
	30-Mai-2014	  :   -	Nom du projet : Console_v1.0
					  - L'os s'initialise, transfert l'exécutable et lui passe la main, celui-ci s'exécute normalement
	
	28-Mai-2014	  :   -	Nom du projet : Console_v0.96
					  - Initialisation de l'OS
					  - Saut sur le jeu mis en mémoire
					  - Exécution du jeu sans erreur
					  
	13-Mai-2014   :	  - Nom du projet en cours : Console_v0.92 (encore !)
					  - La table de fonction fonctionne (ahaha !!)
					  - Elle est maintenant presente dans api.c, et indiquee dans le startup
	
	06-Mai-2014   :   - Nom du projet en cours : Console_v0.9
					  - La table des fonctions avance ! Elle est presente dans system_stm32f4xx ou elle est initialisee. Les fonctions 
					  qui l'utilisent sont definient dans api.c
					  #### Gros probleme de place, il faut arriver à compiler avec GCC absolument !!
					  -  L'appel des fonctions via la table fonctionne (avec passage d'argument sans retour)
					  -  Il faut definir les fichies minimaux pour permettre de faire un nouveau projet pour le jeu.

	30-Avril-2014 : - Nom du projet en cours : Console_v0.81
							- Le driver graphique a été ajouté !

	30-Avril-2014 : - Nom du projet en cours : Console_v0.8
							- Le SDIO de la version 0.6 ne marchait pas. Le code a été un peu modifié et maintenant cela fonctionne !
	
	10-Avril-2014 : - Nom du projet en cours : Console_v0.7
							- Ajout des fichiers d'init du FSMC et des tests fonctionnels de la SRAM.
	
	10-Avril-2014 : - Nom du projet en cours : Console_v0.6_beta		
							- Ajout des fichiers de configuration de la carte sd (compile mais non testé en réel)=

							
	08-Avril-2014 : - Nom du projet en cours : Console_v0.5_beta		
							- Création des fichiers serial.c et serial.h. 
							- Un simple printf permet d'envoyer un texte sur le port série. 
									(include du global et de includ_app est necessaire)
							- Utile au débug
							- Fonctionne parfaitement. 
							- Beta : Bug de la ram

	07-Avril-2014 : - Nom du projet en cours : Console_v0.4_beta
							- Création de fichier SRAM pour la ram, nouvelle fonction InitFSMC
							- Bug : On peut écrire dans la ram mais à l'étape d'après c'est effacé ! :(

	04-Avril-2014 : -Nom du projet en cours : Console_v0.4

							- Création du répertoire app qui contient tous les fichiers .c et .h pour l'application
									(gestion des boutons de la carte, des leds de la carte, du potentiometre...)
							- Création des fichiers buttons, leds et potentiometer qui proposent des fonctions
									d'initialisation et d'utilisation des boutons, des leds et du potentiometre de la carte
							- Modification du main.c pour effectuer un test de ces fonctions
							- Etat : 	- Compile avec des warnings sans importance
										- Fonctionne en réel
							- Note : penser a ajouter tous les includes des app dans "include_app.h"
										fichier inclus par tous ceux qui ont besoin d'au moins un application

	
	14-Mars-2014 : 	- Création du projet contenant les librairies
							- Création des fichiers main.c \ global.c \global.h
							- Etat : 	- Projet compile. Warnings dus aux fonctions vides 
							- Pas d'éxécution

