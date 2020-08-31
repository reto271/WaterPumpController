#pragma once

/// Debounces a physical digital input signal and transforms it to a logical
/// input signal.
class IInputSignal
{
public:
    /// Samples the digital input.
    /// \remark Shall be called every 10ms.
    virtual void sampleInput() = 0;

    /// Returns the locgical state of an input signal.
    /// \return true if the logical state of the signal is on, true, active, ...
    virtual bool getState() = 0;
};
