#include "PumpController.hpp"

#include <stdio.h>

#include "IIOHandler.hpp"
#include "ITimerMgr.hpp"
#include "IDebugWriter.hpp"

PumpController::PumpController(IIOHandler* pIOHandler, ITimerMgr* pTimerMgr, IDebugWriter* pDebugWriter)
    : m_pIOHandler(pIOHandler)
    , m_pTimerMgr(pTimerMgr)
    , m_pDebugWriter(pDebugWriter)
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
    m_pDebugWriter->print("onEnterState_On", 15, m_pTimerMgr->getBCD_Time());
}

void PumpController::onEnterState_Off()
{
    m_pumpState = PumpState::Off;
    m_pDebugWriter->print("onEnterState_Off", 16, m_pTimerMgr->getBCD_Time());
}

void PumpController::onEnterState_OffTimeout()
{
    m_timerId = m_pTimerMgr->createTimer(MIN_PUMP_IDLE_TIME);
    m_pumpState = PumpState::OffTimeout;
    m_pDebugWriter->print("onEnterState_OffTimeout", 23, m_pTimerMgr->getBCD_Time());
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
