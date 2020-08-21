#include "InputSignal.hpp"
#include <iostream>

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
    printState("Constructor");
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

    uint16_t doChangeCnt = 0;
    for(uint16_t cnt = 0; cnt < DEBOUNCE_ARRAY_SIZE; cnt++) {
        if(m_debounceArray[cnt] != m_state) {
            doChangeCnt++;
        }
    }
    if(5 <= doChangeCnt) {
        m_state = !m_state;
    }
    printState("sampleInput");
}

bool InputSignal::getState()
{
    return m_state;
}

void InputSignal::printState(std::string title)
{
    #if 0
    std::cout << "---" << title << "--------------------" << std::endl;
    std::cout << "arr: ";
    for(uint16_t cnt = 0; cnt < DEBOUNCE_ARRAY_SIZE; cnt++) {
        std::cout << m_debounceArray[cnt] << ", ";
    }
    std::cout << std::endl;
    std::cout << "state: " << m_state << std::endl;
    std::cout << "inverting: " << !m_isInverting << std::endl;
    std::cout << "---" << title << "--------------------" << std::endl;
    #endif
}
