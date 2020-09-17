#include "CommandInterpreter.hpp"

#include "PeriodicDump.hpp"
#include "UART_miniDriver.hpp"

CommandInterpreter::CommandInterpreter(UART_HandleTypeDef* pUART_Hdl, IPeriodicDump* pPeriodicDump)
    : m_pUART_Hdl(pUART_Hdl)
    , m_pPeriodicDump(pPeriodicDump)
{
}

CommandInterpreter::~CommandInterpreter()
{
}

void CommandInterpreter::pollUART()
{
#if !defined(_UNIT_TESTS_)
    uint8_t data;
    HAL_StatusTypeDef status = HAL_UART_Receive_rdu(m_pUART_Hdl, &data);

    if(HAL_OK == status) {
        if(data == 'd') {
            m_pPeriodicDump->dumpInfo();
        }
    }
#endif  // _UNIT_TESTS_
}
