#pragma once

#include <stdint.h>
#include "IIOHandler.hpp"
#include "InputSignal.hpp"

/// Handles all digital inputs and outputs. It is the central
///  instance to get information about the inputs and control
///  the digital outputs.
class IOHandler : public IIOHandler
{
public:
    /// Constructs the IO handler. Creates an InputSignal instance
    ///  for all digital inputs. Outputs are directly controlled
    ///  from this object.
    IOHandler();

    /// Destructor of the IO-Handler
    virtual ~IOHandler();

    void run() override;

    bool getLevelLow() override;
    bool getLevelHigh() override;
    void setPumpState(bool pumpOn) override;
    bool getPumpState() override;
    void setLED_State(bool LED_On) override;

protected:
    /// Input signal to detect the lower water level (switch off the pump).
    InputSignal m_levelLow;

    /// Input signal to detect the higher water level (switch on the pump).
    InputSignal m_levelHigh;

    /// State of the pump
    bool m_isPumpOn;
};
