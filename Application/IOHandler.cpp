#include "IOHandler.hpp"

#if !defined(_UNIT_TESTS_)
#include "main.h"
#else
#include "../Test/src/Test_IOHandler.hpp"
#endif

IOHandler::IOHandler()
    : m_debArrayWritePos(0)
    , m_pumpOn(false)
{
    int val = 0;
    for(uint16_t sigCnt = 0; sigCnt < NR_SIGNALS_TO_DEBOUNCE; sigCnt++) {
        m_debouncedSignals[sigCnt] = 0;
        for(uint16_t sampleCnt = 0; sampleCnt < DEBOUNCE_ARRAY_SIZE; sampleCnt++) {
            m_debounceArray[sigCnt][sampleCnt] = val;
            val++;
        }
    }
}

IOHandler::~IOHandler()
{
}

void IOHandler::run()
{
    GPIO_PinState newValue = HAL_GPIO_ReadPin(LEVEL_1_IN_GPIO_Port, LEVEL_1_IN_Pin);
    m_levelLow = debounceSignal(&m_debounceArray[0][0], DEBOUNCE_ARRAY_SIZE, (GPIO_PIN_SET == newValue));

    newValue = HAL_GPIO_ReadPin(LEVEL_1_IN_GPIO_Port, LEVEL_2_IN_Pin);
    m_levelHigh = debounceSignal(&m_debounceArray[1][0], DEBOUNCE_ARRAY_SIZE, (GPIO_PIN_SET == newValue));

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
    return m_levelLow;
}

bool IOHandler::getLevelHigh()
{
    return m_levelHigh;
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

bool IOHandler::debounceSignal(bool* pArray, uint16_t arraySize, bool newValue)
{
    // No debouncing implemented yet 
    return newValue;
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
