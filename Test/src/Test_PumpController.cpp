#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdint.h>

#include "Application/PumpController.hpp"
#include "Application/IIOHandler.hpp"
#include "Application/ITimerMgr.hpp"


/// Time defined in PumpController.hpp
const uint32_t TEST_MAX_PUMP_RUN_TIME = 120;

/// Time defined in PumpController.hpp
const uint32_t TEST_MIN_PUMP_IDLE_TIME = 3600;

namespace
{
using ::testing::StrictMock;
using ::testing::Return;
// using ::testing::Exactly;
using ::testing::AtMost;
// using ::testing::_;
// using ::testing::HasSubstr;


#if 0
virtual WaxType GetPreferredWax(int) const = 0;
MOCK_METHOD1(GetPreferredWax, WaxType(int));

virtual void run() = 0;

virtual bool getLevelLow() = 0;
virtual bool getLevelHigh() = 0;
virtual void setPumpState(bool pumpOn) = 0;

#endif

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
    MOCK_METHOD(void, setLED_State, (bool), (override));
};

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

    MOCK_METHOD(uint32_t, createTimer, (const uint32_t), (override));
    MOCK_METHOD(void, cancelTimer, (const uint32_t), (override));
    MOCK_METHOD(bool, isTimerExpired, (const uint32_t), (override));
};

class Test_PumpController : public testing::Test
{
protected:
    void SetUp() override
    {
        // srand(time(NULL));
        m_pPumpCtrl = std::make_shared<PumpController>(&mockIOHdl, &mockTimerMgr);
    }

    void TearDown() override
    {
    }

    StrictMock<MockIOHandler> mockIOHdl;
    StrictMock<MockTimerMgr> mockTimerMgr;
    std::shared_ptr<PumpController> m_pPumpCtrl;
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
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();

    // Upper level signal no longer true
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(5).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(AtMost(5)).WillRepeatedly(Return(true));
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
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();
    m_pPumpCtrl->run();

    // Upper level signal no longer true
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(5).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(AtMost(5)).WillRepeatedly(Return(true));
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


}  // unnamed namespace
