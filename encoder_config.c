/**
  ******************************************************************************
  * @file    encoder_config.h
  * @author  AW 
  * @version V1.0
  * @date    30-Oct-2020
  * @brief   Simple rotary encoder driver library configuration file. 
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "encoder.h"
#include "encoder_config.h"
#include "main.h"
#ifdef ENC_HARDWARE_COUNTER
#include "tim.h"
#endif
/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
#ifdef ENC_HARDWARE_COUNTER

ENC_HandleTypeDef henc1 = {
  .Timer = &htim4,
  .Counter  = temperatura_zadana,
};


#else
extern int32_t temperatura_zadana;
ENC_HandleTypeDef henc1 = {
  .CLK_Port = ENC_CLK_GPIO_Port, .CLK_Pin = ENC_CLK_Pin,
  .DT_Port  = ENC_DT_GPIO_Port,  .DT_Pin  = ENC_DT_Pin,
  .CounterMax = 3700, .CounterMin = 2500, .CounterStep = 10
};

#endif

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/
