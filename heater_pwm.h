/**
  ******************************************************************************
  * @file    heater_pwm.h
  * @author  AW
  * @version V1.0
  * @date    15-Nov-2020
  * @brief   Simple PWM-controled heater driver library
  *
  ******************************************************************************
  */
#ifndef INC_HEATER_PWM_H_
#define INC_HEATER_PWM_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Typedef -------------------------------------------------------------------*/
#define HEATER_PWM_TimerType   TIM_HandleTypeDef*
#define HEATER_PWM_ChannelType uint16_t

typedef struct {
  HEATER_PWM_TimerType Timer;
  HEATER_PWM_ChannelType Channel;
} HEATER_PWM_HandleTypeDef;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

void HEATER_PWM_Init(HEATER_PWM_HandleTypeDef* hheaterpwm);

void HEATER_PWM_SetDuty(HEATER_PWM_HandleTypeDef* hheaterpwm, float duty);

#endif /* INC_HEATER_PWM_H_ */
