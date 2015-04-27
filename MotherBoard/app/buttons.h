/**
  ******************************************************************************
  * @file    buttons.h
  * @author  Jeremy LAUVIGE (4AE-SE) 
  * @version V0.1
  * @date    03-April-2014
  * @brief  Contient toutes les structures, includes, variables... utiles
	*					au fonctionnement des boutons
  ******************************************************************************
  */
	
	#ifndef __BUTTONS_H
	#define __BUTTONS_H

/**
  ******************************************************************************
	*	Includes
  ******************************************************************************
  */
	#include <stm32f4xx.h>
	
	/**
  ******************************************************************************
	*	Enumérations
  ******************************************************************************
  */
	enum _Button { TAMPER, USER }typedef Button;
	enum _Boolean_button { TRUE, FALSE }typedef _Boolean_button;
	
	/**
  ******************************************************************************
	*	Fonctions
  ******************************************************************************
  */
	void Initialize_Button(Button But);
	_Boolean_button is_button_pressed(Button But);
	
	#endif

