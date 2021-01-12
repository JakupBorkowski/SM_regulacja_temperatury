/**
  ******************************************************************************
  * @file    bh1750.h
  * @author  AW 
  * @version V1.0
  * @date    04-Nov-2020
  * @brief   Simple driver for digital light sensor with I2C: BH1750
  *
  ******************************************************************************
  */
#ifndef INC_BH1750_H_
#define INC_BH1750_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Typedef -------------------------------------------------------------------*/
#define BH1750_I2CType I2C_HandleTypeDef*

typedef struct {
  BH1750_I2CType I2C;
  uint8_t Address;
  uint32_t Timeout;
} BH1750_HandleTypeDef;

/* Define --------------------------------------------------------------------*/
#define BH1750_ADDRESS_L (0x23 << 1)     //! ADDR = 'L' @see BH1750 technical note p. 10
#define BH1750_ADDRESS_H (0x5C << 1)     //! ADDR = 'H' @see BH1750 technical note p. 10

#define BH1750_POWER_DOWN				0x00
#define BH1750_POWER_ON					0x01
#define BH1750_RESET					0x07
#define BH1750_CONTINOUS_H_RES_MODE		0x10
#define BH1750_CONTINOUS_H_RES_MODE2	0x11
#define BH1750_CONTINOUS_L_RES_MODE		0x13
#define BH1750_ONE_TIME_H_RES_MODE		0x20
#define BH1750_ONE_TIME_H_RES_MODE2		0x21
#define BH1750_ONE_TIME_L_RES_MODE		0x23

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

void BH1750_Init(BH1750_HandleTypeDef* hbh1750);

float BH1750_ReadLux(BH1750_HandleTypeDef* hbh1750);


#endif /* INC_BH1750_H_ */
