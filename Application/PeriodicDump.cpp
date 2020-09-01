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
{
}

PeriodicDump::~PeriodicDump()
{
}

void PeriodicDump::run()
{
    uint32_t time = m_pTimerMgr->getCurrentTime();

    if((0x7fff & time) == 0x7fff) {
        m_pDebugWriter->print("alive", 5, m_pTimerMgr->getBCD_Time());
        if(true == m_pIOHandler->getLevelLow()) {
            m_pDebugWriter->print("   Low: on", 10);
        } else {
            m_pDebugWriter->print("   Low: off", 11);
        }
        if(true == m_pIOHandler->getLevelHigh()) {
            m_pDebugWriter->print("   High: on", 11);
        } else {
            m_pDebugWriter->print("   High: off", 12);
        }
        if(true == m_pIOHandler->getPumpState()) {
            m_pDebugWriter->print("   Pump: on", 11);
        } else {
            m_pDebugWriter->print("   Pump: off", 12);
        }
        // Is the only pointer not set at construction time
        if(nullptr != m_pPumpCtrl) {
            m_pPumpCtrl->dumpState();
        }
    }
}

void PeriodicDump::setPumpController(PumpController* pPumpCtrl)
{
    m_pPumpCtrl = pPumpCtrl;
}
