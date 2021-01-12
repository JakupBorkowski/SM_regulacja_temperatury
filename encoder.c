/**
  ******************************************************************************
  * @file    encoder.c
  * @author  AW 
  * @version V1.0
  * @date    30-Oct-2020
  * @brief   Simple rotary encoder driver library. 
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "encoder.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

#ifdef ENC_HARDWARE_COUNTER

int32_t ENC_Init(ENC_HandleTypeDef* henc)
{
	HAL_TIM_Encoder_Start(henc->Timer, TIM_CHANNEL_ALL);
}

uint32_t ENC_GetCounter(ENC_HandleTypeDef* henc)
{
	henc->Counter = henc->Timer->Instance->CNT;
	return henc->Counter;
}

#else

/**
 * @brief Rotary encoder software counter update procedure
 * @param hbtn Encoder handler
 * @retval Current counter value
 */
int32_t ENC_UpdateCounter(ENC_HandleTypeDef* henc)
{
  GPIO_PinState dt = HAL_GPIO_ReadPin(henc->DT_Port, henc->DT_Pin);
  
  if(dt == GPIO_PIN_RESET)
    henc->Counter = (henc->Counter >= henc->CounterMax) ? henc->CounterMax : (henc->Counter + henc->CounterStep);
  else
    henc->Counter = (henc->Counter <= henc->CounterMin) ? henc->CounterMin : (henc->Counter - henc->CounterStep);
  
  return henc->Counter;
}

#endif
