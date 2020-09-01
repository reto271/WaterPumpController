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
    : m_exe10msInterval(false)
    , m_exe100msInterval(false)
    , m_exe1sInterval(false)
    , m_periodCounter10ms(1)
    , m_periodCounter100ms(1)
    , m_currentTime(0)
    , m_lastAssignedTimerId(0)
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
//    assert(false === m_exe10msInterval);
    m_exe10msInterval = true;
    if(10 <= m_periodCounter10ms) {
        m_periodCounter10ms = 0;
//        assert(false === m_exe100msInterval);
        m_exe100msInterval = true;
        if(10 <= m_periodCounter100ms) {
            m_periodCounter100ms = 0;
            m_currentTime++;
            m_bcdTime.incrementSecond();
            m_exe1sInterval = true;
        }
        m_periodCounter100ms++;
    }
    m_periodCounter10ms++;
}

bool TimerMgr::is10ms()
{
    return m_exe10msInterval;
}

void TimerMgr::confirm10ms()
{
    m_exe10msInterval = false;
}

bool TimerMgr::is100ms()
{
    return m_exe100msInterval;
}

void TimerMgr::confirm100ms()
{
    m_exe100msInterval = false;
}

bool TimerMgr::is1s()
{
    return m_exe1sInterval;
}

void TimerMgr::confirm1s()
{
    m_exe1sInterval = false;
}

uint32_t TimerMgr::createTimer(const uint32_t timeoutInSec)
{
    uint32_t newTimerId = getAvailableTimerId();
    uint32_t newTimerPos = INVALID_TIMER_ID;
    if(true == freePositionInArray(newTimerPos)) {
        m_activeTimer[newTimerPos].timerId = newTimerId;
        m_activeTimer[newTimerPos].timeItExpires = m_currentTime + timeoutInSec;
#if defined(_UNIT_TESTS_)
        // std::cout << "CreateTimer, currentTime: " << m_currentTime << ", newId: " << newTimerId <<
        //    ", expireTime: " << m_activeTimer[newTimerPos].timeItExpires << std::endl;
#endif
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

uint32_t TimerMgr::getAvailableTimerId()
{
    bool idFound;
    do {
        idFound = true;
        m_lastAssignedTimerId++;

        // Care about the wrap-around
        if(INVALID_TIMER_ID == m_lastAssignedTimerId) {
            m_lastAssignedTimerId = 0;
        }

        // Is the ID in use?
        for(uint32_t cnt = 0; cnt < MAX_CURRENT_ACTIVE_TIMERS; cnt++) {
            if(m_lastAssignedTimerId == m_activeTimer[cnt].timerId) {
                idFound = false;
            }
        }
    } while(false == idFound);
    return m_lastAssignedTimerId;
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

void TimerMgr::setLastAssignedId(uint32_t id)
{
    m_lastAssignedTimerId = id;
}
