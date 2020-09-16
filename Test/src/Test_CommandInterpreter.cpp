#if 0
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
    }

    void TearDown() override
    {
    }

//    StrictMock<MockCommandInterpreter> mockIOHdl;
};


TEST_F(Test_CommandInterpreter, construct)
{

}
#endif
