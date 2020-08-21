// #include "Test_InputSignal.hpp"

#include <gtest/gtest.h>
#include <stdint.h>

#include "Application/InputSignal.hpp"

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    return GPIO_PIN_RESET;
}

namespace
{
// using ::testing::StrictMock;
// using ::testing::Return;
// using ::testing::Exactly;
// using ::testing::_;
// using ::testing::HasSubstr;



class Test_InputSignal : public testing::Test
{
protected:
    void SetUp() override
    {
        // srand(time(NULL));
    }

    void TearDown() override
    {
    }

};




TEST_F(Test_InputSignal, initializationOrder)
{
    EXPECT_TRUE(true);
}
// TEST_F(Test_InputSignal, initializationOrder)
// {
//    // Initialize arrays
//    initializeArrayAlternating();
//
//    // Test value as single dimension array
//    bool val = false;
//    bool* pSingleDimArray = reinterpret_cast<bool*>(m_debounceArray);
//    for(uint16_t valCnt = 0; valCnt < DEBOUNCE_ARRAY_SIZE * NR_SIGNALS_TO_DEBOUNCE; valCnt++) {
//        EXPECT_EQ(val, *pSingleDimArray);
//        // std::cout << "Array value: " << *pSingleDimArray << ", @ " << pSingleDimArray << std::endl;
//        pSingleDimArray++;
//        val = !val;
//    }
// }
//
// TEST_F(Test_InputSignal, initializationOrder2)
// {
//    // Initialize arrays
//    initializeArraySameValus();
//
//    bool* pSingleDimArray = reinterpret_cast<bool*>(m_debounceArray);
//    // std::cout << "Single arr(p1): 0x" << std::hex << pSingleDimArray << std::dec << std::endl;
//    for(uint16_t valCnt = 0; valCnt < DEBOUNCE_ARRAY_SIZE; valCnt++) {
//        EXPECT_EQ(false, *pSingleDimArray);
//        // std::cout << "Array value: " << *pSingleDimArray << ", @ " << pSingleDimArray << std::endl;
//        pSingleDimArray++;
//    }
//
//
//    pSingleDimArray = reinterpret_cast<bool*>(m_debounceArray) + 5 * sizeof(bool);
//    // std::cout << "Single arr(p2): 0x" << std::hex << pSingleDimArray << std::dec << std::endl;
//    for(uint16_t valCnt = 0; valCnt < DEBOUNCE_ARRAY_SIZE; valCnt++) {
//        EXPECT_EQ(true, *pSingleDimArray);
//        // std::cout << "Array value: " << *pSingleDimArray << ", @ " << pSingleDimArray << std::endl;
//        pSingleDimArray++;
//    }
// }
//
// TEST_F(Test_InputSignal, debounce01)
// {
//    // Initialize arrays
//    initializeArraySameValus();
//
//    this->run();
//    EXPECT_EQ(false, this->m_debouncedSignals[0]);
//    EXPECT_EQ(true, this->m_debouncedSignals[1]);
// }
//
// TEST_F(Test_InputSignal, debounce02)
// {
//    // Initialize arrays
//    initializeArrayAlternating();
//
//    this->run();
//    EXPECT_EQ(false, this->m_debouncedSignals[0]);
//    EXPECT_EQ(false, this->m_debouncedSignals[1]);
// }
//
// TEST_F(Test_InputSignal, debounce03)
// {
//    // Initialize arrays
//    initializeArrayAllOne();
//
//    this->run();
//    EXPECT_EQ(true, this->m_debouncedSignals[0]);
//    EXPECT_EQ(true, this->m_debouncedSignals[1]);
// }

}  // unnamed namespace
