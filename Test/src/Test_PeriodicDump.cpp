#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdint.h>

#include "Application/PeriodicDump.hpp"
#include "Application/IIOHandler.hpp"
#include "Application/BCD_Time.hpp"
#include "Application/IDebugWriter.hpp"

#include "Mock_TimerMgr.hpp"
#include "Mock_IOHandler.hpp"

namespace
{
using ::testing::StrictMock;
using ::testing::NiceMock;
using ::testing::Return;
// using ::testing::Exactly;
using ::testing::AtMost;
// using ::testing::_;
// using ::testing::HasSubstr;

class MockDebugWriter : public IDebugWriter
{
public:
    virtual ~MockDebugWriter()
    {
    }

    MOCK_METHOD(bool, print, (char const*, uint8_t), (override));
    MOCK_METHOD(bool, print, (char const*, uint8_t, BCD_Time*), (override));
};

class Test_PeriodicDump : public testing::Test
{
protected:
    void SetUp() override
    {
        // srand(time(NULL));
        m_pPumpCtrl = std::make_shared<PeriodicDump>(&mockIOHdl, &mockTimerMgr, &mockDbgWriter);
        // m_testTime.sec[0] = 1;
        // m_testTime.sec[1] = 2;
        // m_testTime.sec[2] = 4;
    }

    void TearDown() override
    {
    }

    StrictMock<MockIOHandler> mockIOHdl;
    StrictMock<MockTimerMgr> mockTimerMgr;
    NiceMock<MockDebugWriter> mockDbgWriter;
    std::shared_ptr<PeriodicDump> m_pPumpCtrl;
//    BCD_Time m_testTime;
};


TEST_F(Test_PeriodicDump, notAtDumpTime)
{
    EXPECT_CALL(mockTimerMgr, getCurrentTime()).Times(1).WillRepeatedly(Return(1234));
    m_pPumpCtrl->run();
}

TEST_F(Test_PeriodicDump, DumpTimeAndState)
{
    BCD_Time currentTimeBCD;
    currentTimeBCD.sec[3] = 7;
    EXPECT_CALL(mockTimerMgr, getCurrentTime()).Times(1).WillRepeatedly(Return(0x12ffff));
    EXPECT_CALL(mockTimerMgr, getBCD_Time()).Times(1).WillRepeatedly(Return(&currentTimeBCD));
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(AtMost(1)).WillRepeatedly(Return(false));
    m_pPumpCtrl->run();
}

}  // unnamed namespace
