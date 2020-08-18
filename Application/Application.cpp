/*
 * Application.cpp
 *
 *  Created on: Aug 18, 2020
 *      Author: reto
 */

#include "stm32f0xx_hal.h"
#include "main.h"
#include "Application.h"

	  //HAL_GPIO_WritePin(GPIOA, PUMP_OUT_Pin|LED_OUT_Pin, GPIO_PIN_RESET);
	  //HAL_GPIO_WritePin(GPIOA, PUMP_OUT_Pin|LED_OUT_Pin, GPIO_PIN_RESET);
void runBackgroudLoop()
{
	  HAL_GPIO_WritePin(GPIOA, LED_OUT_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA, LED_OUT_Pin, GPIO_PIN_SET);

}
