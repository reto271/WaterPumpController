#pragma once

#include <stdint.h>
#include <string>

#include "IInputSignal.hpp"


#if !defined(_UNIT_TESTS_)
#include "main.h"
#else
#include "../Test/src/Test_InputSignal.hpp"
#endif


/// Debounces a physical digital input signal and transforms it to a logical
/// input signal.
class InputSignal : public IInputSignal
{
public:
    /// Constructs a single digital input.
    /// \param[in] port on which the digital IO resides
    /// \param[in] pin number of the digital IO on the given port
    /// \param[in] logicalInitVal initial value of the digital input. Provide the logical state.
    /// \param[in] isInverting true if the input is inverting.
    InputSignal(GPIO_TypeDef* port, uint16_t pin, bool logicalInitVal, bool isInverting);
    virtual ~InputSignal();

    void sampleInput() override;
    bool getState() override;

protected:
    /// Do not allow uninitialized digital inputs.
    InputSignal();

    /// Prints the state of the input. Implemented for unit tests only.
    /// \param[in] title to be printed along with the input value.
    void printState(std::string title);

    /// Number of buffered samples to debounce the input.
    static const uint16_t DEBOUNCE_ARRAY_SIZE = 5;

    /// Handle to the GPIO port definition (STM driver lib)
    GPIO_TypeDef* m_port;

    /// Pin number of the input at the given port.
    uint16_t m_pin;

    /// Logical state of the input
    bool m_state;

    /// Index to write the next sample into the debounce array.
    uint16_t m_debArrayWritePos;

    /// Boolean array, stores the last DEBOUNCE_ARRAY_SIZE number of samples.
    bool m_debounceArray[DEBOUNCE_ARRAY_SIZE];

    /// Whether the input pin is inverting
    GPIO_PinState m_isInverting;
};
