#pragma once

#include <stdint.h>

class IIOHandler {
public:
    virtual void run() = 0;

    virtual bool getLevelLow() = 0;
    virtual bool getLevelHigh() = 0;
    virtual void setPumpState(bool pumpOn) = 0;
};
