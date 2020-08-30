#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f0xx_hal.h>

/// Main application
/// The main application consists of a single task. It is the background loop of the
///  application. It will be interrupted by a 10ms interrupt, to control the timing


/// Initializes the background loop.
/// \param[in] pUART_Hdl pointer to the UART handler offered by the STM driver.
void initializeBackgroundLoop(UART_HandleTypeDef* pUART_Hdl);

/// 'ISR' shall be called every 10ms by a timer interrupt.
void ApplicationTimerInterrupt10ms();

/// The background loop. It is an endless loop. It mainly checks the timers/timing and
///  calls the necessary functions at the required time. (IO-Handler, Pump Controller
///  and periodic dump of information.)
void runBackgroudLoop();

#ifdef __cplusplus
}
#endif
