#include "Application.hpp"

#include "stm32f0xx_hal.h"
#include "main.h"

#include "DebugWriter.hpp"
#include "TimerMgr.hpp"
#include "IOHandler.hpp"
#include "PeriodicDump.hpp"
#include "PumpController.hpp"

static DebugWriter* pDbgWriter = NULL;
static TimerMgr* pTimerMgr = NULL;
static IOHandler* pIoHandler = NULL;
static PeriodicDump* pPeriodicDump = NULL;
static PumpController* pPumpCtrl = NULL;

void initializeBackgroundLoop(UART_HandleTypeDef* pUART_Hdl)
{
    pTimerMgr = new TimerMgr();
    pDbgWriter = new DebugWriter(pUART_Hdl, pTimerMgr);
    pIoHandler = new IOHandler();
    pPeriodicDump = new PeriodicDump(pIoHandler, pTimerMgr, pDbgWriter);
    pPumpCtrl = new PumpController(pIoHandler, pTimerMgr, pDbgWriter);

    pPeriodicDump->setPumpController(pPumpCtrl);

    pDbgWriter->print(" ", 1);
    pDbgWriter->print("Water Pump Controller", 21);
    // pDbgWriter->print("V01.09 B03", 10);
    pDbgWriter->print("V01.09", 6);
    pDbgWriter->print("---", 3);
}

void ApplicationTimerInterrupt10ms()
{
    pTimerMgr->timerISR();
}

void runBackgroudLoop()
{
    if(true == pTimerMgr->is10ms()) {
        pTimerMgr->confirm10ms();
        pIoHandler->run();
    }
    if(true == pTimerMgr->is100ms()) {
        pTimerMgr->confirm100ms();
        pPumpCtrl->run();
    }
    if(true == pTimerMgr->is1s()) {
        pTimerMgr->confirm1s();
        pPeriodicDump->run();
    }
}
