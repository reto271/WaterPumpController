#pragma once

#include <stdint.h>

class BCD_Time;

/// \brief Very primitive replacement for the stdio printf implementation.
/// There is very little FLASH memory on the used uP. The persistent memory
///  is not sufficiently large to link stdio lib. This class implements a
///  very simple and slim printf implementation
/// \remark The characters are printed in busy waiting.
class IDebugWriter
{
public:
    /// Prints a given text with a given length.
    /// \param[in] pData string to be printed, no necessary 0 terminated.
    /// \param[in] len length of the buffer to be printed.
    /// \return true if the buffer is printed, false if printing is rejected.
    virtual bool print(char const* pData, uint8_t len) = 0;

    /// Prints a given text with a given length.
    /// \param[in] pData string to be printed, no necessary 0 terminated.
    /// \param[in] len length of the buffer to be printed.
    /// \param[in] pBCD_Time time in BCD format to be printed before the buffer.
    /// \return true if the buffer is printed, false if printing is rejected.
    virtual bool print(char const* pData, uint8_t len, BCD_Time* pBCD_Time) = 0;
};
