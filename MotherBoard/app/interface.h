/**
 * \file	interface.h
 * \brief Driver interface for STM32
 * \author Guillaume Fauxpoint, Oussama El Fatayri, Sahin Serdar, Hugo Bevilacqua (4AE-SE) 
 * \version v1
 * \date 24/05/2014
 *
 * Copyright (c) 2014, INSA-GEI Toulouse, France.
 * Tout droits réservés.
 */



	#ifndef INTERFACE_H
	#define INTERFACE_H

	#include <stm32f4xx.h>
	#include "global.h"
	#include "stm32f4_discovery_sdio_sd.h"
	#include "stm32f4_discovery.h"
	#include "ff.h"
	#include "diskio.h"
	#include "interface.h"

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
 * \section INTERFACE_exemples Examples
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
	#include "interface.h"

	int main (void)
	{
	GPU_Color Serdar;

	GPU_Init(void);

	Initialize_Button(USER);
	Initialize_Button(TAMPER);

	Serdar.R = 3;
	Serdar.G = 1;
	Serdar.B = 16;
	Serdar.A = 4;

	while(1)
	{
		if (!is_button_pressed(TAMPER))
		{
			GPU_MoveRect (Plan_Trois ,0,0,100,100,Plan_Trois,100,100);

			while (!is_button_pressed(TAMPER));

		}

	}
	}

	 \endcode
 *
 */



    /**
    *\addtogroup INTERFACE_Driver Driver
    * \brief Driver : Basic function to allow and configure the communication between the two card
    *\{
    */

				/**
        *	@brief Wait procedure
        **/


				void Wait(int delay);
				
				
				
        /**
        *	@brief initialize and configure the FSMC
        **/


        int GPU_initFSMC(void);

        /**
        *	@brief Set the HLCK (FSMC clock)
        * @param a How much the HLCK will be divide, range 1 to 512
        **/

        int GPU_setClockFSMC(int a);

        /**
        *	@brief initialize and configure SD
        **/

        int GPU_init_SD(void);

        /**
        *	@brief Send to the FPGA the content of a file
        * @param name_file Name of the file to transfer, this file should be present on the SD card.
        **/

        int GPU_SD_TO_US (int name_file);

        /**
		*	@brief Initialize GPIO which are used by this driver
		*
		**/

        int GPU_init_GPIO_interface(void);

        /**
        *   @brief Allow to read the BUSY output pin
        * @return The value on the BUSY output pin
        **/

        uint8_t GPU_read_GPIO_busy(void);

        /**
        *	@brief Use the FSMC to write DATA on a specific adress
        * @param data The data which FSMC have to transfer
        **/

        int ecriture_registre(uint16_t data);

        /**
        *	@brief Use the FSMC to read DATA on a specific adress
        * @return The data which FSMC have to read
        **/

        uint16_t lecture_registre(void);

        /**
        *	@brief Send data to the FPGA with the three cycle protocol
        * @param registre The adress where to tranfer the DATA
        * @param data The data that FSMC have to transfer
        **/

        int GPU_WriteReg(uint16_t registre, uint32_t data);

        /**
        *	@brief Read data to the FPGA with the three cycle protocol
        * @param registre The adress where to tranfer the DATA
        * @return data The data that FSMC had to read
        **/

        uint32_t GPU_ReadReg(uint16_t registre);

	/**
    * @}
    */ //Fin groupe driver


	/** @addtogroup INTERFACE_Defines Defines
    * \brief Macro of this API
    * @{
    */

		/** @name FSMC Configuration parameter
        * @{
        */

			/**
			*	@brief HLCK division, range : 2 to 512 except 32
			*/
			#define		GPU_DIVISION_CLOCK_FSMC	1
			/**
			*@brief Number of HLCK period to hold the address, range : 0 to 15
			*/
			#define		GPU_FSMC_ADDSET					15
			/**
			*	@brief Number of HLCK period to hold the DATA, range : 0 to 255
			*/
				#define		GPU_FSMC_DATAST					25
			/**
			 *@brief Time between two FSMC operation, range : 0 to 16
			*/
			#define		GPU_FSMC_BUSTURN					15



		/**
        * @}
        */  //Fin FSMC


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

			#define		FIRST_PLANE_ENABLE				0x1
			#define		SECOND_PLANE_ENABLE 			0x2
			#define		THIRD_PLANE_ENABLE				0x4
			#define		FOURTH_PLANE_ENABLE 			0x8



		/**
        * @}
        */



		/** @name PIXEL Specificaton
        * @{
        */

        /**
        *@brief Size of one pixel in the FPGAs RAM
        */

			#define PIXEL_SIZE 24

        /**
        * @}
        */  // Fin pixel

		/** @name SCREEN specificaton (pixel)
		* @{
		*/

			#define SCREEN_WIDTH 320
			#define SCREEN_HEIGTH 240


		/**
        * @}
        */  // Fin ecran

		/** @name Memory address
        * @{
        */

			/** @name Graphic Card adress memory (STM32 side)
            * @{
            */
                /**
                *@brief RAM address
                */
								#define CG_RAM 					0x6C000002

                /**
                *@brief Register address
                */
								#define CG_REG 					0x6C000000

								/**
                *@brief SD Fifo address
                */
								#define SD_ADRESSE			SDIO_FIFO_ADDRESS
								
								/**
                *@brief GPU address
                */
								#define CG_BASE   (0x60000000UL | 0x0C000000UL)
								
								/**
                *@brief DATA of the GPU register
                */
								#define CG_REG16  (*((volatile uint16_t *)(CG_BASE  )))
									
								/**
                *@brief DATA of the GPU RAM
                */
								#define CG_DAT16  (*((volatile uint16_t *)(CG_BASE+2)))
			

						/**
            * @}
            */ // Fin memoire

						/** @name FrameBuffer register address
            * @{
            */

                #define		FBCTRL				0x0000
                #define		FBP1ADDR 			0x0001
                #define		FBP1SIZE 			0x0002
                #define		FBP1SCRL 			0x0003
                #define		FBP2ADDR 			0x0004
                #define		FBP2SIZE 			0x0005
                #define		FBP2SCRL 			0x0006
                #define		FBP3ADDR 			0x0007
                #define		FBP3SIZE 			0x0008
                #define		FBP3SCRL 			0x0009
                #define		FBP4ADDR 			0x000A
                #define		FBP4SIZE 			0x000B
                #define		FBP4SCRL 			0x000C
						/**
            * @}
            */   // Fin FB


							/** @name Output video register address
            * @{
            */

					#define		DCMODE 				0x0100

					/**
            * @}
            */


			/** @name LCD register address
            * @{
            */

					#define		LCDCTRL				0x0200
					#define		LCDTEST 			0x0201
					#define		LCDFILT 			0x0202
					#define		LCDCON 				0x0203
					#define		LCDBRI 				0x0204
					#define		LCDSBRI 			0x0205
					#define		LCDHS 				0x0206


			/**
            * @}
            */

			/** @name BPU register Address
            * @{
            */

					#define		BPUCTRL 			0x0300
					#define		BPUSRCADDR 		    0x0301
					#define		BPUPICSIZE		    0x0302
					#define		BPUSIZE 			0x0303
					#define		BPUDSTADDR 		    0x0304
					#define		BPUFILCOL 		    0x0305
					#define		BPUSAR 				0x0306
					#define		BPUDUMADDR 		    0x0307

			/**
            * @}
            */

			/** @name PGU register address
            * @{
            */

					#define		PGUCTRL 			0x0400
					#define		PGUCOLOR 			0x0401
					#define		PGUDSTADDR 		    0x0402
					#define		PGUDSTLEN 		    0x0403
					#define		PGULC1R 			0x0404
					#define		PGULC2R 			0x0405
					#define		PGUCHAR 			0x0406

			/**
            * @}
            */


			/** @name DMA register Address
            * @{
            */

					#define		DMACTRL				    0x0500
					#define		DMAIMGSIZE		    0x0501
					#define		DMAPIXCNT			    0x0502
					#define		DMADSTADDR		    0x0503
					#define 	DMADSTSIZER		    0x0504

			/**
            * @}
            */




			/** @name Specific macro of FPGA
            * @{
            */

                /**
                *@brief Buffer address
                */

				#define 	ADRESSE_TEMPON				0x0700000

                /**
                *@brief Start plane address
                */
				#define 	START_ADRESSE_DATA_PLANE1	0x0000000
				#define 	START_ADRESSE_DATA_PLANE2	0x0050000
				#define 	START_ADRESSE_DATA_PLANE3	0x0070000
				#define 	START_ADRESSE_DATA_PLANE4	0x0090000


			/**
            * @}
            */

        /**
        * @}
        */  //Fin memory address


	/**
    * @}
    */


	/** @defgroup INTERFACE_Class Class
    * \brief Class
    * @{
    */


        /**
        * @brief  Plane structure
        */

        struct GPU_Plane
        {
            uint32_t numero;
            uint32_t Addr;
            uint32_t Plane_Width;
            uint32_t Plane_Height;
            uint32_t ScrollDx;
            uint32_t ScrollDy;
        }typedef GPU_Plane;

        /**
        * @brief  Plane configuration structure
        */

            struct GPU_Plane_conf
        {
            uint32_t Enable;
            uint32_t Plan_Enable;
            uint32_t Test_On;
            uint32_t Alpha_On;
        }typedef GPU_Plane_conf;


        /**
        * @brief  Color structure
        */

        struct GPU_Color
        {
            uint16_t R;
            uint16_t G;
            uint16_t B;
            uint16_t A;

        }typedef GPU_Color;


        /**
        * @brief  Image structure
        */

        struct GPU_Image
        {
            char * Nom;
            uint32_t Width;
            uint32_t Height;
            uint32_t Adresse;
                
        }typedef GPU_Image;


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

            int GPU_Init(void);

            /**
            * @brief Configure the output signal (VGA or LCD)
            * @param choix 1 = VGA, 0 = LCD
            **/

            int GPU_ConfigureOutput(int choix);

            /**
            * @brief Enable or disable the test program of the FPGA
            * @param testOn 1 = Enable, 0 = Disable
            **/

            int GPU_VideoSignalTest (uint32_t testOn);


		/**
        * @}
        */


    	/** @name Color structure function
        * @{
        */

            /**
            * @brief Initialize a new color structure
            * @param color The color pointer to initialize
            * @param rouge Red's pourcentage of this color , range 0 to 16
            * @param vert Green's pourcentage of this color , range 0 to 16
            * @param bleu Blue's pourcentage of this color , range 0 to 16
            * @param alpha Alpha transparency level
            **/

            int GPU_NewColor(GPU_Color *color,int rouge, int vert, int bleu, int alpha);


		/**
        * @}
        */


        /** @name Image structure function
        * @{
        */

            /**
            * @brief Initialize a new image structure
            * @param image The image pointer to initialize
            * @param Width The width of this image
            * @param Height The height of this image
            * @param nom The name of this image
						* @param Addr The address of this image
            **/

            int GPU_NewImage(GPU_Image *image,uint32_t Width,uint32_t Height, char * nom,uint32_t Addr);


		/**
        * @}
        */



    	/** @name Plane and Plane_conf structure function
        * @{
        */

            /**
            *	@brief Initialize the plane structure
            * @param NumPlan The number of the plane to initialize (1 to 4)
            **/

            int GPU_InitPlan(int NumPlan);


            /**
            *	@brief Configure the different planes
            * @param plane Define the plane to configure
            * @param planeBaseAddr Plane's address on the FPGA RAM
            * @param planeWidth Width of the plane (Pixel)
            * @param planeHeight Height of the plane (Pixel)
            **/

            int GPU_ConfigurePlane (GPU_Plane plane, uint32_t planeBaseAddr, uint32_t planeWidth, uint32_t planeHeight);



            /**
            *	@brief Send the configuration plane update to the FPGA
            **/

            int GPU_MAJ_PLAN(void);


        /**
        * @}
        */

        /** @name Display control
        * @{
        */

            /**
            *	@brief Disable the frame buffer
            **/

            int disable_FB(void);

            /**
            *	@brief Enable the plane
            * @param planeFlags use the define FIRST_PLAN_ENABLE, SECOND_PLAN_ENABLE, THIRD_PLAN_ENABLE, FOURTH_PLAN_ENABLE
            **/

            int GPU_PlaneeEnable (uint32_t planeFlags);

            /**
            *	@brief Enable the transparency
            * @param AlphaNBinary 1 = enable, 0 = disable;
            **/

            int GPU_TransparenceMode (uint32_t AlphaNBinary);

            /**
            *	@brief Do a horizontal scrolling operation on a plane
            * @param plane Plane to scroll
            * @param dX Range
            * @param sens Direction, 0 => left, 1 => right
            **/

            int GPU_HScroll (GPU_Plane plane, uint32_t dX, int sens);

            /**
            *	@brief Do a vertical scrolling operation on a plane
            * @param plane Plane to scroll
            * @param dY Range
            * @param sens Direction, 0 => top, 1 => bot
            **/

            int GPU_VScroll (GPU_Plane plane, uint32_t dY, int sens);



        /**
        * @}
        */

        /** @name LCD configuration
        * @{
        */

            /**
            *	@brief Ajust the contrast level on the LCD
            * @param cont Contrast level , range 0 to ??
            **/

            int GPU_LCD_AjustContrast(uint32_t cont);

            /**
            *	@brief Ajust the brightness level on the LCD
            * @param cont brightness level , range 0 to ??
            **/
						
						/**
            *	@brief NOT IMPLENMENTED
            **/

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
            *	@brief Waiting for the gpu to finishe his current operation
            **/

            int GPU_verif_status(void);
						
						/**
            *	@brief Set a pixel with a given color
            * @param plane In which plane we have to do this operation
						* @param X The x coordinate of the pixel
						* @param Y The y coordinate of the pixel
						* @param Color The color of the pixel
            **/

            int GPU_SetPixel (GPU_Plane plane, int X, int Y, GPU_Color color);
						
						/**
            *	@brief Clear a pixel
            * @param plane In which plane we have to do this operation
						* @param X The x coordinate of the pixel
						* @param Y The y coordinate of the pixel
            **/

            int GPU_ClearPixel (GPU_Plane plane, int X, int Y);
						
						
						/**
            *	@brief Draw a line with a given color, between two coordinates
            * @param plane In which plane we have to do this operation
						* @param X1 The x coordinate of starting point of the line
						* @param Y1 The y coordinate of starting point of the line
						* @param X2 The x coordinate of ending point of the line
						* @param Y2 The y coordinate of ending point of the line
						* @param Color The color of the line
						**/
						
						int GPU_DrawLine (GPU_Plane plane, int X1, int Y1, int X2, int Y2, GPU_Color color);
						

						/**
            *	@brief Draw a circle with a given color
            * @param plane In which plane we have to do this operation
						* @param X The x coordinate of the center of the circle
						* @param Y The y coordinate of the center of the circle
						* @param R The radius of the circle
						* @param Color The color of the circle
						**/
						
						int GPU_DrawCircle (GPU_Plane plane, int X, int Y, int R, GPU_Color color);

						
						/**
            *	@brief Write a character with a given color  (6x8 font)
            * @param plane In which plane we have to do this operation
						* @param X The x coordinate of starting point of the character (top-left)
						* @param Y The y coordinate of starting point of the character (top-left)
						* @param c The character to be drawn
						* @param Color The color of the character
						**/
						
						int GPU_WriteChar (GPU_Plane plane, int X, int Y, char c, GPU_Color color);
						
						/**
            *	@brief Write a text with a given color  (6x8 font)
            * @param plane In which plane we have to do this operation
						* @param X The x coordinate of starting point of the character (top-left)
						* @param Y The y coordinate of starting point of the character (top-left)
						* @param str The text string to be drawn
						* @param Color The color of the character
						**/
						
						int GPU_WriteText (GPU_Plane plane, int X, int Y, char* str, GPU_Color color);
												
						/**
            *	@brief Draw a rectangle with a given color, between two coordinates
            * @param plane In which plane we have to do this operation
						* @param X1 The x coordinate of the first corner of the rectange
						* @param Y1 The y coordinate of the first corner of the rectange
						* @param X2 The x coordinate of the opposite corner of the rectange
						* @param Y2 The y coordinate of the opposite corner of the rectange
						* @param Color The color of the line
						**/
						
						int GPU_DrawRect (GPU_Plane plane, int X1, int Y1, int X2, int Y2, GPU_Color color);
						

						
						 /**
            *	@brief Clear all of the pixel of a plane
            * @param plane In which plane we have to do this operation
            **/
            int GPU_ClearScreen (GPU_Plane plane);

						 /**
            *	@brief Fill a rectangular area at a given color
						* @param plane In which plane we have to do this operation
            * @param X0 The x coordinate of the top left corner of the area
					  * @param Y0 The y coordinate of the top left corner of the area
						* @param dX The width of the area
            * @param dY The height of the area
						* @param color The color of the area
						**/

            int GPU_FillRect (GPU_Plane plane,uint32_t X0,uint32_t Y0,uint32_t dX,uint32_t dY,GPU_Color Color);
						
						 /**
            *	@brief Clear a rectangular area
            * @param plane In which plane we have to do this operation
            * @param X0 The x coordinate of the top left corner of the area
					  * @param Y0 The y coordinate of the top left corner of the area
						* @param dX The width of the area
            * @param dY The height of the area
						**/

            int GPU_ClearRect(GPU_Plane plane,uint32_t X0,uint32_t Y0,uint32_t dX,uint32_t dY);
						
					 /**
            *	@brief Set the alpha level on a rectangular area 
						* @param plane In which plane we have to do this operation
            * @param X0 The x coordinate of the top left corner of the area
					  * @param Y0 The y coordinate of the top left corner of the area
						* @param dX The width of the area
            * @param dY The height of the area
						* @param alpha The alpha level 
						**/

            int GPU_SetRectAlphaValue (GPU_Plane plane,uint32_t X0,uint32_t Y0,uint32_t dX,uint32_t dY, uint32_t alpha);
						
						 /**
            *	@brief Blit a image
						* @param srcPlane The plane where the image come from
						* @param destPlane The plan where the image will be 
            * @param image The image to blit
						* @param dstX The x coordinate of the top left corner of the image destination
            * @param dstY The y coordinate of the top left corner of the image destination
						**/

            int GPU_BitBlitRect (GPU_Plane srcPlane,GPU_Image *image,GPU_Plane destPlane,uint32_t dstX,uint32_t dstY);
						
						 /**
            *	@brief Blit a image, version 2
						* @param x  The x coordinate of the image to blit
						* @param y	The y coordinate of the image to blit
            * @param dx The width of the image
						* @param dy The height of the image
            * @param destPlane The plan where the image will be 
            * @param image The image to blit
						* @param dstX The x coordinate of the top left corner of the image destination
            * @param dstY The y coordinate of the top left corner of the image destination
						**/
						
						int GPU_BitBlitRectV2 (uint32_t x,uint32_t y,uint32_t dx,uint32_t dy, GPU_Image *image,GPU_Plane destPlane,uint32_t dstX,uint32_t dstY) ;

						
						 /**
            *	@brief Set the alpha level on a rectangular area 
						* @param srcPlane The plane where the image come from
						* @param destPlane The plan where the image will be             
						* @param image The image to move
						* @param dstX The x coordinate of the top left corner of the image destination
            * @param dstY The y coordinate of the top left corner of the image destination
						**/

            int GPU_MoveRect (GPU_Plane srcPlane,GPU_Image *image,GPU_Plane destPlane,uint32_t dstX,uint32_t dstY);
						
					 /**
            *	@brief Set the alpha level on a rectangular area 
						* @param srcPlane The plane where the image come from
						* @param destPlane The plan where the image will be 
						* @param dstX The x coordinate of the top left corner of the image destination
            * @param dstY The y coordinate of the top left corner of the image destination
						* @param Color The color to fill at the old place of the image
						**/

            int GPU_Move1_bpu(GPU_Plane srcPlane,GPU_Image *image,GPU_Plane destPlane,uint32_t dstX,uint32_t dstY,GPU_Color Color);
						
						/**
            *	@brief NOT IMPLENMENTED
            **/

            int seta1_bpu(uint32_t adresse_source,uint32_t adresse_dest, uint32_t taille_horizontal, uint32_t taille_vertical, uint16_t couleur, uint16_t alpha);


        /**
        * @}
        */

        /** @name DMA control
        * @{
        */

						 /**
            *	@brief Give information about the FPGA DMA status
            * @return Status of the FPGA DMA
            **/

            int GPU_StatusDMA (void);

						/**
            *	@brief Prepare the FPGA DMA to receive data
						* @param image The image to send
						* @param dx The x ccordinate of the image destination
						* @param dy The x ccordinate of the image destination
						* @param plan The plan to transfert the image
            **/

            int GPU_PreSendData(GPU_Image *image, uint32_t dx, uint32_t dy, GPU_Plane plan);


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

	extern	GPU_Plane_conf PLANE;
	extern	GPU_Plane Plane_One;
	extern	GPU_Plane Plane_Two;
	extern	GPU_Plane Plane_Three;
	extern	GPU_Plane Plane_Four;

	/**
	* @}
	*/



#endif
