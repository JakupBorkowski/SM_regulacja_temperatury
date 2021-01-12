/**
  ******************************************************************************
  * @file    led_pwm.h
  * @author  AW 
  * @version V1.0
  * @date    05-Nov-2020
  * @brief   Simple LED driver library with PWM control.
  *
  ******************************************************************************
  */
#ifndef INC_LED_PWM_H_
#define INC_LED_PWM_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Typedef -------------------------------------------------------------------*/
#define LED_PWM_TimerType   TIM_HandleTypeDef*
#define LED_PWM_ChannelType uint16_t

typedef struct {
  LED_PWM_TimerType Timer;
  LED_PWM_ChannelType Channel;
} LED_PWM_HandleTypeDef;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

void LED_PWM_Init(LED_PWM_HandleTypeDef* hledpwm);

void LED_PWM_SetDuty(LED_PWM_HandleTypeDef* hledpwm, float duty);

#endif /* INC_LED_PWM_H_ */
