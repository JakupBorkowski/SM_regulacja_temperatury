/**
  ******************************************************************************
  * @file    bh1750.c
  * @author  AW
  * @version V1.0
  * @date    04-Nov-2020
  * @brief   Simple driver for digital light sensor with I2C: BH1750
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "bh1750.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

void BH1750_Init(BH1750_HandleTypeDef* hbh1750)
{
  uint8_t command;

  command = BH1750_POWER_ON;
  HAL_I2C_Master_Transmit(hbh1750->I2C, hbh1750->Address, &command, 1, hbh1750->Timeout);

  command = BH1750_CONTINOUS_H_RES_MODE;
  HAL_I2C_Master_Transmit(hbh1750->I2C, hbh1750->Address, &command, 1, hbh1750->Timeout);
}

float BH1750_ReadLux(BH1750_HandleTypeDef* hbh1750)
{
	float light = 0;
	uint8_t buff[2];

	HAL_I2C_Master_Receive(hbh1750->I2C, hbh1750->Address, buff, 2, hbh1750->Timeout);

	light = ((buff[0]<<8) | buff[1]) / 1.2; // @see BH1750 technical note p. 10

	return light;
}
