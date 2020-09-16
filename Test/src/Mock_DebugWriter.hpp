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

    MOCK_METHOD(void, print, (char const*), (override));
    MOCK_METHOD(void, print, (char const*, BCD_Time*), (override));
};
