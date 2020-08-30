#pragma once

#include <stdint.h>

class IPeriodicDump {
public:
    virtual void run() = 0;
};
