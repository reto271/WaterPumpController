#pragma once

#include <stdint.h>
#include "IInputSignal.hpp"


#if !defined(_UNIT_TESTS_)
#include "main.h"
#else
#include "../Test/src/Test_InputSignal.hpp"
#endif
// #include "Drivers/CMSIS/Device/ST/STM32F0xx/Include/stm32f030x6.h"

class InputSignal : public IInputSignal
{
public:
    InputSignal(GPIO_TypeDef* port, uint16_t pin, bool logicalInitVal, bool isInverting);
    virtual ~InputSignal();

    void sampleInput() override;

    bool getState() override;

protected:
    InputSignal();

    static const uint16_t DEBOUNCE_ARRAY_SIZE = 5;

    GPIO_TypeDef* m_port;
    uint16_t m_pin;

    bool m_state;
    uint16_t m_debArrayWritePos;
    bool m_debounceArray[DEBOUNCE_ARRAY_SIZE];
    GPIO_PinState m_isInverting;
};
