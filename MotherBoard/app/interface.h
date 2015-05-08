/**
 * \file	interface.h
 * \brief Driver interface for STM32
 * \author Fauxpoint Guillaume
 * \version 1
 * \date 24/05/2014
 *
 * Copyright (c) 2013, INSA-GEI Toulouse, France.
 * Tout droits réservés.
 */

	#ifndef INTERFACE_H
	#define INTERFACE_H

	#include <stm32f4xx.h>
	#include "gpu_driver.h"

/**
 * \page INTERFACE INTERFACE
 * \section INTERFACE_intro Introduction
 *
 * This driver allow to establish a communication between an FPGA card and a STM32 microprocessor.
 * The communication use the FSMC peripheral with pins dedicated to the LCD.
 * If the FPGA is configured like a Graphic Card, you have the possibility to command it from the STM32.
 * The driver got many functions  to do the basic functionality of Graphic Card.
 * Data transfer is also available to access to the FPGAs RAM.
 *
 * \section INTERFACE_dep Dependencies
 *  - \ref stm32f4__driver
 *
 *
 * \section INTERFACE_reference List of APIs related to the driver
 *  - \ref INTERFACE_Driver
 *  - \ref INTERFACE_Class
 *  - \ref Service
 *  - \ref Global

 *
 * \section GPU_DRIVER_exemples Examples
 *  Exemple 1 BitBlit operation
 *
 \code

	#include <stm32f4xx.h>
	#include "global.h"
	#include "../app/include_app.h"
	#include "stm32f4_discovery_sdio_sd.h"
	#include "stm32f4_discovery.h"
	#include "ff.h"
	#include "diskio.h"
	#include "gpu_driver.h"

	int main (void){
		GPU_Color Serdar;

		GPU_Init();

		Initialize_Button(USER);
		Initialize_Button(TAMPER);

		Serdar.R = 3;
		Serdar.G = 1;
		Serdar.B = 16;
		Serdar.A = 4;

		while(1){
			if (!is_button_pressed(TAMPER)){
				GPU_MoveRect (Plan_3 ,0,0,100,100,Plan_3,100,100);

				while (!is_button_pressed(TAMPER));
			}
		}
	}
	 \endcode
 *
 */
 
 /** @addtogroup INTERFACE_Defines Defines
    * \brief Macro of this API
    * @{
    */

		/** @name Output video configuration Mode
      * @{
      */
			#define		MODE_VGA			0x1
			#define		MODE_LCD 			0x0
		/**
      * @}
      */

	/** @name Plan configuration 
    * @{
    */
			#define		LAYER_1_ENABLE		0x1
			#define		LAYER_2_ENABLE		0x2
			#define		LAYER_3_ENABLE		0x4
			#define		LAYER_4_ENABLE		0x8
		/**
      * @}
      */
		
		/** @name Specific macro of FPGA
			* @{
			*/
			/**
				*@brief Buffer address
				*/
				#define 	ADRESSE_TAMPON				0x0700000
			/**
				*@brief Start plane address
				*/
				#define 	LAYER1_START_ADDRESS	0x0000000
				#define 	LAYER2_START_ADDRESS	0x0050000
				#define 	LAYER3_START_ADDRESS	0x0070000
				#define 	LAYER4_START_ADDRESS	0x0090000
		/**
			* @}
			*/

	/** @defgroup INTERFACE_Class Class
    * \brief Class
    * @{
    */
        /**
        * @brief  Layer class
        */
        struct GPU_Layer {
          uint8_t  no;
          uint32_t addr;
          uint16_t width;
          uint16_t height;
          uint16_t scrDx;
          uint16_t scrDy;
        }typedef GPU_Layer;
        /**
        * @brief  Display Configuration class
        */
        struct GPU_Display_conf {
          uint8_t Enable;
          uint8_t Plan_Enable;
          uint8_t Test_On;
          uint8_t Alpha_On;
        }typedef GPU_Display_conf;
        /**
        * @brief  Color class
        */
        struct GPU_Color {
					uint8_t R;
          uint8_t G;
          uint8_t B;
          uint8_t A;
        }typedef GPU_Color;
        /**
        * @brief  Image class
        */
        struct GPU_Image {
          char name[32];
          uint16_t width;
          uint16_t height;
          uint32_t addr;      
        }typedef GPU_Image;			
        /**
        * @brief  DMA conf class
        */
        struct GPU_DMAconf {
					uint8_t  ongoing;
          uint16_t width;
          uint16_t height;
          uint32_t addr;      
        }typedef GPU_DMAconf;			

	/**
    * @}
    */

	/** @addtogroup Service Function
	  * \brief Function to command and transfer data to the FPGA
    * @{
    */
			/** @name Initialization and configuration
        * @{
        */
					/**
            *	@brief Initialize the communication and load in the FPGA the default value
            **/
            void GPU_Init(void);
          /**
            * @brief Configure the output signal (VGA or LCD)
            * @param output 1 = VGA, 0 = LCD
            **/
            void GPU_ConfigureOutput(uint8_t output);
          /**
            * @brief Enable or disable the test program of the FPGA
            * @param testOn 1 = Enable, 0 = Disable
            **/
            void GPU_VideoSignalTest(uint8_t testOn);
			/**
        * @}
        */
    	/** @name Class color functions
        * @{
        */
					/**
            * @brief Initialize a new class color
            * @param color The pointer of the color to initialize
            * @param red Red's part of this color , range 0 to 16
            * @param green Green's part of this color , range 0 to 16
            * @param blue Blue's part of this color , range 0 to 16
            * @param alpha Alpha transparency level
            **/
            void GPU_NewColor(GPU_Color *color, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
			/**
				* @}
				*/
      /** @name Class image functions
        * @{
        */
					/**
            * @brief Initialize a new class image
            * @param image The pointer to the color to initialize
            * @param width The width of this image
            * @param height The height of this image
            * @param name The name of this image
						* @param addr The address of this image
            **/
            void GPU_NewImage(GPU_Image *image, uint16_t width, uint16_t height, char * name, uint32_t addr);
			/**
        * @}
        */
    	/** @name Class Layer and Display_conf functions
        * @{
        */
          /**
            *	@brief Initialize plane class
            * @param layerNo Plane's numero to initialize (1 to 4)
            **/
            void GPU_InitLayer(GPU_Layer* layer, uint8_t no);
          /**
            *	@brief Configure the different layer
            * @param layerNo Define the plane to configure
            * @param layerAddr Plane's address on the FPGAs RAM
            * @param layerWidth Width of the plane (Pixel)
            * @param layerHeight Height of the plane (Pixel)
            **/
            void GPU_ConfigureLayer(GPU_Layer* layer, uint32_t layerAddr, uint16_t layerWidth, uint16_t layerHeight);
          /**
            *	@brief Send the configuration plane update to the FPGA
            **/
            void GPU_UpdateDisplayConfig(void);
      /**
        * @}
        */
				
      /** @name Display control
        * @{
        */
          /**
            *	@brief Enable layers
            * @param layerFlags use the define LAYER_1_ENABLE, LAYER_2_ENABLE, LAYER_3_ENABLE, LAYER_4_ENABLE
            **/
            void GPU_EnableLayers (uint8_t layerFlags);
          /**
            *	@brief Enable the transparency
            * @param AlphaNBinary 1 = enable, 0 = disable;
            **/
            void GPU_TransparencyMode (uint8_t AlphaNBinary);
          /**
            *	@brief Realize a horizontal scrolling operation on a plane
            * @param layerNo Layer to scroll
            * @param dX Range
            * @param dir Direction, 0 => left, 1 => right
            **/
            void GPU_HScroll (GPU_Layer* layer, uint16_t dX, uint8_t dir);
					/**
            *	@brief Realize a vertical scrolling operation on a plane
            * @param layerNo Layer to scroll
            * @param dY Range
            * @param dir Direction, 0 => top, 1 => bot
            **/
            void GPU_VScroll (GPU_Layer* layer, uint16_t dY, uint8_t dir);
      /**
        * @}
        */
				
      /** @name LCD configuration
        * @{
        */
					/**
            *	@brief DRIVER NOT YET IMPLENMENTED
            **/
            int GPU_LCD_AjustContrast(uint32_t cont);
						int GPU_LCD_AjusteBrightness(uint32_t bri);
            int GPU_LCD_AjusteHS(uint32_t hue,uint32_t sat);
            int GPU_LCD_AjusteSubBri(uint32_t red,uint32_t blue);
			/**
        * @}
        */
				
			/** @name Primtive operation
        * @{
        */
          /**
            *	@brief Returns whether BPU is busy or not
            **/
            uint8_t GPU_checkBPU(void);
					/**
            *	@brief [BPU] Clears all of the pixel of a layer (set to black)
            * @param layer In which plane we have to do this operation
            **/
            void GPU_ClearScreen (GPU_Layer* layer);
					/**
            *	@brief [BPU] Fill a rectangular area at a given color
						* @param layer In which plane we have to do this operation
            * @param x0 The x coordinate of the top left corner of the area
					  * @param y0 The y coordinate of the top left corner of the area
						* @param dX The width of the area
            * @param dY The height of the area
						* @param color The color of the area
						**/
            void GPU_FillRect (GPU_Layer* layer, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY, GPU_Color color);	
					/**
            *	@brief [BPU] Clear a rectangular area
            * @param layer In which plane we have to do this operation
            * @param x0 The x coordinate of the top left corner of the area
					  * @param y0 The y coordinate of the top left corner of the area
						* @param dX The width of the area
            * @param dY The height of the area
						**/
            void GPU_ClearRect(GPU_Layer* layer, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY);	
					/**
            *	@brief [BPU] Set the alpha level on a rectangular area 
						* @param layer In which plane we have to do this operation
            * @param x0 The x coordinate of the top left corner of the area
					  * @param y0 The y coordinate of the top left corner of the area
						* @param dX The width of the area
            * @param dY The height of the area
						* @param alpha The alpha level 
						**/
            void GPU_SetRectAlphaValue (GPU_Layer* layer, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY, uint8_t alpha);
					/**
            *	@brief [BPU] Blit a image
						* @param srcPlane The plane where the image come from
						* @param destPlane The plan where the image will be 
            * @param image The image to blit
						* @param dstX The x coordinate of the top left corner of the image destination
            * @param dstY The y coordinate of the top left corner of the image destination
						**/
            void GPU_BitBlitL2L(GPU_Layer* layer, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY, 
															 GPU_Layer* destLayer, uint16_t dstX, uint16_t dstY);
						void GPU_BitBlitI2L(GPU_Image *image, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY, 
															 GPU_Layer* destLayer, uint16_t dstX, uint16_t dstY) ;
					/**
            *	@brief [BPU] Set the alpha level on a rectangular area 
						* @param srcPlane The plane where the image come from
						* @param destPlane The plan where the image will be             
						* @param image The image to move
						* @param dstX The x coordinate of the top left corner of the image destination
            * @param dstY The y coordinate of the top left corner of the image destination
						**/
            void GPU_MoveL2L (GPU_Layer* layer, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY, 
														 GPU_Layer* destLayer, uint16_t dstX, uint16_t dstY);						
            void GPU_MoveI2L (GPU_Image *image, uint16_t x0, uint16_t y0, uint16_t dX, uint16_t dY, 
														 GPU_Layer* destLayer, uint16_t dstX, uint16_t dstY);						

					/**
            *	@brief NOT IMPLENMENTED
            **/
            void GPU_SetA1(uint32_t adresse_source,uint32_t adresse_dest, uint32_t taille_horizontal, uint32_t taille_vertical, uint16_t couleur, uint16_t alpha);
            void GPU_Move1(GPU_Layer*  srcLayer,GPU_Image *image,GPU_Layer* destLayer,uint32_t dstX,uint32_t dstY,GPU_Color Color);
					
					/**
            *	@brief Waiting for the BPU finishes this current operation
            **/
            uint8_t GPU_checkPGU(void);
					/**
            *	@brief [PGU] Set a pixel with a given color
            * @param plane In which plane we have to do this operation
						* @param X The x coordinate of the pixel
						* @param Y The y coordinate of the pixel
						* @param Color The color of the pixel
            **/
            void GPU_SetPixel (GPU_Layer* layer, uint16_t X, uint16_t Y, GPU_Color color);
					/**
            *	@brief [PGU] Clear a pixel
            * @param plane In which plane we have to do this operation
						* @param X The x coordinate of the pixel
						* @param Y The y coordinate of the pixel
            **/
            void GPU_ClearPixel (GPU_Layer* layer, uint16_t X, uint16_t Y);
					/**
            *	@brief [PGU] Draw a line with a given color, between two coordinates
            * @param plane In which plane we have to do this operation
						* @param X1 The x coordinate of starting point of the line
						* @param Y1 The y coordinate of starting point of the line
						* @param X2 The x coordinate of ending point of the line
						* @param Y2 The y coordinate of ending point of the line
						* @param Color The color of the line
						**/	
						void GPU_DrawLine (GPU_Layer* layer, uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, GPU_Color color);
					/**
            *	@brief [PGU] Draw a circle with a given color
            * @param plane In which plane we have to do this operation
						* @param X The x coordinate of the center of the circle
						* @param Y The y coordinate of the center of the circle
						* @param R The radius of the circle
						* @param Color The color of the circle
						**/
						void GPU_DrawCircle (GPU_Layer* layer, uint16_t X, uint16_t Y, uint16_t R, GPU_Color color);
					/**
            *	@brief [PGU] Write a character with a given color  (6x8 font)
            * @param plane In which plane we have to do this operation
						* @param X The x coordinate of starting point of the character (top-left)
						* @param Y The y coordinate of starting point of the character (top-left)
						* @param c The character to be drawn
						* @param Color The color of the character
						**/						
						void GPU_WriteChar (GPU_Layer* layer, uint16_t X, uint16_t Y, char c, GPU_Color color);
					/**
            *	@brief [PGU] Write a text with a given color  (6x8 font)
            * @param plane In which plane we have to do this operation
						* @param X The x coordinate of starting point of the character (top-left)
						* @param Y The y coordinate of starting point of the character (top-left)
						* @param str The text string to be drawn
						* @param Color The color of the character
						**/					
						void GPU_WriteText (GPU_Layer* layer, uint16_t X, uint16_t Y, char* str, GPU_Color color);
					/**
            *	@brief [PGU] Draw a rectangle with a given color, between two coordinates
            * @param plane In which plane we have to do this operation
						* @param X1 The x coordinate of the first corner of the rectange
						* @param Y1 The y coordinate of the first corner of the rectange
						* @param X2 The x coordinate of the opposite corner of the rectange
						* @param Y2 The y coordinate of the opposite corner of the rectange
						* @param Color The color of the line
						**/
						void GPU_DrawRect (GPU_Layer* layer, uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, GPU_Color color);
			/**
        * @}
        */

      /** @name DMA control
        * @{
        */
					/**
            *	@brief DMA functions
            **/
            uint8_t GPU_checkDMA (void);
						void GPU_PreSendDataToLayer(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy, GPU_Layer* layer);
						void GPU_PreSendDataToImage(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy, GPU_Image* image);
						void GPU_DMAStartTransfer(void);
						void GPU_DMAStopTransfer(void);

/**
        * @}
        */
  /**
    * @}
    */

/** @addtogroup Global Global variable
  * \brief variable
  * @{
  */
		extern GPU_Display_conf Display_conf;
		extern GPU_Layer Layer_1;
		extern GPU_Layer Layer_2;
		extern GPU_Layer Layer_3;
		extern GPU_Layer Layer_4;
		extern GPU_DMAconf	DMA_conf;
	/**
	* @}
	*/
#endif
