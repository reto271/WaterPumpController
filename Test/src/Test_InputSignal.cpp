#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdint.h>

#include "Application/InputSignal.hpp"

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


using ::testing::StrictMock;
using ::testing::Return;
// using ::testing::Exactly;
using ::testing::_;
// using ::testing::HasSubstr;

class Mock_HAL_GPIO
{
public:
    virtual ~Mock_HAL_GPIO()
    {
    }

    MOCK_METHOD(GPIO_PinState, HAL_GPIO_ReadPin_xxx, (GPIO_TypeDef*, uint16_t));
};

class Test_InputSignal : public testing::Test
{
protected:
    Test_InputSignal()
    {
        m_gpioMock.reset(new StrictMock<Mock_HAL_GPIO>());
    }

    virtual ~Test_InputSignal()
    {
        m_gpioMock.reset();
    }

    void SetUp() override
    {
        // srand(time(NULL));
    }

    void TearDown() override
    {
    }

    std::shared_ptr<InputSignal> m_input;

public:
    static std::unique_ptr<StrictMock<Mock_HAL_GPIO> > m_gpioMock;
};

std::unique_ptr<StrictMock<Mock_HAL_GPIO> > Test_InputSignal::m_gpioMock;

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    return Test_InputSignal::m_gpioMock->HAL_GPIO_ReadPin_xxx(GPIOx, GPIO_Pin);
}

TEST_F(Test_InputSignal, initializationFalseNoninverting)
{
    m_input = std::make_shared<InputSignal>(nullptr, 0, false, false);
    EXPECT_FALSE(m_input->getState());
}

TEST_F(Test_InputSignal, initializationTrueNoninverting)
{
    m_input = std::make_shared<InputSignal>(nullptr, 0, true, false);
    EXPECT_TRUE(m_input->getState());
}

TEST_F(Test_InputSignal, initializationFalseInverting)
{
    m_input = std::make_shared<InputSignal>(nullptr, 0, false, true);
    EXPECT_FALSE(m_input->getState());
}

TEST_F(Test_InputSignal, initializationTrueInverting)
{
    m_input = std::make_shared<InputSignal>(nullptr, 0, true, true);
    EXPECT_TRUE(m_input->getState());
}

TEST_F(Test_InputSignal, initFalseNoninverting_transient)
{
    m_input = std::make_shared<InputSignal>(nullptr, 0, false, false);

    EXPECT_CALL(*m_gpioMock, HAL_GPIO_ReadPin_xxx(nullptr, 0)).Times(5).WillRepeatedly(Return(GPIO_PIN_RESET));
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());

    EXPECT_CALL(*m_gpioMock, HAL_GPIO_ReadPin_xxx(nullptr, 0)).Times(5).WillRepeatedly(Return(GPIO_PIN_SET));
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
}

TEST_F(Test_InputSignal, initTrueNoninverting_transient)
{
    m_input = std::make_shared<InputSignal>(nullptr, 0, true, false);

    EXPECT_CALL(*m_gpioMock, HAL_GPIO_ReadPin_xxx(_, _)).Times(5).WillRepeatedly(Return(GPIO_PIN_SET));
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());

    EXPECT_CALL(*m_gpioMock, HAL_GPIO_ReadPin_xxx(_, _)).Times(5).WillRepeatedly(Return(GPIO_PIN_RESET));
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
}

TEST_F(Test_InputSignal, initFalseInverting_transient)
{
    m_input = std::make_shared<InputSignal>(nullptr, 0, false, true);

    EXPECT_CALL(*m_gpioMock, HAL_GPIO_ReadPin_xxx(_, _)).Times(5).WillRepeatedly(Return(GPIO_PIN_SET));
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());

    EXPECT_CALL(*m_gpioMock, HAL_GPIO_ReadPin_xxx(_, _)).Times(5).WillRepeatedly(Return(GPIO_PIN_RESET));
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
}

TEST_F(Test_InputSignal, initTrueInverting_transient)
{
    m_input = std::make_shared<InputSignal>(nullptr, 0, true, true);

    EXPECT_CALL(*m_gpioMock, HAL_GPIO_ReadPin_xxx(_, _)).Times(5).WillRepeatedly(Return(GPIO_PIN_RESET));
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());

    EXPECT_CALL(*m_gpioMock, HAL_GPIO_ReadPin_xxx(_, _)).Times(5).WillRepeatedly(Return(GPIO_PIN_SET));
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_TRUE(m_input->getState());
    m_input->sampleInput();
    EXPECT_FALSE(m_input->getState());
}
