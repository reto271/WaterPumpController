#include "TimerMgr.hpp"

#include <stdio.h>

#if defined(_UNIT_TESTS_)
#include <iostream>
#endif


/// Limitations:
/// - Reuse of timers if 2^32 is expired is limited. Namely if a timer is created, never expires, meanwhile 2^32 timers are created and expire. Then there is a timer ID allocation issue.
/// - At most 10 timers may be active at the same time


const uint32_t TimerMgr::INVALID_TIMER_ID;  // Initialized in the header, necessary for the linker

TimerMgr::TimerMgr()
    : m_exe10msInvervall(false)
    , m_exe100msInvervall(false)
    , m_periodCounter10ms(1)
    , m_periodCounter100ms(1)
    , m_currentTime(0)
    , m_nextFreeTimerId(0)
{
    for(uint32_t cnt = 0; cnt < MAX_CURRENT_ACTIVE_TIMERS; cnt++) {
        m_activeTimer[cnt].timerId = INVALID_TIMER_ID;
        m_activeTimer[cnt].timeItExpires = 0;
    }
}

TimerMgr::~TimerMgr()
{
}

void TimerMgr::timerISR()
{
    // Check that the previous interval was properly handled.
//    assert(false === m_exe10msInvervall);
    m_exe10msInvervall = true;
    if(10 <= m_periodCounter10ms) {
        m_periodCounter10ms = 0;
//        assert(false === m_exe100msInvervall);
        m_exe100msInvervall = true;
        if(10 <= m_periodCounter100ms) {
            m_periodCounter100ms = 0;
            m_currentTime++;
            m_bcdTime.incrementSecond();
        }
        m_periodCounter100ms++;
    }
    m_periodCounter10ms++;
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

uint32_t TimerMgr::createTimer(const uint32_t timeoutInSec)
{
    uint32_t newTimerId = m_nextFreeTimerId;
    uint32_t newTimerPos = INVALID_TIMER_ID;
    if(true == freePositionInArray(newTimerPos)) {
        // assert(INVALID_TIMER_ID == m_activeTimer[m_nextFreeTimerId].timerId);
        m_activeTimer[newTimerPos].timerId = newTimerId;
        m_activeTimer[newTimerPos].timeItExpires = m_currentTime + timeoutInSec;
#if defined(_UNIT_TESTS_)
        // std::cout << "CreateTimer, currentTime: " << m_currentTime << ", newId: " << newTimerId <<
        //    ", expireTime: " << m_activeTimer[newTimerPos].timeItExpires << std::endl;
#endif
        incrementTimerId();
        return newTimerId;
    } else {
        return INVALID_TIMER_ID;
    }
}

void TimerMgr::cancelTimer(const uint32_t timerId)
{
    for(uint32_t cnt = 0; cnt < MAX_CURRENT_ACTIVE_TIMERS; cnt++) {
        if(timerId == m_activeTimer[cnt].timerId) {
            m_activeTimer[cnt].timerId = INVALID_TIMER_ID;
            m_activeTimer[cnt].timeItExpires = 0;
        }
    }
}

bool TimerMgr::isTimerExpired(const uint32_t timerId)
{
    if(INVALID_TIMER_ID == timerId) {
        return false;
    }
    for(uint32_t cnt = 0; cnt < MAX_CURRENT_ACTIVE_TIMERS; cnt++) {
        if((timerId == m_activeTimer[cnt].timerId) && (m_activeTimer[cnt].timeItExpires <= m_currentTime)) {
            cancelTimer(timerId);
            return true;
        }
    }
    return false;
}

uint32_t TimerMgr::getCurrentTime()
{
    return m_currentTime;
}

BCD_Time* TimerMgr::getBCD_Time()
{
    return &m_bcdTime;
}

void TimerMgr::incrementTimerId()
{
    m_nextFreeTimerId++;
    if(INVALID_TIMER_ID == m_nextFreeTimerId) {
        m_nextFreeTimerId++;
    }
}

bool TimerMgr::freePositionInArray(uint32_t& freePos)
{
    for(uint32_t cnt = 0; cnt < MAX_CURRENT_ACTIVE_TIMERS; cnt++) {
        if(INVALID_TIMER_ID == m_activeTimer[cnt].timerId) {
            freePos = cnt;
#if defined(_UNIT_TESTS_)
            // std::cout << "Free pos in array: " << freePos << std::endl;
#endif
            return true;
        }
    }
    return false;
}
