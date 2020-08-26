#include "PumpController.hpp"

#include "IIOHandler.hpp"
#include "ITimerMgr.hpp"

PumpController::PumpController(IIOHandler* pIOHandler, ITimerMgr* pTimerMgr)
    : m_pIOHandler(pIOHandler)
    , m_pTimerMgr(pTimerMgr)
    , m_pumpState(PumpState::Off)
    , m_timerId(ITimerMgr::INVALID_TIMER_ID)
{
}

PumpController::~PumpController()
{
}

void PumpController::run()
{
    switch(m_pumpState) {
        case PumpState::On:
            state_On();
            break;

        case PumpState::OffTimeout:
            state_OffTimeout();
            break;

        default:
        case PumpState::Off:
            state_Off();
            break;
    }

    m_pIOHandler->setPumpState(PumpState::On == m_pumpState);
    m_pIOHandler->setLED_State(PumpState::On == m_pumpState);
}

void PumpController::onEnterState_On()
{
    m_timerId = m_pTimerMgr->createTimer(MAX_PUMP_RUN_TIME);
    m_pumpState = PumpState::On;
}

void PumpController::onEnterState_Off()
{
    m_pumpState = PumpState::Off;
}

void PumpController::onEnterState_OffTimeout()
{
    m_timerId = m_pTimerMgr->createTimer(MIN_PUMP_IDLE_TIME);
    m_pumpState = PumpState::OffTimeout;
}

void PumpController::state_On()
{
    if((false == m_pIOHandler->getLevelLow()) && (false == m_pIOHandler->getLevelHigh())) {
        m_pTimerMgr->cancelTimer(m_timerId);
        m_timerId = ITimerMgr::INVALID_TIMER_ID;
        onEnterState_OffTimeout();
    } else {
        if(true == m_pTimerMgr->isTimerExpired(m_timerId)) {
            m_timerId = ITimerMgr::INVALID_TIMER_ID;
            onEnterState_OffTimeout();
        }
    }
}

void PumpController::state_Off()
{
    if((true == m_pIOHandler->getLevelLow()) && (true == m_pIOHandler->getLevelHigh())) {
        onEnterState_On();
    }
}

void PumpController::state_OffTimeout()
{
    if(true == m_pTimerMgr->isTimerExpired(m_timerId)) {
        m_timerId = ITimerMgr::INVALID_TIMER_ID;
        onEnterState_Off();
    }
}
