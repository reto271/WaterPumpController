#include "IOHandler.hpp"

// #if !defined(_UNIT_TESTS_)
// #include "main.h"
// #else
// #include "../Test/src/Test_IOHandler.hpp"
// #endif

IOHandler::IOHandler()
//    InputSignal(GPIO_TypeDef* port, uint16_t pin, bool logicalInitVal, bool isInverting);
    : m_levelLow(LEVEL_1_IN_GPIO_Port, LEVEL_1_IN_Pin, false, false)
    , m_levelHigh(LEVEL_1_IN_GPIO_Port, LEVEL_2_IN_Pin, false, false)
{
}

IOHandler::~IOHandler()
{
}

void IOHandler::run()
{
//    GPIO_PinState newValue = HAL_GPIO_ReadPin(LEVEL_1_IN_GPIO_Port, LEVEL_1_IN_Pin);
//    m_levelLow = debounceSignal(&m_debounceArray[0][0], DEBOUNCE_ARRAY_SIZE, (GPIO_PIN_SET == newValue));
//
//    newValue = HAL_GPIO_ReadPin(LEVEL_1_IN_GPIO_Port, LEVEL_2_IN_Pin);
//    m_levelHigh = debounceSignal(&m_debounceArray[1][0], DEBOUNCE_ARRAY_SIZE, (GPIO_PIN_SET == newValue));
}

bool IOHandler::getLevelLow()
{
    return m_levelLow.getState();
}

bool IOHandler::getLevelHigh()
{
    return m_levelHigh.getState();
}

void IOHandler::setPumpState(bool pumpOn)
{
//    m_pumpOn = pumpOn;
//    if(true == m_pumpOn) {
// #if !defined(_UNIT_TESTS_)
//        HAL_GPIO_WritePin(PUMP_OUT_GPIO_Port, PUMP_OUT_Pin, GPIO_PIN_SET);
// #endif
//    } else {
// #if !defined(_UNIT_TESTS_)
//        HAL_GPIO_WritePin(PUMP_OUT_GPIO_Port, PUMP_OUT_Pin, GPIO_PIN_RESET);
// #endif
//    }
}
