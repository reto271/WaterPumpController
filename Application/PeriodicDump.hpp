#pragma once

#include <stdint.h>
#include "IPeriodicDump.hpp"

class IIOHandler;
class ITimerMgr;
class IDebugWriter;

class PeriodicDump : public IPeriodicDump
{
public:
    PeriodicDump(IIOHandler* pIOHandler, ITimerMgr* pTimerMgr, IDebugWriter* pDebugWriter);
    virtual ~PeriodicDump();

    void run() override;

protected:
    IIOHandler* m_pIOHandler;
    ITimerMgr* m_pTimerMgr;
    IDebugWriter* m_pDebugWriter;
};
