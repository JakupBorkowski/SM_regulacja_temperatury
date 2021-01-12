/**
  ******************************************************************************
  * @file    led.h
  * @author  AW
  * @version V1.0
  * @date    3-Oct-2020
  * @brief   Simple LED driver library.
  *
  ******************************************************************************
  */
#ifndef INC_LED_H_
#define INC_LED_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Typedef -------------------------------------------------------------------*/
#define LED_PortType GPIO_TypeDef*
#define LED_PinType uint16_t

typedef struct {
	LED_PortType Port;  //! LED GPIO port pointer
	LED_PinType Pin;	//! LED GPIO pin position
	uint8_t  Logic;     //! LED logic: 1 if LED is on when pin is high, 0 otherwise
} LED_HandleTypeDef;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Turn LED on
 * @param hled LED handle
 * @retval None
 */
void LED_On(LED_HandleTypeDef* hled);

/**
 * @brief Turn LED off
 * @param hled LED handle
 * @retval None
 */
void LED_Off(LED_HandleTypeDef* hled);

/**
 * @brief Toggle LED state
 * @param hled LED handle
 * @retval None
 */
void LED_Toggle(LED_HandleTypeDef* hled);

/**
 * @brief Set LED to selected state (SET/RESET)
 * @param hled LED handle
 * @retval None
 */
void LED_SetTo(LED_HandleTypeDef* hled, unsigned char state);

#endif /* INC_LED_H_ */
