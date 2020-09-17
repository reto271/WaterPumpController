#include "Application.hpp"

#include "stm32f0xx_hal.h"
#include "main.h"

#include "DebugWriter.hpp"
#include "TimerMgr.hpp"
#include "IOHandler.hpp"
#include "PeriodicDump.hpp"
#include "PumpController.hpp"
#include "CommandInterpreter.hpp"

static DebugWriter* m_pDbgWriter = NULL;
static TimerMgr* m_pTimerMgr = NULL;
static IOHandler* m_pIoHandler = NULL;
static PeriodicDump* m_pPeriodicDump = NULL;
static PumpController* m_pPumpCtrl = NULL;
static CommandInterpreter* m_pCmdInter = NULL;

void initializeBackgroundLoop(UART_HandleTypeDef* pUART_Hdl)
{
    m_pTimerMgr = new TimerMgr();
    m_pDbgWriter = new DebugWriter(pUART_Hdl, m_pTimerMgr);
    m_pIoHandler = new IOHandler();
    m_pPeriodicDump = new PeriodicDump(m_pIoHandler, m_pTimerMgr, m_pDbgWriter);
    m_pPumpCtrl = new PumpController(m_pIoHandler, m_pTimerMgr, m_pDbgWriter);
    m_pCmdInter = new CommandInterpreter(pUART_Hdl, m_pPeriodicDump);

    m_pPeriodicDump->setPumpController(m_pPumpCtrl);

    m_pPumpCtrl->printNameAndVersion();
}

void ApplicationTimerInterrupt10ms()
{
    m_pTimerMgr->timerISR();
}

void runBackgroudLoop()
{
    if(true == m_pTimerMgr->is10ms()) {
        m_pTimerMgr->confirm10ms();
        m_pIoHandler->run();
    }
    if(true == m_pTimerMgr->is100ms()) {
        m_pTimerMgr->confirm100ms();
        m_pPumpCtrl->run();
    }
    if(true == m_pTimerMgr->is1s()) {
        m_pTimerMgr->confirm1s();
        m_pPeriodicDump->run();
    }
    // Poll UART, check if there are commands from the terminal
    m_pCmdInter->pollUART();
}
