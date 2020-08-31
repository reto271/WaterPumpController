#pragma once

#include <stdint.h>
#include "IPeriodicDump.hpp"

class IIOHandler;
class ITimerMgr;
class IDebugWriter;

/// \brief Periodically dumps some information on the debug channel.
class PeriodicDump : public IPeriodicDump
{
public:
    /// Creates the periodic dump object.
    /// \param[in] pIOHandler reference to the IO handler, to get input states
    /// \param[in] pTimerMgr reference to timer manager, to the current time (binary and BCD)
    /// \param[in] pDebugWriter reference to the debug writer, to dump the data
    PeriodicDump(IIOHandler* pIOHandler, ITimerMgr* pTimerMgr, IDebugWriter* pDebugWriter);

    /// Destructs the periodic dump object.
    virtual ~PeriodicDump();

    void run() override;

protected:
    /// Reference to the IO handler, to get input states
    IIOHandler* m_pIOHandler;

    /// Reference to timer manager, to the current time (binary and BCD)
    ITimerMgr* m_pTimerMgr;

    /// Reference to the debug writer, to dump the data
    IDebugWriter* m_pDebugWriter;
};
