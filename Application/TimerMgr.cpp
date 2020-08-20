#include "TimerMgr.hpp"

TimerMgr::TimerMgr()
    : m_exe10msInvervall(false)
    , m_exe100msInvervall(false)
    , m_periodCounter(0)
{
}

TimerMgr::~TimerMgr()
{

}

void TimerMgr::timerISR()
{
    // Check that the previous intervall was properly handled.
//    assert(false === m_exe10msInvervall);
    m_exe10msInvervall = true;
    if(10 <= m_periodCounter) {
        m_periodCounter = 0;
//        assert(false === m_exe100msInvervall);
        m_exe100msInvervall = true;
    }
    m_periodCounter++;
}

bool TimerMgr::is10ms()
{
    return m_exe10msInvervall;
}

void TimerMgr::confirm10ms()
{
    m_exe10msInvervall = false;
}

bool TimerMgr::is100ms()
{
    return m_exe100msInvervall;
}

void TimerMgr::confirm100ms()
{
    m_exe100msInvervall = false;
}
