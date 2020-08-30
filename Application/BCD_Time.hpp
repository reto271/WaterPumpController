#pragma once

#include <stdint.h>

/// \brief Stores a time in BCD format.
/// Is a crude and simple way to store the current application time and
///  print it. (There is not enough flash memory to use printf("%d").
class BCD_Time
{
public:
    /// Constructs a BCD_Time object and initializes the time as 0.
    BCD_Time();

    /// Destructor of the BCD time object.
    virtual ~BCD_Time();

    /// Increments the time in BCD format by 1s.
    void incrementSecond();

    /// Number of BCD 'digits' the object stores.
    static const uint8_t NR_DIGITS = 8;

    /// Current time in BCD format. Array index 0 stores 10^0. Array
    /// index 1 stores 10^1 and so on.
    uint8_t sec[8];
};
