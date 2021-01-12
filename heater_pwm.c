/**
  ******************************************************************************
  * @file    heater_pwm.c
  * @author  AW
  * @version V1.0
  * @date    15-Nov-2020
  * @brief   Simple PWM-controled heater driver library
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "heater_pwm.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

void HEATER_PWM_Init(HEATER_PWM_HandleTypeDef* hheaterpwm)
{
  HAL_TIM_PWM_Start(hheaterpwm->Timer, hheaterpwm->Channel);
}

void HEATER_PWM_SetDuty(HEATER_PWM_HandleTypeDef* hheaterpwm, float duty)
{
  int COMPARE = (duty * (__HAL_TIM_GET_AUTORELOAD(hheaterpwm->Timer)+1)) / 100;
  __HAL_TIM_SET_COMPARE(hheaterpwm->Timer, hheaterpwm->Channel, COMPARE);
}
