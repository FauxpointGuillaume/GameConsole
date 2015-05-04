	#ifndef __ZELDA_H
	#define __ZELDA_H
	
	
	/**
  ******************************************************************************
	*	Includes
  ******************************************************************************
  */
	
	#include <RTL.h>
	#include "Leds.h"
	#include "joystick.h"
	#include "interface.h"
	#include "sd.h"
	
	/**
  ******************************************************************************
	*	Enumeration
  ******************************************************************************
  */
	
	enum movement
	{
		MOVE_RIGHT,
		MOVE_LEFT,
		MOVE_UP,
		MOVE_DOWN,
		
		MOVE_SWORD,
		MOVE_HIT,
		
		MOVE_IDLE
	}typedef movement;
	
	/**
  ******************************************************************************
	*	Functions
  ******************************************************************************
  */
	
	int blockMovementLink(int nextLinkPosX, int nextLinkPosY;

	
	__task void taskZelda (void);
	
	/**
  ******************************************************************************
	*	Variables
  ******************************************************************************
  */
	
	// La hit Box de link fait 16x16

	
	
	// Dans ce tableau on va enregistrer tous les pixels qu'on
	// peut traverser et ceux qu'on ne peut pas, techniquement
	// c'est pas fait comme ça mais plutôt avec le moteur physique
	// mais osef
	
	

	
#endif
	
	




