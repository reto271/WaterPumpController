#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f0xx_hal.h>

void initializeBackgroundLoop(UART_HandleTypeDef* huart1);
void ApplicationTimerInterrupt10ms();
void runBackgroudLoop();

#ifdef __cplusplus
}
#endif

#endif // __APPLICATION_HPP__
