#include "CommandInterpreter.hpp"

#include <stdio.h>

#if defined(_UNIT_TESTS_)
#include <iostream>
#endif

CommandInterpreter::CommandInterpreter(UART_HandleTypeDef* pUART_Hdl)
    : m_pUART_Hdl(pUART_Hdl)
{
}

CommandInterpreter::~CommandInterpreter()
{
}

void CommandInterpreter::pollUART()
{
#if !defined(_UNIT_TESTS_)
//    static uint8_t CRLF[3] = "\r\n";

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


//typedef enum
//{
//  HAL_OK       = 0x00U,
//  HAL_ERROR    = 0x01U,
//  HAL_BUSY     = 0x02U,
//  HAL_TIMEOUT  = 0x03U
//} HAL_StatusTypeDef;


//    HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)

    uint8_t data[10];
//    HAL_StatusTypeDef status = HAL_UART_Receive(m_pUART_Hdl, data, 1, 1);

//    if (HAL_OK == status) {
//        char response = 'x';
//
//        HAL_UART_Transmit(m_pUART_Hdl, reinterpret_cast<uint8_t*>(response), 1, 100);
//        HAL_UART_Transmit(m_pUART_Hdl, CRLF, 2, 100);
//    }
#endif  // _UNIT_TESTS_
}
