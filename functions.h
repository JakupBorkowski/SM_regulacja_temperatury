/*
 * functions.h
 *
 *  Created on: Jan 18, 2021
 *      Author: Kuba
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_
#define MAX_PWM 1000
#define MIN_PWM 0
#include <stdio.h>
//pobieranie temperatury przez uart od uzytkownika
void pobieranie_temperatury_UART(char *rx_buffer, uint32_t *acc1, uint32_t *acc2, uint32_t *acc3, uint32_t *acc4, int32_t *temperatura_zadana);

//wysylanie wiadomosci po UART
void wysylanie_UART(char *tx_buffer, int32_t *temp32, int32_t *temperatura_zadana, int32_t *wzmocnienie_grzalka, int32_t *wzmocnienie_wiatrak);

//sterowanie kanalami PWM przy regulacji temperatury
void sterowanie(int32_t *wzmocnienie_grzalka, int32_t *wzmocnienie_wiatrak);

//regulacja temperatury w ukladze
void regulacja(int32_t *wzmocnienie_grzalka, int32_t *wzmocnienie_wiatrak, uint32_t *kp, uint32_t *uchyb, int32_t *temperatura_zadana, int32_t *temp32);






#endif /* INC_FUNCTIONS_H_ */
