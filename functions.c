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

void pobieranie_temperatury_UART(char *rx_buffer, uint32_t *acc1, uint32_t *acc2, uint32_t *acc3, uint32_t *acc4, int32_t *temperatura_zadana)
{

		       *acc1=rx_buffer[0]-'0';
		       *acc2=rx_buffer[1]-'0';
		       *acc3=rx_buffer[2]-'0';
		       *acc4=rx_buffer[3]-'0';
	           *temperatura_zadana=1000*(*acc1)+100*(*acc2)+10*(*acc3)+1*(*acc4);

		        HAL_UART_Receive_DMA(&huart3,(uint8_t*)rx_buffer,4);

}

void wysylanie_UART(char *tx_buffer, int32_t *temp32, int32_t *temperatura_zadana, int32_t *wzmocnienie_grzalka, int32_t *wzmocnienie_wiatrak)
{
	//int n=sprintf(tx_buffer, "temp32: %d ; temp_zad: %d ; wz_grz: %d ; wz_wiat: %d\r\n",(int)*temp32,(int)*temperatura_zadana, (int)*wzmocnienie_grzalka, (int)*wzmocnienie_wiatrak);
	int n=sprintf(tx_buffer, "temp32: %d ; temp_zad: %d\r\n",(int)*temp32,(int)*temperatura_zadana);
	//int n=sprintf(tx_buffer, "%d",(int)*temp32);
	HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, n, 100);
}

void sterowanie(int32_t *wzmocnienie_grzalka, int32_t *wzmocnienie_wiatrak)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,*wzmocnienie_grzalka);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,*wzmocnienie_wiatrak);

}

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

