/**
  ******************************************************************************
  * @file    led_rgb.c
  * @author  AW 
  * @version V1.0
  * @date    02-Nov-2020
  * @brief   Simple tricolor (RGB) LED driver library.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "led_rgb.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

void LED_RGB_Init(LED_RGB_HandleTypeDef* hledrgb)
{
  HAL_TIM_PWM_Start(hledrgb->Timer, hledrgb->ChannelR);
  HAL_TIM_PWM_Start(hledrgb->Timer, hledrgb->ChannelG);
  HAL_TIM_PWM_Start(hledrgb->Timer, hledrgb->ChannelB);
}

void LED_RGB_SetDuty(LED_RGB_HandleTypeDef* hledrgb, LED_Channel ch, float duty)
{
  LED_RGB_ChannelType channel = 0;
  switch(ch)
  {
    case LED_CHANNEL_R:
	  channel = hledrgb->ChannelR;
	  break;
    case LED_CHANNEL_G:
	  channel = hledrgb->ChannelG;
	  break;
    case LED_CHANNEL_B:
	  channel = hledrgb->ChannelB;
	  break;
    default:
      break;
  }

  int COMPARE = (duty * (__HAL_TIM_GET_AUTORELOAD(hledrgb->Timer)+1)) / 100;
  __HAL_TIM_SET_COMPARE(hledrgb->Timer, channel, COMPARE);
}

void LED_RGB_SetColor(LED_RGB_HandleTypeDef* hledrgb, uint32_t color)
{
  uint8_t R,G,B;

  R = (uint8_t)(color >> 16);
  G = (uint8_t)(color >> 8);
  B = (uint8_t)color;

  LED_RGB_SetDuty(hledrgb, LED_CHANNEL_R, ((float)R * 100.0) / 255.0);
  LED_RGB_SetDuty(hledrgb, LED_CHANNEL_G, ((float)G * 100.0) / 255.0);
  LED_RGB_SetDuty(hledrgb, LED_CHANNEL_B, ((float)B * 100.0) / 255.0);
}
