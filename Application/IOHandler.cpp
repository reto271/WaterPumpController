#include "IOHandler.hpp"

IOHandler::IOHandler()
    : m_levelLow(LEVEL_1_IN_GPIO_Port, LEVEL_1_IN_Pin, false, false)
    , m_levelHigh(LEVEL_1_IN_GPIO_Port, LEVEL_2_IN_Pin, false, false)
    , m_isPumpOn(false)
{
}

IOHandler::~IOHandler()
{
}

void IOHandler::run()
{
    m_levelLow.sampleInput();
    m_levelHigh.sampleInput();
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
#if !defined(_UNIT_TESTS_)
    if(true == pumpOn) {
        HAL_GPIO_WritePin(PUMP_OUT_GPIO_Port, PUMP_OUT_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(PUMP_OUT_GPIO_Port, PUMP_OUT_Pin, GPIO_PIN_RESET);
    }
 #endif
    m_isPumpOn = pumpOn;
}

bool IOHandler::getPumpState()
{
    return m_isPumpOn;
}

void IOHandler::setLED_State(bool LED_On)
{
#if !defined(_UNIT_TESTS_)
    if(true == LED_On) {
        // LED output is inverting
        HAL_GPIO_WritePin(LED_OUT_GPIO_Port, LED_OUT_Pin, GPIO_PIN_RESET);
    } else {
        HAL_GPIO_WritePin(LED_OUT_GPIO_Port, LED_OUT_Pin, GPIO_PIN_SET);
    }
 #endif
}
