#pragma once

#include "ICommandInterpreter.hpp"

#include <stdint.h>

#if defined(_UNIT_TESTS_)
#define UART_HandleTypeDef char
#else
#include "main.h"
#endif

class IPeriodicDump;

// \brief xxx
class CommandInterpreter : public ICommandInterpreter
{
public:
    /// Creates the command interpreter.
    /// \param[in] pUART_Hdl handle of the UART driver provided by the STM framework.
    CommandInterpreter(UART_HandleTypeDef* pUART_Hdl, IPeriodicDump* pPeriodicDump);

    /// Destructs the command interpreter.
    virtual ~CommandInterpreter();

    void pollUART() override;

protected:
    /// Handle to the UART, to use the stm32 lib.
    UART_HandleTypeDef* m_pUART_Hdl;
    IPeriodicDump* m_pPeriodicDump;
};
