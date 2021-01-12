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
  
/* Includes ------------------------------------------------------------------*/
#include "dimmer.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/
#define LAMP_LINE_FREQ 50ul // [Hz]

/* Macro ---------------------------------------------------------------------*/

//! For timer with base frequency (ARR = 0) of 1 MHz (period of 1 us)
#define __LAMP_DEG_TO_MICROSECONDS(A) ((1000000ul*A)/(2ul*LAMP_LINE_FREQ*180ul))

//! Simple software delay
#define __LAMP_SOFT_DELAY(N) for(uint32_t i = 0; i < N; i++){ asm("nop"); }

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/
/**
 * @brief Start lamp control timer.
 * @param hlamp Lamp handler
 * @param ang Triac firing angle [degrees]
 * @retval None
 */
void LAMP_StartTimer(LAMP_HandleTypeDef* hlamp, float ang)
{
  if(ang > hlamp->TriacFiringAngleMax)
    ang = hlamp->TriacFiringAngleMax;
  else if(ang < hlamp->TriacFiringAngleMin)
    ang = hlamp->TriacFiringAngleMin;
  
  hlamp->TriacFiringAngle = ang; 
  
  uint32_t TIM_Counter = __LAMP_DEG_TO_MICROSECONDS(hlamp->TriacFiringAngle);

  __HAL_TIM_SetAutoreload(hlamp->Timer, TIM_Counter);
  HAL_TIM_Base_Start_IT(hlamp->Timer);
}

/**
 * @brief Stop lamp control timer.
 * @param hlamp Lamp handler
 * @retval None
 */
void LAMP_StopTimer(LAMP_HandleTypeDef* hlamp)
{
  HAL_TIM_Base_Stop_IT(hlamp->Timer);
}

/**
 * @brief Triac firing procedure: set triac output on high for short period (<100us)
 * @param hlamp Lamp handler
 * @retval None
 */
void LAMP_TriacFiring(LAMP_HandleTypeDef* hlamp)
{
    HAL_GPIO_WritePin(hlamp->TRIAC_Port, hlamp->TRIAC_Pin, GPIO_PIN_SET);
    __LAMP_SOFT_DELAY(1000);
    HAL_GPIO_WritePin(hlamp->TRIAC_Port, hlamp->TRIAC_Pin, GPIO_PIN_RESET);
}