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


class Test_BitBuffer : public testing::Test, public IOHandler
{
protected:
    void SetUp() override
    {
        srand(time(NULL));
    }

    void TearDown() override
    {
        // Dump Trace buffer
    }

    void getRandomValueUnilimted(uint32_t& value, uint16_t& bitWidth)
    {
        // rand returns numbers 0 and RAND_MAX. -> it returns only 31 bit
        assert(RAND_MAX == 0x7fffffff); //
        bitWidth = (rand() % 32) + 1;
        value = (rand() << 1) ^ rand();   // exor two rand variables, shift one
        EXPECT_TRUE(0 < bitWidth);
        EXPECT_TRUE(32 >= bitWidth);
    }

    void getRandomValue(uint32_t& value, uint16_t& bitWidth)
    {
        uint32_t unlimitedVal;
        getRandomValueUnilimted(unlimitedVal, bitWidth);
        uint32_t bitMask = (0x1 << bitWidth) - 1;
        value = unlimitedVal & bitMask;
    }

    void getRandomValue(int32_t& value, uint16_t& bitWidth)
    {
        uint32_t u32value;
        uint32_t bitMask = 0;

        getRandomValue(u32value, bitWidth);
        if(bitWidth == 1) {
            bitWidth++;
        }

        // Expand sign - prepare range check for signed values, not the smartest implementation
        //  but it shall be different from the active code.
        for(uint32_t cnt = 0; cnt < static_cast<uint32_t>(bitWidth - 1); cnt++) {
            bitMask |= (0x1 << cnt);
        }
        if(0 == (0x80000000 & u32value)) {
            // Positive values
            u32value &= bitMask;
        } else {
            // Negative values
            u32value |= (~bitMask);
        }
        value = *reinterpret_cast<int32_t*>(&u32value);
    }

    void testSingleUnsignedValue(uint32_t oriValue, uint8_t nrBits)
    {
//        uint32_t testValue;
//        this->appendValue(oriValue, nrBits);
//        this->getValue(testValue, nrBits);
//        EXPECT_EQ(oriValue, testValue);
    }

    void testSingleSignedValue(int32_t oriValue, uint8_t nrBits)
    {
//        int32_t testValue;
//        this->appendValue(oriValue, nrBits);
//        this->getValue(testValue, nrBits);
//        EXPECT_EQ(oriValue, testValue);
    }

};


TEST_F(Test_BitBuffer, dummy1)
{
    EXPECT_EQ(true, true);
}

TEST_F(Test_BitBuffer, dummy2)
{
    EXPECT_EQ(false, false);
}

TEST_F(Test_BitBuffer, dummy3)
{
    EXPECT_EQ(true, false);
}


//TEST_F(Test_BitBuffer, clearAll32bits)
//{
//    uint32_t value;
//
//    this->appendValue(static_cast<uint32_t>(0), 32);
//
//    this->restartReading();
//    this->getValue(value, 32);
//
//    EXPECT_EQ(0, value);
//}


}  // unnamed namespace
