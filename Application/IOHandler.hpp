#pragma once

#include <stdint.h>
#include "IIOHandler.hpp"
#include "InputSignal.hpp"

class IOHandler : public IIOHandler
{
public:
    IOHandler();
    virtual ~IOHandler();

    void run() override;

    bool getLevelLow() override;
    bool getLevelHigh() override;
    void setPumpState(bool pumpOn) override;
    void setLED_State(bool LED_On) override;

protected:
    InputSignal m_levelLow;
    InputSignal m_levelHigh;
};
