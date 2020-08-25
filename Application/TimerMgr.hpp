#ifndef __TIMERMGR_HPP__
#define __TIMERMGR_HPP__

#include <stdint.h>

class TimerMgr {
public:
    TimerMgr();
    virtual ~TimerMgr();

    void timerISR();

    bool is10ms();
    void confirm10ms();

    bool is100ms();
    void confirm100ms();

    uint32_t createTimer(const uint32_t timeoutInSec);
    void cancelTimer(const uint32_t timerId);
    bool isTimerExpired(const uint32_t timerId);

    static const uint32_t INVALID_TIMER_ID = UINT32_MAX;

protected:
    void incrementTimerId();
    uint32_t getCurrentTime();
    bool freePositionInArray(uint32_t& freePos);

private:
    bool m_exe10msInvervall;
    bool m_exe100msInvervall;
    uint32_t m_periodCounter10ms;
    uint32_t m_periodCounter100ms;

    uint32_t m_currentTime;

    typedef struct {
        uint32_t timerId;
        uint32_t timeItExpires;
    } TimerData;
    static const uint32_t MAX_CURRENT_ACTIVE_TIMERS = 10;

    uint32_t m_nextFreeTimerId;
    TimerData m_activeTimer[MAX_CURRENT_ACTIVE_TIMERS];

};

#endif // __TIMERMGR_HPP__
