#pragma once

#include "ICommandInterpreter.hpp"

#include <stdint.h>

#if defined(_UNIT_TESTS_)
#define UART_HandleTypeDef char
#else
#include "main.h"
#endif

class IPeriodicDump;

/// \brief Reads and processes commands
/// Reads characters from the UART, identifies commands and triggers the defined action.
class CommandInterpreter : public ICommandInterpreter
{
public:
    /// Creates the command interpreter.
    /// \param[in] pUART_Hdl handle of the UART driver provided by the STM framework.
    /// \param[in] pPeriodicDump Used to dump the state on demand. The dump state function is
    ///             implemented by the periodic dump class.
    CommandInterpreter(UART_HandleTypeDef* pUART_Hdl, IPeriodicDump* pPeriodicDump);

    /// Destructs the command interpreter.
    virtual ~CommandInterpreter();

    void pollUART() override;

protected:
    /// Handle to the UART, to use the stm32 lib.
    UART_HandleTypeDef* m_pUART_Hdl;

    /// Reference to dump the current state of the application.
    IPeriodicDump* m_pPeriodicDump;
};
