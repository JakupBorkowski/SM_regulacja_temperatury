/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bmp280.h"
#include "bmp280_defs.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define BMP280_SPI (&hspi4)

#define BMP280_CS1 1
#define BMP280_CS2 2
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t acc=0;
uint8_t acc1=0;
uint8_t acc2=0;
uint8_t acc3=0;
int licznik = 0;
int32_t local_pres, local_temp;
char tx_buffer[20];
char rx_buffer[4];
uint8_t enc_counter=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int8_t bmp280_spi_reg_write(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
int8_t bmp280_spi_reg_read(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==ENC_CLK_Pin)
	{
		enc_counter=htim4.Instance->CNT;
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{
    if(huart->Instance ==USART3)
    {
	        if(rx_buffer[0]=='G')
	        {
	            acc1=rx_buffer[1]-'0';
	            acc2=rx_buffer[2]-'0';
	            acc3=rx_buffer[3]-'0';
            acc=100*acc1+10*acc2+1*acc3;
	        }
	    }
	    HAL_UART_Receive_IT(&huart3,(uint8_t*)rx_buffer,4);
	}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	struct bmp280_dev bmp280_1 ={
			.dev_id = BMP280_CS1,
			.intf = BMP280_SPI_INTF,
			.read = bmp280_spi_reg_read,
			.write = bmp280_spi_reg_write,
			.delay_ms=HAL_Delay,
	};

	struct bmp280_uncomp_data bmp280_1_data;
	int32_t temp32, temp32_2;
	double temp;
	uint32_t pres32;
	double pres;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_I2C1_Init();
  MX_SPI4_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

//Initialize BMP280 sensor
int8_t rslt;
struct bmp280_config conf;

/*Always read the current settings before writing, especially when all the configuration is modified */
rslt = bmp280_init(&bmp280_1);

/* Configuring the temperature oversampling, filter coefficient and output data rate*/
/*Overwrite the desired settings */
conf.filter = BMP280_FILTER_OFF;

/* Temperature oversampling set at 1x */
conf.os_temp=BMP280_OS_1X;

/* Temperature oversampling set at 1x */
conf.os_pres = BMP280_OS_1X;

/*Setting the output data rate as 4Hz (250ms) */
conf.odr=BMP280_ODR_250_MS;

rslt=bmp280_set_config(&conf,&bmp280_1);

/*Always set the power mode after setting the configuration*/
rslt=bmp280_set_power_mode(BMP280_NORMAL_MODE, &bmp280_1);

HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
HAL_UART_Receive_IT(&huart3, (uint8_t*)rx_buffer,4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,1000);
	 // Read BMP280 sensor measurement
	 /*Reading the raw data from sensor */
	  rslt=bmp280_get_uncomp_data(&bmp280_1_data,&bmp280_1);
	 /*Getting 32 bit compensated temperature */
	 rslt = bmp280_get_comp_temp_32bit(&temp32, bmp280_1_data.uncomp_temp, &bmp280_1);

	 /*Getting the compensated temperature as floating point value */
	 rslt = bmp280_get_comp_temp_double(&temp, bmp280_1_data.uncomp_temp, &bmp280_1);

	 /*Getting the compensated pressure using 32 bit precision */
	 rslt = bmp280_get_comp_pres_32bit(&pres32, bmp280_1_data.uncomp_press, &bmp280_1);
	 local_pres=pres32;

	 /*Getting the compensated pressure as floating point value */
	 rslt = bmp280_get_comp_pres_double(&pres, bmp280_1_data.uncomp_press, &bmp280_1);
int n = sprintf(tx_buffer, " %d;%d\r\n",licznik, temp32);
HAL_UART_Transmit(&huart3,(uint8_t*)tx_buffer,n,100);
	 /*Sleep time between measurements = BMP280_ODR_250_MS*/
	 bmp280_1.delay_ms(1000);
	 licznik=licznik+1;
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_I2C1;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
#define BMP280_SPI_BUFFER_LEN 28
#define BMP280_DATA_INDEX      1

int8_t bmp280_spi_reg_write(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	int32_t iError = BMP280_OK;
	uint8_t txarray[BMP280_SPI_BUFFER_LEN];
	uint8_t stringpos;

	txarray[0]=reg_addr;
	for (stringpos =0; stringpos<length ;stringpos++)
	{
		txarray[stringpos+BMP280_DATA_INDEX] = reg_data[stringpos];
	}

	if(cs==BMP280_CS1)
	{
		HAL_GPIO_WritePin(BMP280_CS1_GPIO_Port, BMP280_CS1_Pin,GPIO_PIN_RESET);
	}

	status=HAL_SPI_Transmit(BMP280_SPI, (uint8_t*)(&txarray),length+1, 100);
	while(BMP280_SPI->State == HAL_SPI_STATE_BUSY){};

	HAL_GPIO_WritePin(BMP280_CS1_GPIO_Port, BMP280_CS1_Pin,GPIO_PIN_SET);
	if (status != HAL_OK)
	{
		iError=(-1);
	}
	return (int8_t)iError;
}

int8_t bmp280_spi_reg_read(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	int32_t iError = BMP280_OK;
	uint8_t txarray[BMP280_SPI_BUFFER_LEN] = {0,};
	uint8_t rxarray[BMP280_SPI_BUFFER_LEN] = {0,};
	uint8_t stringpos;

	txarray[0]=reg_addr;

	if(cs==BMP280_CS1)
		{
			HAL_GPIO_WritePin(BMP280_CS1_GPIO_Port, BMP280_CS1_Pin,GPIO_PIN_RESET);
		}

	status=HAL_SPI_TransmitReceive(BMP280_SPI, (uint8_t*)(&txarray),(uint8_t*)(&rxarray),length+1, 5);
	while(BMP280_SPI->State ==HAL_SPI_STATE_BUSY) {};

	HAL_GPIO_WritePin(BMP280_CS1_GPIO_Port, BMP280_CS1_Pin,GPIO_PIN_SET);

	for (stringpos =0; stringpos <length; stringpos++)
	{
		reg_data[stringpos]=rxarray[stringpos+BMP280_DATA_INDEX];
	}

	if(status !=HAL_OK)
	{
		iError =(-1);
	}
	return (int8_t)iError;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/