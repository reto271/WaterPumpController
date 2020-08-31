#pragma once

#include <stdint.h>

class BCD_Time;

/// \brief Timer manager to provide 10ms, 100ms and 1s periodic timer. It further offers an interface
///  to register a custom timer in 1s resolution. The user must periodically check if the timer
///  did expire.
///
/// ### Limitations ###
/// - There are at most MAX_CURRENT_ACTIVE_TIMERS concurrently active. The number of timers is hard
///    coded and currently set to 10.
/// - There are at most 2^32 timer handles. After this number of timers is created the handles will
///    be reused. If a single timer is created and does not expires while 2^32 other timers are created
///    and expire/canceled there will be a conflict in numbers. -> To be improved.
class ITimerMgr {
public:

    /// Timer interrupt service routine, shall be registered by the interrupt handler and be called
    ///  every 10ms
    virtual void timerISR() = 0;


    /// Returns true if 10ms interval is due to be processed.
    /// \return true if 10ms expired
    virtual bool is10ms() = 0;

    /// Confirms that the 10ms interval is processed. Shall be called such that it is
    ///  not processed multiple times.
    virtual void confirm10ms() = 0;


    /// Returns true if 100ms interval is due to be processed.
    /// \return true if 100ms expired
    virtual bool is100ms() = 0;

    /// Confirms that the 100ms interval is processed. Shall be called such that it is
    ///  not processed multiple times.
    virtual void confirm100ms() = 0;


    /// Returns true if 1s interval is due to be processed.
    /// \return true if 1s expired
    virtual bool is1s() = 0;

    /// Confirms that the 1s interval is processed. Shall be called such that it is
    ///  not processed multiple times.
    virtual void confirm1s() = 0;


    /// Creates a timer
    /// \param[in] timeoutInSec the timeout until the timer expires in seconds.
    /// \return timer handle. The client needs to store the handle to cancel the timer
    ///          or check whether it expired or not.
    virtual uint32_t createTimer(const uint32_t timeoutInSec) = 0;

    /// Cancels a running timer
    /// \param[in] timerId the timer with this timer handle will be canceled. If the ID
    ///            does not, the cancel request is ignored.
    virtual void cancelTimer(const uint32_t timerId) = 0;

    /// Checks whether a timer already expired or not.
    /// \param[in] timerId the timer with this timer handle will be canceled. If the ID
    ///            does not, the cancel request is ignored.
    /// \return true if the timer already expired. In case it expired, the timer will be
    ///          cleared. Subsequent call of this function with this very same ID will
    ///          return false.
    virtual bool isTimerExpired(const uint32_t timerId) = 0;

    /// Returns the current time in seconds since boot of the program
    /// \return time in seconds since the last boot.
    virtual uint32_t getCurrentTime() = 0;

    /// Returns the current time in seconds since boot of the program in BCD format.
    /// \return Reference to the time object in BCD format.
    virtual BCD_Time* getBCD_Time() = 0;

    /// Invalid timer handle. It is recommended to initialize all timer handle variables
    ///  to this value if not used.
    static const uint32_t INVALID_TIMER_ID = UINT32_MAX;
};
