#include "BCD_Time.hpp"

BCD_Time::BCD_Time()
{
    for(uint8_t cnt = 0; cnt < NR_DIGITS; cnt++) {
        sec[cnt] = 0;
    }
}

BCD_Time::~BCD_Time()
{
}

void BCD_Time::incrementSecond()
{
    sec[0]++;
    for(uint8_t cnt = 0; cnt < NR_DIGITS; cnt++) {
        if(sec[cnt] > 9) {
            sec[cnt] = 0;
            if(cnt < NR_DIGITS - 1) {
                sec[cnt + 1]++;
            }
        }
    }
}
