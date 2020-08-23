#pragma once

class IIOHandler;

class PumpController {
public:
    PumpController(IIOHandler* pIOHandler);
    virtual ~PumpController();

    void run();

private:
    enum class PumpState {
        On,
        Off,
        OffByTimeout
    };

    PumpController();

    IIOHandler* m_pIOHandler;
    PumpState m_pumpState;
};
