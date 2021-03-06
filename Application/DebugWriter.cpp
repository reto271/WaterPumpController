#include "DebugWriter.hpp"

#if defined(_UNIT_TESTS_)
#include <iostream>
#endif

#include "TimerMgr.hpp"
#include "UART_miniDriver.hpp"

#if !defined(_UNIT_TESTS_)
static uint8_t CRLF[3] = "\r\n";
#endif

DebugWriter::DebugWriter(UART_HandleTypeDef* pUART_Hdl, ITimerMgr* pTimerMgr)
    : m_pUART_Hdl(pUART_Hdl)
    , m_pTimerMgr(pTimerMgr)
{
}

DebugWriter::~DebugWriter()
{
}

void DebugWriter::print(char const* pData)
{
    uint8_t len = getStringLen(pData);
#if defined(_UNIT_TESTS_)
    std::cout << "Data length: " << static_cast<uint16_t>(len) << " : '" << pData << "'" << std::endl;
#else
    HAL_UART_Transmit_rdu(m_pUART_Hdl, reinterpret_cast<uint8_t*>(const_cast<char*>(pData)), len);
    HAL_UART_Transmit_rdu(m_pUART_Hdl, CRLF, 2);
#endif
}

void DebugWriter::print(char const* pData, BCD_Time* pBCD_Time)
{
#if defined(_UNIT_TESTS_)
    for(uint8_t cnt = 0; cnt < BCD_Time::NR_DIGITS; cnt++) {
        std::cout << static_cast<uint8_t>(pBCD_Time->sec[cnt] + 0x30);
    }
    std::cout << " : " << pData << std::endl;
#else
    uint8_t separator[] = " : ";
    uint8_t val;
    for(int8_t cnt = BCD_Time::NR_DIGITS - 1; cnt >= 0; cnt--) {
        val = static_cast<uint8_t>(pBCD_Time->sec[cnt] + 0x30);
        HAL_UART_Transmit_rdu(m_pUART_Hdl, &val, 1);
    }
    HAL_UART_Transmit_rdu(m_pUART_Hdl, separator, 3);
    HAL_UART_Transmit_rdu(m_pUART_Hdl, reinterpret_cast<uint8_t*>(const_cast<char*>(pData)), getStringLen(pData));
    HAL_UART_Transmit_rdu(m_pUART_Hdl, CRLF, 2);
#endif
}

uint8_t DebugWriter::getStringLen(char const* pData)
{
    uint8_t len = 0;
    for(; ((len < MAX_STRING_LENGTH) && (0 != pData[len])); len++) {
    }
    return len;
}
