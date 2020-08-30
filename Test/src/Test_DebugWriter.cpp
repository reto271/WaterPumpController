#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdint.h>

#include "Application/DebugWriter.hpp"
#include "Application/ITimerMgr.hpp"
#include "Application/BCD_Time.hpp"


// GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
// {
//     return GPIO_PIN_RESET;
// }

namespace
{
using ::testing::StrictMock;
using ::testing::NiceMock;
// using ::testing::Return;
// using ::testing::Exactly;
using ::testing::AtMost;
// using ::testing::_;
// using ::testing::HasSubstr;

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

class Test_DebugWriter : public testing::Test
{
protected:
    void SetUp() override
    {
        // srand(time(NULL));
        char dummy;
        m_pDebugWriter = std::make_shared<DebugWriter>(&dummy, &mockTimerMgr);
    }

    void TearDown() override
    {
    }

    StrictMock<MockTimerMgr> mockTimerMgr;
    std::shared_ptr<DebugWriter> m_pDebugWriter;
};


TEST_F(Test_DebugWriter, simplePrint)
{

    m_pDebugWriter->print("hello", 5);
}

TEST_F(Test_DebugWriter, printWithTime)
{
    BCD_Time bcdTime;
    bcdTime.sec[3] = 3;
    m_pDebugWriter->print("hello", 5, &bcdTime);
}


}   // unnamed namespace
