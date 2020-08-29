#pragma once

#include <stdint.h>

class BCD_Time
{
public:
    BCD_Time();
    virtual ~BCD_Time();

    void incrementSecond();


    static const uint8_t NR_DIGITS = 8;
    uint8_t sec[8];
};
