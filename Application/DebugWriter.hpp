#pragma once

#include "IDebugWriter.hpp"

#if defined(_UNIT_TESTS_)
#define UART_HandleTypeDef char
#else
#include "main.h"
#endif

#include <stdint.h>

class ITimerMgr;

class DebugWriter : public IDebugWriter
{
public:
    DebugWriter(UART_HandleTypeDef* pUART_Hdl, ITimerMgr* pTimerMgr);
    virtual ~DebugWriter();

    bool print(char const* pData, uint8_t len) override;
    bool print(char const* pData, uint8_t len, BCD_Time* pBCD_Time) override;

private:
    UART_HandleTypeDef* m_pUART_Hdl;
    ITimerMgr* m_pTimerMgr;
};
