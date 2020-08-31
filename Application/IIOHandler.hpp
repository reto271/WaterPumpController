#pragma once

#include <stdint.h>

/// Handles all digital inputs and outputs. It is the central
///  instance to get information about the inputs and control
///  the digital outputs.
class IIOHandler {
public:
    /// Used to debounce the inputs signals.
    /// \remark Must be called ever 10ms.
    virtual void run() = 0;

    /// Returns the state of the lower water level sensor.
    /// \return true if the water is above the lower level.
    virtual bool getLevelLow() = 0;

    /// Returns the state of the higher water level sensor.
    /// \return true if the water is above the higher level.
    virtual bool getLevelHigh() = 0;

    /// Switches on/off the pump.
    /// \param[in] pumpOn: if set true the pump is switched on.
    virtual void setPumpState(bool pumpOn) = 0;

    /// Switches the LED on the CPU board.
    /// \param[in] LED_On: if set true the LED is switched on.
    virtual void setLED_State(bool LED_On) = 0;
};
