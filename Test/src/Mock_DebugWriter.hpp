#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Application/IDebugWriter.hpp"

class MockDebugWriter : public IDebugWriter
{
public:
    virtual ~MockDebugWriter()
    {
    }

    MOCK_METHOD(bool, print, (char const*, uint8_t), (override));
    MOCK_METHOD(bool, print, (char const*, uint8_t, BCD_Time*), (override));
};
