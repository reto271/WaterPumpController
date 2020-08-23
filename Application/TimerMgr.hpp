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

private:
    bool m_exe10msInvervall;
    bool m_exe100msInvervall;
    uint32_t m_periodCounter;
};

#endif // __TIMERMGR_HPP__
