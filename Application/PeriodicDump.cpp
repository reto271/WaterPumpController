#include "PeriodicDump.hpp"

#include "TimerMgr.hpp"
#include "DebugWriter.hpp"
#include "IOHandler.hpp"
#include "PumpController.hpp"

PeriodicDump::PeriodicDump(IIOHandler* pIOHandler, ITimerMgr* pTimerMgr, IDebugWriter* pDebugWriter)
    : m_pIOHandler(pIOHandler)
    , m_pTimerMgr(pTimerMgr)
    , m_pDebugWriter(pDebugWriter)
    , m_pPumpCtrl(nullptr)
    , m_startup(true)
{
}

PeriodicDump::~PeriodicDump()
{
}

void PeriodicDump::run()
{
    uint32_t time = m_pTimerMgr->getCurrentTime();

    if(((0xf & time) == 0) || (true == m_startup)) {
        m_startup = false;
        dumpInfo();
    }
}

void PeriodicDump::dumpInfo()
{
    m_pDebugWriter->print("alive", m_pTimerMgr->getBCD_Time());
    if(true == m_pIOHandler->getLevelLow()) {
        m_pDebugWriter->print("           Low: on");
    } else {
        m_pDebugWriter->print("           Low: off");
    }
    if(true == m_pIOHandler->getLevelHigh()) {
        m_pDebugWriter->print("           High: on");
    } else {
        m_pDebugWriter->print("           High: off");
    }
    if(true == m_pIOHandler->getPumpState()) {
        m_pDebugWriter->print("           Pump: on");
    } else {
        m_pDebugWriter->print("           Pump: off");
    }
    // Is the only pointer not set at construction time
    if(nullptr != m_pPumpCtrl) {
        m_pPumpCtrl->dumpState();
    }

}

void PeriodicDump::setPumpController(PumpController* pPumpCtrl)
{
    m_pPumpCtrl = pPumpCtrl;
}
