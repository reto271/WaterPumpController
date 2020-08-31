#pragma once

#include <stdint.h>

class IIOHandler;
class ITimerMgr;
class IDebugWriter;

/// Core functionality of the 'Water Pump Controller' software. It reads the inputs and
///  sets the states of the pump.
///
/// @startuml
/// [*] --> OFF
/// @enduml
class PumpController {
public:
    PumpController(IIOHandler* pIOHandler, ITimerMgr* pTimerMgr, IDebugWriter* pDebugWriter);
    virtual ~PumpController();

    void run();

private:
    enum class PumpState {
        On,
        Off,
        OffTimeout,
    };

    PumpController();

    void onEnterState_On();
    void onEnterState_Off();
    void onEnterState_OffTimeout();

    void state_On();
    void state_Off();
    void state_OffTimeout();

    IIOHandler* m_pIOHandler;
    ITimerMgr* m_pTimerMgr;
    IDebugWriter* m_pDebugWriter;

    PumpState m_pumpState;
    uint32_t m_timerId;

    static const uint32_t MAX_PUMP_RUN_TIME = 10 * 60;  // s, namely 10min
    static const uint32_t MIN_PUMP_IDLE_TIME = 24 * 3600;  // s, namely 24h
};
