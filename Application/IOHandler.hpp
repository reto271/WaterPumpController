#ifndef __IOHANDLER_HPP__
#define __IOHANDLER_HPP__

#include <stdint.h>

class IOHandler {
public:
    IOHandler();
    virtual ~IOHandler();

    void run();

    bool getLevelLow();
    bool getLevelHigh();
    void setPumpState(bool pumpOn);

protected:
    bool debounceSignal(bool* pArray, uint16_t arraySize, bool newValue);

    static const uint16_t DEBOUNCE_ARRAY_SIZE = 5;
    static const uint16_t NR_SIGNALS_TO_DEBOUNCE = 2;

    bool m_debouncedSignals[NR_SIGNALS_TO_DEBOUNCE];
    bool m_debounceArray[NR_SIGNALS_TO_DEBOUNCE][DEBOUNCE_ARRAY_SIZE];
    uint16_t m_debArrayWritePos;

    bool m_pumpOn;
    bool m_levelLow;
    bool m_levelHigh;
};

#endif // __IOHANDLER_HPP__
