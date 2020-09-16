#pragma once

#include "ICommandInterpreter.hpp"

#include <stdint.h>

#if defined(_UNIT_TESTS_)
#define UART_HandleTypeDef char
#else
#include "main.h"
#endif


// \brief Timer manager to provide 10ms, 100ms and 1s periodic timer. It further offers an interface
//  to register a custom timer in 1s resolution. The user must periodically check if the timer
//  did expire.
//
// ### Limitations ###
// - There are at most MAX_CURRENT_ACTIVE_TIMERS concurrently active. The number of timers is hard
//    coded and currently set to 10.
// - There are at most 2^32 timer handles. After this number of timers is created the handles will
//    be reused. If a single timer is created and does not expires while 2^32 other timers are created
//    and expire/canceled there will be a conflict in numbers. -> To be improved.
class CommandInterpreter : public ICommandInterpreter
{
public:
    /// Creates the command interpreter.
    /// \param[in] pUART_Hdl handle of the UART driver provided by the STM framework.
    CommandInterpreter(UART_HandleTypeDef* pUART_Hdl);

    /// Destructs the command interpreter.
    virtual ~CommandInterpreter();

    void pollUART() override;

protected:
    /// Handle to the UART, to use the stm32 lib.
    UART_HandleTypeDef* m_pUART_Hdl;
};
