#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdint.h>

#include "Application/PumpController.hpp"
#include "Application/IIOHandler.hpp"

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
};

class Test_PumpController : public testing::Test // , public PumpController
{
protected:
    void SetUp() override
    {
        // srand(time(NULL));
        m_pPumpCtrl = std::make_shared<PumpController>(&mockIOHdl);
    }

    void TearDown() override
    {
    }

    StrictMock<MockIOHandler> mockIOHdl;
    std::shared_ptr<PumpController> m_pPumpCtrl;
};



TEST_F(Test_PumpController, expectOff)
{
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, setPumpState(false)).Times(1);
    m_pPumpCtrl->run();
    EXPECT_EQ(true, true);
}

TEST_F(Test_PumpController, stillOff)
{
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(1).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIOHdl, setPumpState(false)).Times(1);
    m_pPumpCtrl->run();
    EXPECT_EQ(true, true);
}

TEST_F(Test_PumpController, pumpOn)
{
    EXPECT_CALL(mockIOHdl, getLevelLow()).Times(1).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, getLevelHigh()).Times(1).WillRepeatedly(Return(true));
    EXPECT_CALL(mockIOHdl, setPumpState(true)).Times(1);
    m_pPumpCtrl->run();
    EXPECT_EQ(true, true);
}


}  // unnamed namespace
