#pragma once

#include <stdint.h>

class IIOHandler;
class ITimerMgr;

class PumpController {
public:
    PumpController(IIOHandler* pIOHandler, ITimerMgr* pTimerMgr);
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

    PumpState m_pumpState;
    uint32_t m_timerId;

    static const uint32_t MAX_PUMP_RUN_TIME = 120;  // s, namely 2min
    static const uint32_t MIN_PUMP_IDLE_TIME = 3600;  // s, namely 1h
};
