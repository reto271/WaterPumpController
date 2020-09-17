#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdint.h>

#include "Application/CommandInterpreter.hpp"

namespace
{
using ::testing::StrictMock;
using ::testing::Return;
// using ::testing::Exactly;
// using ::testing::_;
// using ::testing::HasSubstr;


class Test_CommandInterpreter : public testing::Test /// , public CommandInterpreter
{
protected:
    void SetUp() override
    {
        // srand(time(NULL));
        // m_pCmdInter = std::make_shared<CommandInterpreter>(mockUART_Hdl)
    }

    void TearDown() override
    {
    }

    UART_HandleTypeDef mockUART_Hdl;
    // StrictMock<MockPeriodicDump> mockPeriodicDump;
    std::shared_ptr<CommandInterpreter> m_pCmdInter;
};


TEST_F(Test_CommandInterpreter, DISABLED_construct)
{
}

}   // unnamed namespace
