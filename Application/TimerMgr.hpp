#pragma once

#include <stdint.h>

#include "ITimerMgr.hpp"
#include "BCD_Time.hpp"

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
class TimerMgr : public ITimerMgr {
public:
    /// Creates the timer manager.
    TimerMgr();

    /// Destructs the timer manager.
    virtual ~TimerMgr();

    void timerISR() override;

    bool is10ms() override;
    void confirm10ms() override;

    bool is100ms() override;
    void confirm100ms() override;

    bool is1s() override;
    void confirm1s() override;

    uint32_t createTimer(const uint32_t timeoutInSec) override;
    void cancelTimer(const uint32_t timerId) override;
    bool isTimerExpired(const uint32_t timerId) override;

    uint32_t getCurrentTime() override;
    BCD_Time* getBCD_Time() override;

    static const uint32_t INVALID_TIMER_ID = UINT32_MAX;

protected:
    /// Returns the next available timer Id. It cares about the wrap
    ///  and whether the ID is already in use.
    /// \return available timer ID
    uint32_t getAvailableTimerId();

    /// Returns a free position in the timer array.
    /// \param[out] freePos in the timer array.
    /// \returns false if all timers are in use.
    bool freePositionInArray(uint32_t& freePos);



#if defined (_UNIT_TESTS_)
protected:
#else
private:
#endif
    /// Function is for testing only.
    /// Sets the ID do check that an ID in use is not taken again.
    /// \param[in] id used the create the last timer
    void setLastAssignedId(uint32_t id);

private:
    /// True if the 10ms interval timer is ready to be processed.
    bool m_exe10msInterval;

    /// True if the 100ms interval timer is ready to be processed.
    bool m_exe100msInterval;

    /// True if the 1s interval timer is ready to be processed.
    bool m_exe1sInterval;

    /// Counts the number of 10ms intervals. If the count reaches 10
    ///  the 100ms m_exe100msInterval is set to true.
    uint32_t m_periodCounter10ms;

    /// Counts the number of 100ms intervals. If the count reaches 10
    ///  the 100ms m_exe1sInterval is set to true.
    uint32_t m_periodCounter100ms;

    /// Current time in seconds since startup
    uint32_t m_currentTime;

    /// Current time in seconds since startup in BCD encoding.
    BCD_Time m_bcdTime;

    /// Internal struct for a timer
    typedef struct {
        /// ID of the timer, is INVALID_TIMER_ID if the timer is currently not in use
        uint32_t timerId;
        /// Time the timer will expire. Is compared with m_currentTime.
        uint32_t timeItExpires;

    } TimerData;

    /// Maximum number of concurrently active timers
    static const uint32_t MAX_CURRENT_ACTIVE_TIMERS = 10;

    /// Last assigned timer ID, base to evaluate the next available ID.
    uint32_t m_lastAssignedTimerId;

    /// Array of timers. Entries not in use will have timerId equal to INVALID_TIMER_ID
    TimerData m_activeTimer[MAX_CURRENT_ACTIVE_TIMERS];
};
