#include "Application.hpp"

#include "stm32f0xx_hal.h"
#include "main.h"

#include "TimerMgr.hpp"
#include "IOHandler.hpp"
#include "PumpController.hpp"

static TimerMgr* pTimerMgr = NULL;
static IOHandler* pIoHandler = NULL;
static PumpController* pPumpCtrl = NULL;

static void blinkDiv10();


void initializeBackgroundLoop()
{
    pTimerMgr = new TimerMgr();
    pIoHandler = new IOHandler();
    pPumpCtrl = new PumpController(pIoHandler);
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
        blinkDiv10();
    }
}

static void blinkDiv10()
{
    static uint32_t cnt = 0;
    if(10 <= cnt) {
        cnt = 0;
    }
    cnt++;
}
