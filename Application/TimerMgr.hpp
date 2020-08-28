#ifndef __TIMERMGR_HPP__
#define __TIMERMGR_HPP__

#include <stdint.h>

#include "ITimerMgr.hpp"

class TimerMgr : public ITimerMgr {
public:
    TimerMgr();
    virtual ~TimerMgr();

    void timerISR() override;

    bool is10ms() override;
    void confirm10ms() override;

    bool is100ms() override;
    void confirm100ms() override;

    uint32_t createTimer(const uint32_t timeoutInSec) override;
    void cancelTimer(const uint32_t timerId) override;
    bool isTimerExpired(const uint32_t timerId) override;

    uint32_t getCurrentTime() override;

    static const uint32_t INVALID_TIMER_ID = UINT32_MAX;

protected:
    void incrementTimerId();
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
