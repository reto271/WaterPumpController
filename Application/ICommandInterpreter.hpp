#pragma once

#include <stdint.h>

/// Reads characters from the UART, identifies commands and triggers the defined action.
class ICommandInterpreter {
public:
    /// Polls the UART for new data. In case there is a 'd' received the current
    ///  state is dumped.
    virtual void pollUART() = 0;
};
