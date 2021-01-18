/**
  ******************************************************************************
  * @file    components.h
  * @author  AW 
  * @version V1.0
  * @date     
  * @brief   Components drivers and configuration files.
  *
  ******************************************************************************
  */
#ifndef INC_COMPONENTS_H_
#define INC_COMPONENTS_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/

//! LED
#include "led.h"
#include "led_config.h"

//! Push-buttons
#include "btn.h"
#include "btn_config.h"

//! Rotary encoder
#include "encoder.h"
#include "encoder_config.h"

//! Dimmer board
#include "dimmer.h"
#include "dimmer_config.h"

//! LED PWM
#include "led_pwm.h"
#include "led_pwm_config.h"

//! LED RGB
#include "led_rgb.h"
#include "led_rgb_config.h"

//! HD44780 LCD
#include "lcd_i2c.h"


//! HEATER PWM
#include "heater_pwm.h"
#include "heater_pwm_config.h"

//! BH1750 Digital light sensor
#include "bh1750.h"
#include "bh1750_config.h"

//! dodatkowe funkcje
#include "functions.h"


//! BMP280 Digital pressure and temperature sensor
//! https://github.com/BoschSensortec/BMP280_driver
#include "bmp280.h"
#include "bmp280_defs.h"
#include "bmp280_config.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

#endif /* INC_COMPONENTS_H_ */
