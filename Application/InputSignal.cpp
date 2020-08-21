#include "InputSignal.hpp"


InputSignal::InputSignal(GPIO_TypeDef* port, uint16_t pin, bool logicalInitVal, bool isInverting)
    : m_port(port)
    , m_pin(pin)
    , m_state(logicalInitVal)
    , m_debArrayWritePos(0)
{
    for(uint16_t cnt = 0; cnt < DEBOUNCE_ARRAY_SIZE; cnt++) {
        m_debounceArray[cnt] = logicalInitVal;
    }
    if(true == isInverting) {
        m_isInverting = GPIO_PIN_RESET;
    } else {
        m_isInverting = GPIO_PIN_SET;
    }
}

InputSignal::~InputSignal()
{
}

void InputSignal::sampleInput()
{
    GPIO_PinState newSample = HAL_GPIO_ReadPin(m_port, m_pin);
    bool logicalSample = (m_isInverting == newSample);

    // Next writePos
    m_debArrayWritePos++;
    if(DEBOUNCE_ARRAY_SIZE <= m_debArrayWritePos) {
        m_debArrayWritePos = 0;
    }
    m_debounceArray[m_debArrayWritePos] = logicalSample;

    bool doChange = true;
    for(uint16_t cnt = 0; cnt < DEBOUNCE_ARRAY_SIZE; cnt++) {
        if(m_debounceArray[m_debArrayWritePos] == m_state) {
            doChange = false;
        }
    }
    if(true == doChange) {
        m_state = !m_state;
    }
}

bool InputSignal::getState()
{
    return m_state;
}
