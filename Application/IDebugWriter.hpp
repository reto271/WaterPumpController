#pragma once

#include <stdint.h>

class BCD_Time;

class IDebugWriter
{
public:
    virtual bool print(char const* pData, uint8_t len) = 0;
    virtual bool print(char const* pData, uint8_t len, BCD_Time* pBCD_Time) = 0;
};
