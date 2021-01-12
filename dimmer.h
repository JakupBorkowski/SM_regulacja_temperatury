/**
  ******************************************************************************
  * @file    dimmer.c
  * @author  AW
  * @version V1.0
  * @date    30-Oct-20202
  * @brief   Simple dimmer (lamp control board) driver library.
  *
  ******************************************************************************
  */
#ifndef INC_DIMMER_H_
#define INC_DIMMER_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Typedef -------------------------------------------------------------------*/
#define LAMP_TimerType TIM_HandleTypeDef*
#define LAMP_PortType GPIO_TypeDef*
#define LAMP_PinType uint16_t

typedef struct {
  LAMP_TimerType Timer;
  LAMP_PortType SYNC_Port;
  LAMP_PinType SYNC_Pin;
  LAMP_PortType TRIAC_Port;
  LAMP_PinType TRIAC_Pin;
  float TriacFiringAngle;
  float TriacFiringAngleMin;
  float TriacFiringAngleMax;
} LAMP_HandleTypeDef; 

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Start lamp control timer.
 * @param hlamp Lamp handler
 * @param ang Triac firing angle [degrees]
 * @retval None
 */
void LAMP_StartTimer(LAMP_HandleTypeDef* hlamp, float ang);

/**
 * @brief Stop lamp control timer.
 * @param hlamp Lamp handler
 * @retval None
 */
void LAMP_StopTimer(LAMP_HandleTypeDef* hlamp);

/**
 * @brief Triac firing procedure: set triac output on high for short period (<100us)
 * @param hlamp Lamp handler
 * @retval None
 */
void LAMP_TriacFiring(LAMP_HandleTypeDef* hlamp);

#endif /* INC_DIMMER_H_ */
