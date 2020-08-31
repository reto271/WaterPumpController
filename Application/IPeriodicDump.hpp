#pragma once

#include <stdint.h>


/// \brief Periodically dumps some information on the debug channel.
class IPeriodicDump {
public:
    /// Periodically dumps an alive message on the debug terminal.
    /// \remarks Shall be called in 1s interval.
    virtual void run() = 0;
};
