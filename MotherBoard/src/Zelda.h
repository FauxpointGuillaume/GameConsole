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
		
		MOVE_DIAG_UP_RIGHT,
		MOVE_DIAG_RIGHT_UP,
		
		MOVE_DIAG_DOWN_RIGHT,
		MOVE_DIAG_RIGHT_DOWN,
		
		MOVE_DIAG_UP_LEFT,
		MOVE_DIAG_LEFT_UP,
		
		MOVE_DIAG_DOWN_LEFT,
		MOVE_DIAG_RIGHT_LEFT,		
		
		MOVE_SWORD_RIGHT,
		MOVE_SWORD_LEFT,
		MOVE_SWORD_UP,
		MOVE_SWORD_DOWN,
		
		MOVE_HIT,
		
		MOVE_IDLE,
		MOVE_IDLE_UP,
		MOVE_IDLE_DOWN,
		MOVE_IDLE_LEFT,
		MOVE_IDLE_RIGHT
	}typedef movement;
	
	/**
  ******************************************************************************
	*	Functions
  ******************************************************************************
  */
	
	int blockMovementLink(void);
	void refreshScreen(void);
	int updatePosBack(void);
	
	void scrollUp(void);
	void scrollDown(void);
	void scrollLeft(void);
	void scrollRight(void);
	
	void animLink(uint16_t nbAnimLink, uint16_t offsetX, uint16_t offsetY, 
							uint16_t sizeX, uint16_t sizeY, uint16_t xDiff, int16_t curLinkPosX, int16_t curLinkPosY);
	void animLinkIdleDown(void);
	void animLinkIdleLeft(void);
	void animLinkIdleUp(void);
	void animLinkIdleRight(void);
	void animLinkDown(void);
	void animLinkUp(void);
	void animLinkLeft(void);
	void animLinkRight(void);
	void animLinkSwordDown(void);
	void animLinkSwordUp(void);
	void animLinkSwordLeft(void);
	void animLinkSwordRight(void);
	
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
	
	




