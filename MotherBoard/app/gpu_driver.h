/**
 * \file	gpu_driver.h
 * \brief Driver interface for STM32
 * \author Fauxpoint Guillaume & Sahin Serdar
 * \version 1
 * \date 2/05/2015
 *
 * Copyright (c) 2015, INSA-GEI Toulouse, France.
 * Tout droits réservés.
 */

	#ifndef GPU_DRIVER_H
	#define GPU_DRIVER_H

	#include <stm32f4xx.h>

/**
 * \page GPU_DRIVER GPU_DRIVER
 * \section GPU_DRIVER_intro Introduction
 *
 * This driver allow to establish a communication between an FPGA card and a STM32 microprocessor.
 * The communication use the FSMC peripheral with pins dedicated to the LCD.
 * If the FPGA is configured like a Graphic Card, you have the possibility to command it from the STM32.
 * The driver got many functions  to do the basic functionality of Graphic Card.
 * Data transfer is also available to access to the FPGAs RAM.
 *
 * \section GPU_DRIVER_dep Dependencies
 *  - \ref stm32f4__driver
 *
 *
 * \section GPU_DRIVER_reference List of APIs related to the driver
 *  - \ref GPU_DRIVER_Driver
 *  - \ref GPU_DRIVER_Class
 *  - \ref Service
 *  - \ref Global
 */
    /**
    *\addtogroup GPU_DRIVER_Driver Driver
    * \brief Driver : Basic function to allow and configure the communication between the two card
    *\{
    */
				/**
        *	@brief Wait procedure
        **/				
        void GPU_initFSMC(void);
        /**
        *	@brief Set the HLCK (FSMC clock)
        * @param a How much the HLCK will be divide, range 1 to 512
        **/
        void GPU_setClockFSMC(int a);
        /**
				*	@brief Initialize GPIO which are used by this driver
				*
				**/
        void GPU_init_GPIO_interface(void);
        /**
        *   @brief Allow to read the BUSY output pin
        * @return The value on the BUSY output pin
        **/
				
				void wait(int delay);
        /**
        *	@brief initialize and configure the FSMC
        **/
        uint8_t GPU_read_GPIO_busy(void);
        /**
        *	@brief Use the FSMC to write ADDR where you wish d
        * @param data The data which FSMC have to transfer
        **/
        void _gpu_access_addr(uint16_t addr);
        /**
        *	@brief Use the FSMC to write DATA on a specific adress
        * @param data The data which FSMC have to transfer
        **/
        void _gpu_write_data(uint16_t data);
        /**
        *	@brief Use the FSMC to read DATA on a specific adress
        * @return The data which FSMC have to read
        **/
        uint16_t _gpu_read_data(void);
        /**
        *	@brief Send data to the FPGA with the three cycle protocol
        * @param registre The adress where to tranfer the DATA
        * @param data The data that FSMC have to transfer
        **/
        void GPU_WriteReg(uint16_t addr, uint16_t data);
        /**
        *	@brief Read data to the FPGA with the three cycle protocol
        * @param registre The adress where to tranfer the DATA
        * @return data The data that FSMC had to read
        **/
        uint16_t GPU_ReadReg(uint16_t addr);
		/**
    * @}
    */ //Fin groupe driver


	/** @addtogroup GPU_DRIVER_Defines Defines
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
			#define		GPU_FSMC_ADDSET					10
			/**
			*	@brief Number of HLCK period to hold the DATA, range : 0 to 25
			*/
				#define		GPU_FSMC_DATAST					10
			/**
			 *@brief Time between two FSMC operation, range : 0 to 16
			*/
			#define		GPU_FSMC_BUSTURN					10
		/**
      * @}
      */  //Fin FSMC

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
          *@brief GPU REGISTER ADRESS ADRESS
          */
					#define GPU_ADDR 					0x6C000000
				/**
          *@brief GPU REGISTER DATA ADRESSS
          */
					#define GPU_DATA 					0x6C000002
				/**
          *@brief GPU Pointers
          */
				#define GPU_BASE   (0x60000000UL | 0x0C000000UL)
        #define GPU_ADDR16  (*((volatile uint16_t *)(GPU_BASE  )))
				#define GPU_DATA16  (*((volatile uint16_t *)(GPU_BASE+2)))
			/**
        * @}
         */ // Fin memoire

			/** @name FrameBuffer register address
        * @{
        */
        #define		FBCTRL				0x0000
        #define		FBP1ADDR_L 		0x0001
        #define		FBP1ADDR_H		0x0002
        #define		FBP1SIZE_L		0x0003
				#define		FBP1SIZE_H		0x0004
				#define		FBP1SCRL_L		0x0005
				#define		FBP1SCRL_H		0x0006
				#define		FBP2ADDR_L		0x0007
				#define		FBP2ADDR_H		0x0008
				#define		FBP2SIZE_L		0x0009
				#define		FBP2SIZE_H		0x000A
				#define		FBP2SCRL_L		0x000B
				#define		FBP2SCRL_H		0x000C
				#define		FBP3ADDR_L		0x000D
				#define		FBP3ADDR_H		0x000E
				#define		FBP3SIZE_L		0x000F
				#define		FBP3SIZE_H		0x0010
				#define		FBP3SCRL_L		0x0011
				#define		FBP3SCRL_H		0x0012
				#define		FBP4ADDR_L		0x0013
				#define		FBP4ADDR_H		0x0014
				#define		FBP4SIZE_L		0x0015
				#define		FBP4SIZE_H		0x0016
				#define		FBP4SCRL_L		0x0017
				#define		FBP4SCRL_H		0x0018
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
				#define		BPUSRCADDR_L  0x0301
				#define		BPUSRCADDR_H	0x0302
				#define		BPUPICSIZE_L	0x0303
				#define		BPUPICSIZE_H	0x0304
				#define		BPUSIZE_L			0x0305
				#define		BPUSIZE_H			0x0306
				#define		BPUDSTADDR_L	0x0307
				#define		BPUDSTADDR_H	0x0308
				#define		BPUFILCOL 		0x0309
				#define		BPUSAR 				0x030A
				#define		BPUDUMADDR_L	0x030B
				#define		BPUDUMADDR_H	0x030C
			/**
        * @}
        */
			/** @name PGU register address
        * @{
        */
				#define		PGUCTRL 			0x0400
				#define		PGUCOLOR 			0x0401
				#define		PGUDSTADDR_L	0x0402
				#define		PGUDSTADDR_H	0x0403
				#define		PGUDSTLEN 		0x0404
				#define		PGULC1R_L 		0x0405
				#define		PGULC1R_H			0x0406
				#define		PGULC2R_L			0x0407
				#define		PGULC2R_H			0x0408
				#define		PGUCHAR 			0x0409
			/**
        * @}
        */
			/** @name DMA register Address
            * @{
            */
			#define		DMACTRL				0x0500
			#define		DMAIMGSIZE		0x0501
			#define		DMAPIXCNT			0x0502
			#define		DMADSTADDR		0x0503
			#define 	DMADSTSIZER		0x0504
			/**
        * @}
        */
    /**
      * @}
      */  //Fin memory address
	/**
    * @}
    */
  /**
    * @}
    */
#endif
