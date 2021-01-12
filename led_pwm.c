/**
  ******************************************************************************
  * @file    led_pwm.c
  * @author  AW
  * @version V1.0
  * @date    05-Nov-2020
  * @brief   Simple LED driver library with PWM control.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "led_pwm.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

void LED_PWM_Init(LED_PWM_HandleTypeDef* hledpwm)
{
  HAL_TIM_PWM_Start(hledpwm->Timer, hledpwm->Channel);
}

void LED_PWM_SetDuty(LED_PWM_HandleTypeDef* hledpwm, float duty)
{
  int COMPARE = (duty * (__HAL_TIM_GET_AUTORELOAD(hledpwm->Timer)+1)) / 100;
  __HAL_TIM_SET_COMPARE(hledpwm->Timer, hledpwm->Channel, COMPARE);
}
