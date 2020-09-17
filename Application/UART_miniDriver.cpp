#include "UART_miniDriver.hpp"


HAL_StatusTypeDef HAL_UART_Receive_rdu(UART_HandleTypeDef* huart, uint8_t* pData)
{
    uint16_t uhMask;

    __HAL_LOCK(huart);

    // Computation of UART mask to apply to RDR register
    UART_MASK_COMPUTATION(huart);
    uhMask = huart->Mask;

    if(false == __HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE)) {
        // No data ready, release lock and return
        __HAL_UNLOCK(huart);
        return HAL_TIMEOUT;
    }

    // There is a character, read it.
    *pData = (uint8_t)(huart->Instance->RDR & (uint8_t)uhMask);
    __HAL_UNLOCK(huart);

    return HAL_OK;
}


/**
 * @brief  Handle UART Communication Timeout.
 * @param huart     UART handle.
 * @param Flag      Specifies the UART flag to check
 * @param Status    Flag status (SET or RESET)
 * @retval HAL status
 */
HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout_rdu(UART_HandleTypeDef* huart, uint32_t Flag, FlagStatus Status)
{
    // Wait until flag is set (wait for ever)
    while((__HAL_UART_GET_FLAG(huart, Flag) ? SET : RESET) == Status) {
    }
    return HAL_OK;
}


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
HAL_StatusTypeDef HAL_UART_Transmit_rdu(UART_HandleTypeDef* huart, uint8_t* pData, uint16_t Size)
{
    uint8_t* pdata8bits;

    // Check that a Tx process is not already ongoing
    if(huart->gState == HAL_UART_STATE_READY) {
        __HAL_LOCK(huart);

        huart->ErrorCode = HAL_UART_ERROR_NONE;
        huart->gState = HAL_UART_STATE_BUSY_TX;

        huart->TxXferSize = Size;
        huart->TxXferCount = Size;

        pdata8bits = pData;

        while(huart->TxXferCount > 0U) {
            if(UART_WaitOnFlagUntilTimeout_rdu(huart, UART_FLAG_TXE, RESET) != HAL_OK) {
                return HAL_TIMEOUT;
            }

            huart->Instance->TDR = (uint8_t)(*pdata8bits & 0xFFU);
            pdata8bits++;

            huart->TxXferCount--;
        }

        if(UART_WaitOnFlagUntilTimeout_rdu(huart, UART_FLAG_TC, RESET) != HAL_OK) {
            return HAL_TIMEOUT;
        }

        // At end of Tx process, restore huart->gState to Ready
        huart->gState = HAL_UART_STATE_READY;

        __HAL_UNLOCK(huart);

        return HAL_OK;
    } else {
        return HAL_BUSY;
    }
}
