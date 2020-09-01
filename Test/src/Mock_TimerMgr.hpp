#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Application/ITimerMgr.hpp"

class MockTimerMgr : public ITimerMgr
{
public:
    virtual ~MockTimerMgr()
    {
    }

    MOCK_METHOD(void, timerISR, (), (override));
    MOCK_METHOD(bool, is10ms, (), (override));
    MOCK_METHOD(void, confirm10ms, (), (override));

    MOCK_METHOD(bool, is100ms, (), (override));
    MOCK_METHOD(void, confirm100ms, (), (override));

    MOCK_METHOD(bool, is1s, (), (override));
    MOCK_METHOD(void, confirm1s, (), (override));

    MOCK_METHOD(uint32_t, createTimer, (const uint32_t), (override));
    MOCK_METHOD(void, cancelTimer, (const uint32_t), (override));
    MOCK_METHOD(bool, isTimerExpired, (const uint32_t), (override));

    MOCK_METHOD(uint32_t, getCurrentTime, (), (override));
    MOCK_METHOD(BCD_Time*, getBCD_Time, (), (override));
};
