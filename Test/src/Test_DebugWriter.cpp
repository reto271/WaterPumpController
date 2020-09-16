#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdint.h>

#include "Application/DebugWriter.hpp"
#include "Application/BCD_Time.hpp"

#include "Mock_TimerMgr.hpp"

namespace
{
using ::testing::StrictMock;
using ::testing::NiceMock;
// using ::testing::Return;
// using ::testing::Exactly;
using ::testing::AtMost;
// using ::testing::_;
// using ::testing::HasSubstr;

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

    m_pDebugWriter->print("hello");
}

TEST_F(Test_DebugWriter, printWithTime)
{
    BCD_Time bcdTime;
    bcdTime.sec[3] = 3;
    m_pDebugWriter->print("hello", &bcdTime);
}


}   // unnamed namespace
