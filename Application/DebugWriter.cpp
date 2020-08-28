#include "DebugWriter.hpp"

#if defined(_UNIT_TESTS_)
#include <iostream>
#endif

#include "TimerMgr.hpp"

DebugWriter::DebugWriter(UART_HandleTypeDef* pUART_Hdl, ITimerMgr* pTimerMgr)
    : m_pUART_Hdl(pUART_Hdl)
    , m_pTimerMgr(pTimerMgr)
{
}

DebugWriter::~DebugWriter()
{
}

bool DebugWriter::print(char const* pData, uint8_t len)
{
    if(255 > len) {
#if defined(_UNIT_TESTS_)
        std::cout << "Data length: " << static_cast<uint16_t>(len) << " : '" << pData << "'" << std::endl;
#else
        uint8_t CR = '\r';
        HAL_UART_Transmit(m_pUART_Hdl, reinterpret_cast<uint8_t*>(const_cast<char*>(pData)), len, 100);
        HAL_UART_Transmit(m_pUART_Hdl, &CR, 1, 100);
#endif
        return true;
    } else {
        return false;
    }
}

bool DebugWriter::print(char const* pData, uint8_t len, BCD_Time* pBCD_Time)
{
    if(255 > len) {
#if defined(_UNIT_TESTS_)
        for(uint8_t cnt = 0; cnt < BCD_Time::NR_DIGITS; cnt++) {
            std::cout << static_cast<uint8_t>(pBCD_Time->sec[cnt] + 0x30);
        }
        std::cout << " : " << pData << std::endl;
#else
        uint8_t CR = '\r';
        uint8_t separator[] = " : ";
        uint8_t val;
        for(int8_t cnt = BCD_Time::NR_DIGITS - 1; cnt >= 0; cnt--) {
            val = static_cast<uint8_t>(pBCD_Time->sec[cnt] + 0x30);
            HAL_UART_Transmit(m_pUART_Hdl, &val, 1, 100);
        }
        HAL_UART_Transmit(m_pUART_Hdl, separator, 3, 100);
        HAL_UART_Transmit(m_pUART_Hdl, reinterpret_cast<uint8_t*>(const_cast<char*>(pData)), len, 100);
        HAL_UART_Transmit(m_pUART_Hdl, &CR, 1, 100);
#endif
        return true;
    } else {
        return false;
    }
}
