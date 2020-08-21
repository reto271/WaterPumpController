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

protected:
    // bool debounceSignal(bool* pArray, uint16_t arraySize, bool newValue);

    bool m_pumpOn;
    InputSignal m_levelLow;
    InputSignal m_levelHigh;
};
