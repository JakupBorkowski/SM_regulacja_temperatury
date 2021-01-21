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
/**
 * @brief Procedura pobierania temperatury przez UART,
 * mozna ja zadawac za pomoca 4 cyfr, np. 2600 (26 stopni Celsjujsza)
 *
 * @param char *rx_buffer oraz wskaźnik na zmienna
 * int32_t *temperatura_zadana przechowujący pobraną temperatureę
 *
 * @retval Brak
 */
void pobieranie_temperatury_UART(char *rx_buffer, int32_t *temperatura_zadana);

/**
 * @brief Procedura wysylania informacji przez  UART,
 *
 * @param char *tx_buffer oraz wskaźnik na zmienne przechowujace informacje na temat
 *  syganlu sterujacego i pomiaru
 *
 * @retval Brak
 */
void wysylanie_UART(char *tx_buffer, int32_t *temp32, int32_t *temperatura_zadana, int32_t *wzmocnienie_grzalka, int32_t *wzmocnienie_wiatrak);

/**
 * @brief Procedura sterowania temperaturą
 *
 * @param wskaźniki na wzmocnienie wiatraka oraz grzałki
 *
 * @retval Brak
 */
void sterowanie(int32_t *wzmocnienie_grzalka, int32_t *wzmocnienie_wiatrak);

/**
 * @brief Procedura regulacji temperatury
 *
 * @param wskaźniki na parametry potrzebne do regulacji temperatury, wzmocnienie wiatraka, grzalki
 * wzmocnienie, uchyb, temperatura zadana oraz referencyjna
 *
 * @retval Brak
 */
void regulacja(int32_t *wzmocnienie_grzalka, int32_t *wzmocnienie_wiatrak, uint32_t *kp, uint32_t *uchyb, int32_t *temperatura_zadana, int32_t *temp32);






#endif /* INC_FUNCTIONS_H_ */
