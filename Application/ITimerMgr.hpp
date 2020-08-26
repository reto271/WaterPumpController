#pragma once

#include <stdint.h>

class ITimerMgr {
public:
    virtual void timerISR() = 0;

    virtual bool is10ms() = 0;
    virtual void confirm10ms() = 0;

    virtual bool is100ms() = 0;
    virtual void confirm100ms() = 0;

    virtual uint32_t createTimer(const uint32_t timeoutInSec) = 0;
    virtual void cancelTimer(const uint32_t timerId) = 0;
    virtual bool isTimerExpired(const uint32_t timerId) = 0;

    static const uint32_t INVALID_TIMER_ID = UINT32_MAX;
};
