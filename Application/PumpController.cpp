#include "PumpController.hpp"

#include "IOHandler.hpp"

PumpController::PumpController(IIOHandler* pIOHandler)
    : m_pIOHandler(pIOHandler)
    , m_pumpState(PumpState::Off)
{
}

PumpController::~PumpController()
{
}

void PumpController::run()
{
    if(false == m_pIOHandler->getLevelLow()) {
        m_pumpState = PumpState::Off;
    }
    if(true == m_pIOHandler->getLevelHigh()) {
        m_pumpState = PumpState::On;
    }
    m_pIOHandler->setPumpState(PumpState::On == m_pumpState);
}

#if 0

On,
Off,
OffByTimeout
}
PumpController();

IIOHandler* m_pIOHandler;
PumpState m_pumpState;
#endif
