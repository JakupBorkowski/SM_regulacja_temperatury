/**
  ******************************************************************************
  * @file    encoder.h
  * @author  AW 
  * @version V1.0
  * @date    30-Oct-2020
  * @brief   Simple rotary encoder driver library. 
  *
  ******************************************************************************
  */
#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

/* Config --------------------------------------------------------------------*/
//#define ENC_HARDWARE_COUNTER

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Typedef -------------------------------------------------------------------*/
#ifdef ENC_HARDWARE_COUNTER

#define ENC_TimerType TIM_HandleTypeDef*

typedef struct {
 ENC_TimerType Timer;
 uint32_t Counter;
} ENC_HandleTypeDef;


#else

#define ENC_PortType GPIO_TypeDef*
#define ENC_PinType uint16_t

typedef struct {
  ENC_PortType CLK_Port;
  ENC_PinType  CLK_Pin;
  ENC_PortType DT_Port;
  ENC_PinType  DT_Pin;
  int32_t Counter;
  int32_t CounterMax;
  int32_t CounterMin;
  int32_t CounterStep;
} ENC_HandleTypeDef;

#endif
/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
#ifdef ENC_HARDWARE_COUNTER

int32_t ENC_Init(ENC_HandleTypeDef* henc);
uint32_t ENC_GetCounter(ENC_HandleTypeDef* henc);

#else

/**
 * @brief Rotary encoder software counter update procedure
 * @param hbtn Encoder handler
 * @retval Current counter value
 */
int32_t ENC_UpdateCounter(ENC_HandleTypeDef* henc);

#endif

#endif /* INC_ENCODER_H_ */
