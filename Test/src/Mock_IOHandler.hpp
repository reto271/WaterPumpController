#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Application/IIOHandler.hpp"

class MockIOHandler : public IIOHandler
{
public:
    virtual ~MockIOHandler()
    {
    }

    MOCK_METHOD(void, run, (), (override));
    MOCK_METHOD(bool, getLevelLow, (), (override));
    MOCK_METHOD(bool, getLevelHigh, (), (override));
    MOCK_METHOD(void, setPumpState, (bool), (override));
    MOCK_METHOD(bool, getPumpState, (), (override));
    MOCK_METHOD(void, setLED_State, (bool), (override));
};
