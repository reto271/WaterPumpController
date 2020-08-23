#pragma once

class IInputSignal
{
public:
    virtual void sampleInput() = 0;
    virtual bool getState() = 0;
};
