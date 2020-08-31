#pragma once

#include "IDebugWriter.hpp"

#if defined(_UNIT_TESTS_)
#define UART_HandleTypeDef char
#else
#include "main.h"
#endif

#include <stdint.h>

class ITimerMgr;

/// \brief Very primitive replacement for the stdio printf implementation.
/// There is very little FLASH memory on the used uP. The persistent memory
///  is not sufficiently large to link stdio lib. This class implements a
///  very simple and slim printf implementation
/// \remark The characters are printed in busy waiting.
class DebugWriter : public IDebugWriter
{
public:
    /// Constructs the debug writer.
    /// \param[in] pUART_Hdl handle of the UART driver provided by the STM framework.
    /// \param[in] pTimerMgr pointer to the timer manager. Used to get the current time
    DebugWriter(UART_HandleTypeDef* pUART_Hdl, ITimerMgr* pTimerMgr);

    /// Destructor
    virtual ~DebugWriter();

    bool print(char const* pData, uint8_t len) override;
    bool print(char const* pData, uint8_t len, BCD_Time* pBCD_Time) override;

private:
    /// Handle to the UART. (STM lib)
    UART_HandleTypeDef* m_pUART_Hdl;

    /// Reference to the timer manager. Used to print the application run time
    ///  since startup.
    ITimerMgr* m_pTimerMgr;
};
