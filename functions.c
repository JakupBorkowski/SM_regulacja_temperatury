/*
 * functions.c
 *
 *  Created on: Jan 18, 2021
 *      Author: Kuba
 */

#include "functions.h"
#include "usart.h"
#include <stdio.h>
#include "tim.h"
#include "dma.h"

/**
 * @brief Procedura pobierania temperatury przez UART,
 * mozna ja zadawac za pomoca 4 cyfr, np. 2600 (26 stopni Celsjujsza)
 *
 * @param char *rx_buffer oraz wskaźnik na zmienna
 * int32_t *temperatura_zadana przechowujący pobraną temperatureę
 *
 * @retval Brak
 */
void pobieranie_temperatury_UART(char *rx_buffer, int32_t *temperatura_zadana)
{
  *temperatura_zadana=1000*(rx_buffer[0]-'0')+100*(rx_buffer[1]-'0')+10*(rx_buffer[2]-'0')+1*(rx_buffer[3]-'0');
  HAL_UART_Receive_DMA(&huart3,(uint8_t*)rx_buffer,4);
}

/**
 * @brief Procedura wysylania informacji przez  UART,
 *
 * @param char *tx_buffer oraz wskaźnik na zmienne przechowujace informacje na temat
 *  syganlu sterujacego i pomiaru
 *
 * @retval Brak
 */
void wysylanie_UART(char *tx_buffer, int32_t *temp32, int32_t *temperatura_zadana, int32_t *wzmocnienie_grzalka, int32_t *wzmocnienie_wiatrak)
{
  //int n=sprintf(tx_buffer, "temp32: %d ; temp_zad: %d ; wz_grz: %d ; wz_wiat: %d\r\n",(int)*temp32,(int)*temperatura_zadana, (int)*wzmocnienie_grzalka, (int)*wzmocnienie_wiatrak);
  int n=sprintf(tx_buffer, "temp32: %d ; temp_zad: %d\r\n",(int)*temp32,(int)*temperatura_zadana);
  //int n=sprintf(tx_buffer, "%d",(int)*temp32);
  HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, n, 100);
}

/**
 * @brief Procedura sterowania temperaturą
 *
 * @param wskaźniki na wzmocnienie wiatraka oraz grzałki
 *
 * @retval Brak
 */
void sterowanie(int32_t *wzmocnienie_grzalka, int32_t *wzmocnienie_wiatrak)
{
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,*wzmocnienie_grzalka);
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,*wzmocnienie_wiatrak);
}

/**
 * @brief Procedura regulacji temperatury
 *
 * @param wskaźniki na parametry potrzebne do regulacji temperatury, wzmocnienie wiatraka, grzalki
 * wzmocnienie, uchyb, temperatura zadana oraz referencyjna
 *
 * @retval Brak
 */
void regulacja(int32_t *wzmocnienie_grzalka, int32_t *wzmocnienie_wiatrak, uint32_t *kp, uint32_t *uchyb, int32_t *temperatura_zadana, int32_t *temp32)
{
  /* pętka regulacji temperatury */
  *uchyb=*temperatura_zadana-*temp32;
  if(*temperatura_zadana>*temp32)
  {
	*wzmocnienie_wiatrak = MIN_PWM;
	*wzmocnienie_grzalka += *kp*(*uchyb);
  }
  else if(*temperatura_zadana<*temp32)
  {
	*wzmocnienie_wiatrak += -(*kp)*(*uchyb);
	*wzmocnienie_grzalka=MIN_PWM;
  }
  if(*wzmocnienie_grzalka>MAX_PWM)
  {
	*wzmocnienie_grzalka=MAX_PWM;
  }
  else if (*wzmocnienie_grzalka<MIN_PWM)
  {
	*wzmocnienie_grzalka=MIN_PWM;
  }
  if(*wzmocnienie_wiatrak>MAX_PWM)
  {
	*wzmocnienie_wiatrak=MAX_PWM;
  }
  else if (*wzmocnienie_wiatrak<MIN_PWM)
  {
    *wzmocnienie_wiatrak=MIN_PWM;
  }
}

