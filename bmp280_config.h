/**
  ******************************************************************************
  * @file    bmp280_config.h
  * @author  AW
  * @version V1.0
  * @date    15-Nov-2020
  * @brief   Configuration file for BMP280 sensor driver library: 
  *          SPI routines implementation
  *
  ******************************************************************************
  */
#ifndef INC_BMP280_CONFIG_H_
#define INC_BMP280_CONFIG_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "bmp280.h"
#include "bmp280_defs.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/
#define BMP280_SPI (&hspi4)

#define BMP280_CS1 1
#define BMP280_CS2 2

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern struct bmp280_dev bmp280_1;
extern struct bmp280_dev bmp280_2;

/* Public function prototypes ------------------------------------------------*/

/*!
 *  @brief Initialization function
 *
 *  @param[in] bmp        : BMP280 device structure
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t BMP280_Init(struct bmp280_dev* bmp);

/*!
 *  @brief Function for writing the sensor's registers through SPI bus.
 *
 *  @param[in] cs           : Chip select to enable the sensor.
 *  @param[in] reg_addr     : Register address.
 *  @param[in] reg_data     : Pointer to the data buffer whose data has to be written.
 *  @param[in] length       : No of bytes to write.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t bmp280_spi_reg_write(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);

/*!
 *  @brief Function for reading the sensor's registers through SPI bus.
 *
 *  @param[in] cs       : Chip select to enable the sensor.
 *  @param[in] reg_addr : Register address.
 *  @param[out] reg_data    : Pointer to the data buffer to store the read data.
 *  @param[in] length   : No of bytes to read.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t bmp280_spi_reg_read(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);

#endif /* INC_BMP280_CONFIG_H_ */
