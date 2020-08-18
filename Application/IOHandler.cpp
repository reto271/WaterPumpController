#include "IOHandler.hpp"

#if !defined(_UNIT_TESTS_)
#include "main.h"
#endif

IOHandler::IOHandler()
{
//    for(uint16_t cnt = 0; cnt < DEBOUNCE_ARRAY_SIZE; cnt++) {
//        m_levelLowDebArray[cnt] = false;
//        m_levelHighDebArray[cnt] = false;
//    }
}

IOHandler::~IOHandler()
{
}

void IOHandler::run()
{

//    debounceValue(m_levelLowDebArray, newValue);
//    debounceValue(m_levelHighDebArray, newValue);
//
//
//    // Next writePos
//    m_debArrayWritePos++;
//    if(DEBOUNCE_ARRAY_SIZE <= m_debArrayWritePos) {
//        m_debArrayWritePos = 0;
//    }
}

bool IOHandler::getLevelLow()
{
//    return m_levelLow;
    return false;
}

bool IOHandler::getLevelHigh()
{
//    return m_levelHigh;
    return false;
}

void IOHandler::setPumpState(bool pumpOn)
{
    m_pumpOn = pumpOn;
    if(true == m_pumpOn) {
#if !defined(_UNIT_TESTS_)
        HAL_GPIO_WritePin(PUMP_OUT_GPIO_Port, PUMP_OUT_Pin, GPIO_PIN_SET);
#endif
    } else {
#if !defined(_UNIT_TESTS_)
        HAL_GPIO_WritePin(PUMP_OUT_GPIO_Port, PUMP_OUT_Pin, GPIO_PIN_RESET);
#endif
    }
}

bool IOHandler::debounceSignal(bool* pArray, uint16_t arraySize)
{
}

#if 0
GPIO_PIN_RESET = 0U,
GPIO_PIN_SET

#define LEVEL_1_IN_Pin GPIO_PIN_0
#define LEVEL_1_IN_GPIO_Port GPIOA
#define LEVEL_2_IN_Pin GPIO_PIN_1
#define LEVEL_2_IN_GPIO_Port GPIOA
#define PUMP_OUT_Pin GPIO_PIN_2
#define PUMP_OUT_GPIO_Port GPIOA
#define LED_OUT_Pin GPIO_PIN_4
#define LED_OUT_GPIO_Port GPIOA
#endif
