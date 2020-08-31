#pragma once

#include <stdint.h>

class IIOHandler;
class ITimerMgr;
class IDebugWriter;

/// \brief Core functionality of the 'Water Pump Controller' software. It reads the inputs and
///  sets the states of the pump.
///
/// Reads the input, if both levels are on, the pump is switched on. If both levels are off the
///  pump is switched off. There is a maximum run time, if the time is exceeded the pump is
///  switched off independent of the level detection. There is also a minimum idle time. The
///  minimum idle time starts if the pump is switched off. The pump may no be enabled before
///  this minimum idle time expired.
///
/// @startuml
/// [*] --> OFF        : Initialization
/// OFF --> ON         : Low and high level on
/// ON --> OFF_TIMEOUT : (Low and high level off) OR \n (Maximum run time expired)
/// OFF_TIMEOUT -> OFF : Minimum idle time expired
/// @enduml
class PumpController {
public:
    /// Creates the pump controller
    /// \param[in] pIOHandler reference to the IO handler, to get input states and set
    ///             the pump and LED state
    /// \param[in] pTimerMgr reference to timer manager to create the necessary timers
    /// \param[in] pDebugWriter reference to the debug writer, to dump state changes
    PumpController(IIOHandler* pIOHandler, ITimerMgr* pTimerMgr, IDebugWriter* pDebugWriter);

    /// Destructor of the pump controller
    virtual ~PumpController();

    /// Runs the pump controller.
    /// \remark Shall be called every 100ms
    void run();

private:
    /// States of the pump controller
    enum class PumpState {
        /// Pump state is on, maximum run time timer is on.
        On,
        /// Pump state is off, it is ready to switch on.
        Off,
        /// Pump state is off, the min idle timer is still running. The pump remains off
        ///  independent of the level detection.
        OffTimeout,
    };

    /// The pump controller shall not be created without the necessary references to
    /// IO handler, timer manager and debug writer
    PumpController();

    /// Enters the state on and starts the maximum run-time timer.
    void onEnterState_On();
    /// Enters the state off.
    void onEnterState_Off();
    /// Enters the state off-timeout and starts the minimum idle timer.
    void onEnterState_OffTimeout();

    /// Checks if both levels get off, to switch of the pump and checks
    ///  the maximum run-time timer.
    void state_On();
    /// Pump is off, wait until both levels get on.
    void state_Off();
    /// Idle timer is running, wait until is expired to eventually switch on again.
    void state_OffTimeout();


    /// Reference to the IO handler, to get input states and set
    ///             the pump and LED state
    IIOHandler* m_pIOHandler;

    /// Reference to timer manager to create the necessary timers
    ITimerMgr* m_pTimerMgr;

    /// Reference to the debug writer, to dump state changes
    IDebugWriter* m_pDebugWriter;

    /// Internal state of the pump controller.
    PumpState m_pumpState;

    /// Id if the currently active timer.
    uint32_t m_timerId;

    /// Maximum pump run time in s, currently 10min
    static const uint32_t MAX_PUMP_RUN_TIME = 10 * 60;

    /// Minimum pump idle time in s, currently 24h
    static const uint32_t MIN_PUMP_IDLE_TIME = 24 * 3600;
};
