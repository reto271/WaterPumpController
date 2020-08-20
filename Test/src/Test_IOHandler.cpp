#include "Test_IOHandler.hpp"

#include <gtest/gtest.h>
#include <stdint.h>

#include "Application/IOHandler.hpp"

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



class Test_IOHandler : public testing::Test, public IOHandler
{
protected:
    void SetUp() override
    {
        // srand(time(NULL));
    }

    void TearDown() override
    {
    }

    void initializeArrayAlternating()
    {
        // Initialize arrays
        bool val = false;
        for(uint16_t sigCnt = 0; sigCnt < NR_SIGNALS_TO_DEBOUNCE; sigCnt++) {
            m_debouncedSignals[sigCnt] = 0;
            for(uint16_t sampleCnt = 0; sampleCnt < DEBOUNCE_ARRAY_SIZE; sampleCnt++) {
                m_debounceArray[sigCnt][sampleCnt] = val;
                val = !val;
            }
        }
    }

    void initializeArraySameValus()
    {
        bool val = false;
        for(uint16_t sampleCnt = 0; sampleCnt < DEBOUNCE_ARRAY_SIZE; sampleCnt++) {
            for(uint16_t sigCnt = 0; sigCnt < NR_SIGNALS_TO_DEBOUNCE; sigCnt++) {
                m_debouncedSignals[sigCnt] = 0;
                m_debounceArray[sigCnt][sampleCnt] = val;
                val = !val;
            }
        }
    }

    void initializeArrayAllOne()
    {
        for(uint16_t sampleCnt = 0; sampleCnt < DEBOUNCE_ARRAY_SIZE; sampleCnt++) {
            for(uint16_t sigCnt = 0; sigCnt < NR_SIGNALS_TO_DEBOUNCE; sigCnt++) {
                m_debouncedSignals[sigCnt] = 0;
                m_debounceArray[sigCnt][sampleCnt] = true;
            }
        }
    }

};



TEST_F(Test_IOHandler, initializationOrder)
{
    // Initialize arrays
    initializeArrayAlternating();

    // Test value as single dimension array
    bool val = false;
    bool* pSingleDimArray = reinterpret_cast<bool*>(m_debounceArray);
    for(uint16_t valCnt = 0; valCnt < DEBOUNCE_ARRAY_SIZE * NR_SIGNALS_TO_DEBOUNCE; valCnt++) {
        EXPECT_EQ(val, *pSingleDimArray);
        // std::cout << "Array value: " << *pSingleDimArray << ", @ " << pSingleDimArray << std::endl;
        pSingleDimArray++;
        val = !val;
    }
}

TEST_F(Test_IOHandler, initializationOrder2)
{
    // Initialize arrays
    initializeArraySameValus();

    bool* pSingleDimArray = reinterpret_cast<bool*>(m_debounceArray);
    // std::cout << "Single arr(p1): 0x" << std::hex << pSingleDimArray << std::dec << std::endl;
    for(uint16_t valCnt = 0; valCnt < DEBOUNCE_ARRAY_SIZE; valCnt++) {
        EXPECT_EQ(false, *pSingleDimArray);
        // std::cout << "Array value: " << *pSingleDimArray << ", @ " << pSingleDimArray << std::endl;
        pSingleDimArray++;
    }


    pSingleDimArray = reinterpret_cast<bool*>(m_debounceArray) + 5 * sizeof(bool);
    // std::cout << "Single arr(p2): 0x" << std::hex << pSingleDimArray << std::dec << std::endl;
    for(uint16_t valCnt = 0; valCnt < DEBOUNCE_ARRAY_SIZE; valCnt++) {
        EXPECT_EQ(true, *pSingleDimArray);
        // std::cout << "Array value: " << *pSingleDimArray << ", @ " << pSingleDimArray << std::endl;
        pSingleDimArray++;
    }
}

TEST_F(Test_IOHandler, debounce01)
{
    // Initialize arrays
    initializeArraySameValus();

    this->run();
    EXPECT_EQ(false, this->m_debouncedSignals[0]);
    EXPECT_EQ(true, this->m_debouncedSignals[1]);
}

TEST_F(Test_IOHandler, debounce02)
{
    // Initialize arrays
    initializeArrayAlternating();

    this->run();
    EXPECT_EQ(false, this->m_debouncedSignals[0]);
    EXPECT_EQ(false, this->m_debouncedSignals[1]);
}

TEST_F(Test_IOHandler, debounce03)
{
    // Initialize arrays
    initializeArrayAllOne();

    this->run();
    EXPECT_EQ(true, this->m_debouncedSignals[0]);
    EXPECT_EQ(true, this->m_debouncedSignals[1]);
}

}  // unnamed namespace
