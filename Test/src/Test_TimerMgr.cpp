#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdint.h>

#include "Application/TimerMgr.hpp"
// #include "Application/ITimerMgr.hpp"

namespace
{
using ::testing::StrictMock;
using ::testing::Return;
// using ::testing::Exactly;
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

// class MockTimerMgr : public ITimerMgr
// {
// public:
//    virtual ~MockTimerMgr()
//    {
//    }
//
//    MOCK_METHOD(void, run, (), (override));
//    MOCK_METHOD(bool, getLevelLow, (), (override));
//    MOCK_METHOD(bool, getLevelHigh, (), (override));
//    MOCK_METHOD(void, setPumpState, (bool), (override));
//    MOCK_METHOD(void, setLED_State, (bool), (override));
// };

class Test_TimerMgr : public testing::Test, public TimerMgr
{
protected:
    void SetUp() override
    {
        // srand(time(NULL));
    }

    void TearDown() override
    {
    }

//    StrictMock<MockTimerMgr> mockIOHdl;
};


TEST_F(Test_TimerMgr, testInitialization)
{
    EXPECT_EQ(0, this->getCurrentTime());
    EXPECT_FALSE(this->is10ms());
    EXPECT_FALSE(this->is100ms());
    EXPECT_FALSE(this->isTimerExpired(0));
}

TEST_F(Test_TimerMgr, 10msInterval)
{
    this->timerISR();
    EXPECT_EQ(0, this->getCurrentTime());
    EXPECT_TRUE(this->is10ms());
    EXPECT_FALSE(this->is100ms());
    EXPECT_FALSE(this->isTimerExpired(0));
}

TEST_F(Test_TimerMgr, 100msInterval)
{
    for(uint32_t cnt = 0; cnt < 9; cnt++) {
        this->timerISR();
        EXPECT_EQ(0, this->getCurrentTime());
        EXPECT_FALSE(this->is100ms());
        EXPECT_FALSE(this->isTimerExpired(0));
    }
    this->timerISR();
    EXPECT_EQ(0, this->getCurrentTime());
    EXPECT_TRUE(this->is100ms());
    EXPECT_FALSE(this->isTimerExpired(0));
    this->confirm100ms();
    for(uint32_t cnt = 0; cnt < 9; cnt++) {
        this->timerISR();
        EXPECT_EQ(0, this->getCurrentTime());
        EXPECT_FALSE(this->is100ms());
        EXPECT_FALSE(this->isTimerExpired(0));
    }
    this->timerISR();
    EXPECT_EQ(0, this->getCurrentTime());
    EXPECT_TRUE(this->is100ms());
    EXPECT_FALSE(this->isTimerExpired(0));
}

TEST_F(Test_TimerMgr, 1sInterval)
{
    for(uint32_t cnt = 0; cnt < 99; cnt++) {
        this->timerISR();
        EXPECT_EQ(0, this->getCurrentTime());
        EXPECT_FALSE(this->isTimerExpired(0));
    }
    this->timerISR();
    EXPECT_EQ(1, this->getCurrentTime());
    EXPECT_FALSE(this->isTimerExpired(0));
    for(uint32_t cnt = 0; cnt < 99; cnt++) {
        this->timerISR();
        EXPECT_EQ(1, this->getCurrentTime());
        EXPECT_FALSE(this->isTimerExpired(0));
    }
    this->timerISR();
    EXPECT_EQ(2, this->getCurrentTime());
    EXPECT_FALSE(this->isTimerExpired(0));
}


TEST_F(Test_TimerMgr, singleTimer)
{
    uint32_t myTimerId;
    for(uint32_t cnt = 0; cnt < 300; cnt++) {
        this->timerISR();
        EXPECT_FALSE(this->isTimerExpired(0));
    }
    EXPECT_EQ(3, this->getCurrentTime());

    myTimerId = this->createTimer(4);
    EXPECT_EQ(0, myTimerId);

    for(uint32_t cnt = 0; cnt < 399; cnt++) {
        this->timerISR();
        // std::cout << "getCurrentTime: " << this->getCurrentTime() << std::endl;
        EXPECT_FALSE(this->isTimerExpired(myTimerId));
    }

    this->timerISR();
    EXPECT_TRUE(this->isTimerExpired(myTimerId));
    EXPECT_FALSE(this->isTimerExpired(myTimerId));
}


TEST_F(Test_TimerMgr, cancelTimer)
{
    uint32_t myTimerId;
    for(uint32_t cnt = 0; cnt < 300; cnt++) {
        this->timerISR();
        EXPECT_FALSE(this->isTimerExpired(0));
    }
    EXPECT_EQ(3, this->getCurrentTime());

    myTimerId = this->createTimer(4);
    EXPECT_EQ(0, myTimerId);

    for(uint32_t cnt = 0; cnt < 399; cnt++) {
        this->timerISR();
        // std::cout << "getCurrentTime: " << this->getCurrentTime() << std::endl;
        EXPECT_FALSE(this->isTimerExpired(myTimerId));
    }

    // Cancel the timer right before it expires
    this->cancelTimer(myTimerId);

    this->timerISR();
    EXPECT_FALSE(this->isTimerExpired(myTimerId));
    EXPECT_FALSE(this->isTimerExpired(myTimerId));
}


TEST_F(Test_TimerMgr, multipleTimers)
{
    uint32_t myTimerId_1;
    uint32_t myTimerId_2;
    uint32_t myTimerId_3;

    for(uint32_t cnt = 0; cnt < 300; cnt++) {
        this->timerISR();
        EXPECT_FALSE(this->isTimerExpired(0));
    }
    EXPECT_EQ(3, this->getCurrentTime());

    myTimerId_1 = this->createTimer(1);
    myTimerId_2 = this->createTimer(2);
    myTimerId_3 = this->createTimer(4);

    EXPECT_EQ(0, myTimerId_1);
    EXPECT_EQ(1, myTimerId_2);
    EXPECT_EQ(2, myTimerId_3);

    for(uint32_t cnt = 0; cnt < 99; cnt++) {
        this->timerISR();
        // std::cout << "getCurrentTime: " << this->getCurrentTime() << std::endl;
        EXPECT_FALSE(this->isTimerExpired(myTimerId_1));
        EXPECT_FALSE(this->isTimerExpired(myTimerId_2));
        EXPECT_FALSE(this->isTimerExpired(myTimerId_3));
    }

    this->timerISR();
    EXPECT_TRUE(this->isTimerExpired(myTimerId_1));
    EXPECT_FALSE(this->isTimerExpired(myTimerId_1));
    EXPECT_FALSE(this->isTimerExpired(myTimerId_2));
    EXPECT_FALSE(this->isTimerExpired(myTimerId_3));

    for(uint32_t cnt = 0; cnt < 99; cnt++) {
        this->timerISR();
        // std::cout << "getCurrentTime: " << this->getCurrentTime() << std::endl;
        EXPECT_FALSE(this->isTimerExpired(myTimerId_1));
        EXPECT_FALSE(this->isTimerExpired(myTimerId_2));
        EXPECT_FALSE(this->isTimerExpired(myTimerId_3));
    }

    this->timerISR();
    EXPECT_FALSE(this->isTimerExpired(myTimerId_1));
    EXPECT_TRUE(this->isTimerExpired(myTimerId_2));
    EXPECT_FALSE(this->isTimerExpired(myTimerId_2));
    EXPECT_FALSE(this->isTimerExpired(myTimerId_3));

    for(uint32_t cnt = 0; cnt < 199; cnt++) {
        this->timerISR();
        // std::cout << "getCurrentTime: " << this->getCurrentTime() << std::endl;
        EXPECT_FALSE(this->isTimerExpired(myTimerId_1));
        EXPECT_FALSE(this->isTimerExpired(myTimerId_2));
        EXPECT_FALSE(this->isTimerExpired(myTimerId_3));
    }

    this->timerISR();
    EXPECT_FALSE(this->isTimerExpired(myTimerId_1));
    EXPECT_FALSE(this->isTimerExpired(myTimerId_2));
    EXPECT_TRUE(this->isTimerExpired(myTimerId_3));
    EXPECT_FALSE(this->isTimerExpired(myTimerId_3));
}

TEST_F(Test_TimerMgr, tooManyTimers)
{

    EXPECT_EQ(0, this->createTimer(1));
    EXPECT_EQ(1, this->createTimer(1));
    EXPECT_EQ(2, this->createTimer(1));
    EXPECT_EQ(3, this->createTimer(1));
    EXPECT_EQ(4, this->createTimer(1));
    EXPECT_EQ(5, this->createTimer(1));
    EXPECT_EQ(6, this->createTimer(1));
    EXPECT_EQ(7, this->createTimer(1));
    EXPECT_EQ(8, this->createTimer(1));
    EXPECT_EQ(9, this->createTimer(1));
    EXPECT_EQ(INVALID_TIMER_ID, this->createTimer(1));
}


TEST_F(Test_TimerMgr, reuseOfTimers)
{

    EXPECT_EQ(0, this->createTimer(2));
    EXPECT_EQ(1, this->createTimer(2));
    EXPECT_EQ(2, this->createTimer(2));
    EXPECT_EQ(3, this->createTimer(2));
    EXPECT_EQ(4, this->createTimer(2));
    EXPECT_EQ(5, this->createTimer(1));
    EXPECT_EQ(6, this->createTimer(2));
    EXPECT_EQ(7, this->createTimer(2));
    EXPECT_EQ(8, this->createTimer(2));
    EXPECT_EQ(9, this->createTimer(2));

    for(uint32_t cnt = 0; cnt < 99; cnt++) {
        this->timerISR();
        // std::cout << "getCurrentTime: " << this->getCurrentTime() << std::endl;
        for(uint32_t timerIds = 0; timerIds < 22; timerIds++) {
            EXPECT_FALSE(this->isTimerExpired(timerIds));
        }
    }

    this->timerISR();
    EXPECT_FALSE(this->isTimerExpired(0));
    EXPECT_FALSE(this->isTimerExpired(1));
    EXPECT_FALSE(this->isTimerExpired(2));
    EXPECT_FALSE(this->isTimerExpired(3));
    EXPECT_FALSE(this->isTimerExpired(4));
    EXPECT_TRUE(this->isTimerExpired(5));
    EXPECT_FALSE(this->isTimerExpired(5));
    EXPECT_FALSE(this->isTimerExpired(6));
    EXPECT_FALSE(this->isTimerExpired(7));
    EXPECT_FALSE(this->isTimerExpired(8));
    EXPECT_FALSE(this->isTimerExpired(9));
    EXPECT_FALSE(this->isTimerExpired(10));

    // Create timer a the location timer 5 did expire
    EXPECT_EQ(10, this->createTimer(1));
    // Now there is no longer space
    EXPECT_EQ(INVALID_TIMER_ID, this->createTimer(1));
}

}  // unnamed namespace
