#pragma once

#include <stdint.h>

class PumpController;


/// \brief Periodically dumps some information on the debug channel.
class IPeriodicDump {
public:
    /// Periodically dumps an alive message on the debug terminal.
    /// \remarks Shall be called in 1s interval.
    virtual void run() = 0;

    /// Dumps the state and inputs on request.
    virtual void dumpInfo() = 0;

    /// Set reference to the pump controller, used to dump its state.
    /// \param[in] pPumpCtrl reference to the pump controller.
    virtual void setPumpController(PumpController* pPumpCtrl) = 0;
};
