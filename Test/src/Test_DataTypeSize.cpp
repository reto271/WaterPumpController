#include <gtest/gtest.h>
#include <stdint.h>

#include "Application/IOHandler.hpp"

namespace
{
// using ::testing::StrictMock;
// using ::testing::Return;
// using ::testing::Exactly;
// using ::testing::_;
// using ::testing::HasSubstr;


class Test_DataTypeSize : public testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

};


TEST_F(Test_DataTypeSize, trivialTypes)
{
    EXPECT_EQ(1, sizeof(bool));

    EXPECT_EQ(1, sizeof(char));
    EXPECT_EQ(2, sizeof(short));
    EXPECT_EQ(4, sizeof(int));

    EXPECT_EQ(1, sizeof(unsigned char));
    EXPECT_EQ(2, sizeof(unsigned short));
    EXPECT_EQ(4, sizeof(unsigned int));

    EXPECT_EQ(1, sizeof(int8_t));
    EXPECT_EQ(2, sizeof(int16_t));
    EXPECT_EQ(4, sizeof(int32_t));
    EXPECT_EQ(8, sizeof(int64_t));

    EXPECT_EQ(1, sizeof(uint8_t));
    EXPECT_EQ(2, sizeof(uint16_t));
    EXPECT_EQ(4, sizeof(uint32_t));
    EXPECT_EQ(8, sizeof(uint64_t));
}

TEST_F(Test_DataTypeSize, DISABLED_longTypes)
{
    // Test does not work on build server (Raspi). Long is only 4Bytes. -> Fix the test later
    EXPECT_EQ(8, sizeof(long));
    EXPECT_EQ(8, sizeof(unsigned long));
}
// TEST_F(Test_DataTypeSize, customTypes)
// {
//    EXPECT_EQ(2, sizeof(m_debouncedSignals));
//    EXPECT_EQ(10, sizeof(m_debounceArray));
// }

}  // unnamed namespace
