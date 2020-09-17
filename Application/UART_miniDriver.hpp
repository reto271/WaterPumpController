#pragma once

#if defined(_UNIT_TESTS_)
#define UART_HandleTypeDef char
#define HAL_StatusTypeDef char
#define FlagStatus char
#else
#include "main.h"
#endif


/**
 * @brief Receive an amount of data in blocking mode.
 * @note   When UART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
 *         the received data is handled as a set of u16. In this case, Size must indicate the number
 *         of u16 available through pData.
 * @note   When UART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
 *         address of user data buffer for storing data to be received, should be aligned on a half word frontier (16 bits)
 *         (as received data will be handled using u16 pointer cast). Depending on compilation chain,
 *         use of specific alignment compilation directives or pragmas might be required to ensure proper alignment for pData.
 * @param huart   UART handle.
 * @param pData   Pointer to data buffer (u8 or u16 data elements).
 * @param Size    Amount of data elements (u8 or u16) to be received.
 * @param Timeout Timeout duration.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_UART_Receive_rdu(UART_HandleTypeDef* huart, uint8_t* pData);


/**
 * @brief  Handle UART Communication Timeout.
 * @param huart     UART handle.
 * @param Flag      Specifies the UART flag to check
 * @param Status    Flag status (SET or RESET)
 * @retval HAL status
 */
HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout_rdu(UART_HandleTypeDef* huart, uint32_t Flag, FlagStatus Status);


/**
 * @brief Send an amount of data in blocking mode.
 * @note   When UART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
 *         the sent data is handled as a set of u16. In this case, Size must indicate the number
 *         of u16 provided through pData.
 * @note   When UART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
 *         address of user data buffer containing data to be sent, should be aligned on a half word frontier (16 bits)
 *         (as sent data will be handled using u16 pointer cast). Depending on compilation chain,
 *         use of specific alignment compilation directives or pragmas might be required to ensure proper alignment for pData.
 * @param huart   UART handle.
 * @param pData   Pointer to data buffer (u8 or u16 data elements).
 * @param Size    Amount of data elements (u8 or u16) to be sent.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_UART_Transmit_rdu(UART_HandleTypeDef* huart, uint8_t* pData, uint16_t Size);
