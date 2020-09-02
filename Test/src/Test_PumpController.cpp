#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdint.h>

#include "Application/PumpController.hpp"
#include "Application/BCD_Time.hpp"

#include "Mock_TimerMgr.hpp"
#include "Mock_IOHandler.hpp"
#include "Mock_DebugWriter.hpp"

/// Time defined in PumpController.hpp
const uint32_t TEST_MAX_PUMP_RUN_TIME = 10 * 60;

/// Time defined in PumpController.hpp
const uint32_t TEST_MIN_PUMP_IDLE_TIME = 24 * 3600;

namespace
{
using ::testing::StrictMock;
using ::testing::NiceMock;
using ::testing::Return;
// using ::testing::Exactly;
using ::testing::AtMost;
// using ::testing::_;
// using ::testing::HasSubstr;


class Test_PumpController : public testing::Test
{
protected:
    void SetUp() override
    {
        // srand(time(NULL));
        m_pPumpCtrl = std::make_shared<PumpController>(&mockIOHdl, &mockTimerMgr, &mockDbgWriter);
        m_testTime.sec[0] = 1;
        m_testTime.sec[1] = 2;
        m_testTime.sec[2] = 4;
    }

    void TearDown() override
    {
    }

    StrictMock<MockIOHandler> mockIOHdl;
    StrictMock<MockTimerMgr> mockTimerMgr;
    NiceMock<MockDebugWriter> mockDbgWriter;
    std::shared_ptr<PumpController> m_pPumpCtrl;
    BCD_Time m_testTime;
};


TEST_F(Test_PumpController, expectOffAtInitialization)
{
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(AtMost(1)).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, setPumpState(false)).Times(1);
    EXPECT_CALL(mockIOHdl, setLED_State(false)).Times(1);
    m_pPumpCtrl->run();
}

TEST_F(Test_PumpController, stillOff)
{
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(1).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, setPumpState(false)).Times(1);
    EXPECT_CALL(mockIOHdl, setLED_State(false)).Times(1);
    m_pPumpCtrl->run();
}

TEST_F(Test_PumpController, pumpOn)
{
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(1).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(1).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, setPumpState(true)).Times(1);
    EXPECT_CALL(mockIOHdl, setLED_State(true)).Times(1);
    EXPECT_CALL(mockTimerMgr, createTimer(TEST_MAX_PUMP_RUN_TIME)).Times(1).WillRepeatedly(Return(1));
    EXPECT_CALL(mockTimerMgr, getBCD_Time()).Times(1).WillRepeatedly(Return(&m_testTime));
    m_pPumpCtrl->run();
}

TEST_F(Test_PumpController, switchOnLaterOffByLevel)
{
    const uint32_t TIMER_ID_ON_TIME = 1;
    const uint32_t TIMER_ID_OFF_TIME = 2;

    // Both levels true -> switch on the pump
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(3).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(AtMost(3)).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, setPumpState(true)).Times(3);
    EXPECT_CALL(mockIOHdl, setLED_State(true)).Times(3);
    EXPECT_CALL(mockTimerMgr, createTimer(TEST_MAX_PUMP_RUN_TIME)).Times(1).WillRepeatedly(Return(TIMER_ID_ON_TIME));
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_ON_TIME)).Times(2).WillRepeatedly(Return(false));
    EXPECT_CALL(mockTimerMgr, getBCD_Time()).Times(2).WillRepeatedly(Return(&m_testTime));
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();

    // Upper level signal no longer true
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(5).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(AtMost(5)).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, setPumpState(true)).Times(5);
    EXPECT_CALL(mockIOHdl, setLED_State(true)).Times(5);
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_ON_TIME)).Times(5).WillRepeatedly(Return(false));
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();

    // Lower level signal no longer true -> switch off and start idle timeout
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, setPumpState(false)).Times(4);
    EXPECT_CALL(mockIOHdl, setLED_State(false)).Times(4);
    EXPECT_CALL(mockTimerMgr, cancelTimer(TIMER_ID_ON_TIME)).Times(1);
    EXPECT_CALL(mockTimerMgr, createTimer(TEST_MIN_PUMP_IDLE_TIME)).Times(1).WillRepeatedly(Return(TIMER_ID_OFF_TIME));
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_OFF_TIME)).Times(3).WillRepeatedly(Return(false));
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
}

TEST_F(Test_PumpController, switchOnLaterOffByTimeout)
{
    const uint32_t TIMER_ID_ON_TIME = 1;
    const uint32_t TIMER_ID_OFF_TIME = 2;

    // Both levels true -> switch on the pump
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(3).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(AtMost(3)).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, setPumpState(true)).Times(3);
    EXPECT_CALL(mockIOHdl, setLED_State(true)).Times(3);
    EXPECT_CALL(mockTimerMgr, createTimer(TEST_MAX_PUMP_RUN_TIME)).Times(1).WillRepeatedly(Return(TIMER_ID_ON_TIME));
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_ON_TIME)).Times(2).WillRepeatedly(Return(false));
    EXPECT_CALL(mockTimerMgr, getBCD_Time()).Times(2).WillRepeatedly(Return(&m_testTime));
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();

    // Upper level signal no longer true
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(5).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(AtMost(5)).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, setPumpState(true)).Times(5);
    EXPECT_CALL(mockIOHdl, setLED_State(true)).Times(5);
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_ON_TIME)).Times(5).WillRepeatedly(Return(false));
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();

    // Lower level signal still on, timeout -> switch off and start idle timeout
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(1).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(AtMost(1)).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, setPumpState(false)).Times(4);
    EXPECT_CALL(mockIOHdl, setLED_State(false)).Times(4);
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_ON_TIME)).Times(1).WillRepeatedly(Return(true));
    EXPECT_CALL(mockTimerMgr, createTimer(TEST_MIN_PUMP_IDLE_TIME)).Times(1).WillRepeatedly(Return(TIMER_ID_OFF_TIME));
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_OFF_TIME)).Times(3).WillRepeatedly(Return(false));
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
}


TEST_F(Test_PumpController, switchOnOfftestIdleTimeout)
{
    const uint32_t TIMER_ID_ON_TIME = 1;
    const uint32_t TIMER_ID_OFF_TIME = 2;
    const uint32_t TIMER_ID_ON_TIME_2 = 3;

    // Both levels true -> switch on the pump
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(1).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(AtMost(1)).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, setPumpState(true)).Times(1);
    EXPECT_CALL(mockIOHdl, setLED_State(true)).Times(1);
    EXPECT_CALL(mockTimerMgr, createTimer(TEST_MAX_PUMP_RUN_TIME)).Times(1).WillRepeatedly(Return(TIMER_ID_ON_TIME));
//    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_ON_TIME)).Times(2).WillRepeatedly(Return(false));
    EXPECT_CALL(mockTimerMgr, getBCD_Time()).Times(4).WillRepeatedly(Return(&m_testTime));
    m_pPumpCtrl->run();

    // Upper level signal no longer true
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(AtMost(1)).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, setPumpState(true)).Times(1);
    EXPECT_CALL(mockIOHdl, setLED_State(true)).Times(1);
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_ON_TIME)).Times(1).WillRepeatedly(Return(false));
    m_pPumpCtrl->run();

    // Lower level signal no longer true -> switch off and start idle timeout
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, setPumpState(false)).Times(2);
    EXPECT_CALL(mockIOHdl, setLED_State(false)).Times(2);
    EXPECT_CALL(mockTimerMgr, cancelTimer(TIMER_ID_ON_TIME)).Times(1);
    EXPECT_CALL(mockTimerMgr, createTimer(TEST_MIN_PUMP_IDLE_TIME)).Times(1).WillRepeatedly(Return(TIMER_ID_OFF_TIME));
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_OFF_TIME)).Times(1).WillRepeatedly(Return(false));
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();

    // Lower level signal on again
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(0);    // no call, still in idle timeout
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(0);   // no call, still in idle timeout
    EXPECT_CALL(mockIOHdl, setPumpState(false)).Times(2);
    EXPECT_CALL(mockIOHdl, setLED_State(false)).Times(2);
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_OFF_TIME)).Times(2).WillRepeatedly(Return(false));
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();

    // Idle timer expires
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(AtMost(1)).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, setPumpState(false)).Times(2);
    EXPECT_CALL(mockIOHdl, setLED_State(false)).Times(2);
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_OFF_TIME)).Times(1).WillRepeatedly(Return(true));
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();

    // Lower level becomes true
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(2).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(2).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, setPumpState(false)).Times(2);
    EXPECT_CALL(mockIOHdl, setLED_State(false)).Times(2);
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();

    // Higher level becomes true
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(5).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(AtMost(5)).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, setPumpState(true)).Times(5);
    EXPECT_CALL(mockIOHdl, setLED_State(true)).Times(5);
    EXPECT_CALL(mockTimerMgr, createTimer(TEST_MAX_PUMP_RUN_TIME)).Times(1).WillRepeatedly(Return(TIMER_ID_ON_TIME_2));
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_ON_TIME)).Times(0);
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_OFF_TIME)).Times(0);
    EXPECT_CALL(mockTimerMgr, isTimerExpired(TIMER_ID_ON_TIME_2)).Times(4).WillRepeatedly(Return(false));
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
}

}  // unnamed namespace
