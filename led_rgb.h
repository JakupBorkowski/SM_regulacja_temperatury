/**
  ******************************************************************************
  * @file    led_rgb.h
  * @author  AW 
  * @version V1.0
  * @date    02-Nov-2020
  * @brief   Simple tricolor (RGB) LED driver library.
  *
  ******************************************************************************
  */
#ifndef INC_LED_RGB_H_
#define INC_LED_RGB_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Typedef -------------------------------------------------------------------*/
#define LED_RGB_TimerType   TIM_HandleTypeDef*
#define LED_RGB_ChannelType uint16_t

typedef struct {
  LED_RGB_TimerType Timer;
  LED_RGB_ChannelType ChannelR;
  LED_RGB_ChannelType ChannelG;
  LED_RGB_ChannelType ChannelB;
} LED_RGB_HandleTypeDef;

typedef enum {
	LED_CHANNEL_R,
	LED_CHANNEL_G,
	LED_CHANNEL_B
} LED_Channel;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

void LED_RGB_Init(LED_RGB_HandleTypeDef* hledrgb);

void LED_RGB_SetDuty(LED_RGB_HandleTypeDef* hledrgb, LED_Channel ch, float duty);

void LED_RGB_SetColor(LED_RGB_HandleTypeDef* hledrgb, uint32_t color);

#endif /* INC_LED_RGB_H_ */
