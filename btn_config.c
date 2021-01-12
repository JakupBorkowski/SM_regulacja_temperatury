/**
  ******************************************************************************
  * @file    btn_config.c
  * @author  AW
  * @version V1.0
  * @date    30-Oct-2020
  * @brief   Simple push button driver library configuration file.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "btn.h"
#include "btn_config.h"
#include "main.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
BTN_HandleTypeDef hbtn1 = {
  .Port = EX1_Btn_GPIO_Port, .Pin = EX1_Btn_Pin,
  .Edge = FALLING_EDGE, .State = GPIO_PIN_SET
};

BTN_HandleTypeDef hbtn2 = {
  .Port = EX2_Btn_GPIO_Port, .Pin = EX2_Btn_Pin,
  .Edge = RISING_EDGE, .State = GPIO_PIN_RESET
};

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/
