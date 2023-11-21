#ifndef __ANALOG_PIN_H
#define  __ANALOG_PIN_H
#include <stdint.h>
#include "bitmacros.h"

// Ntc class {
//  float celsius = 1 / (log(1 / (1023. / value - 1)) / BETA + 1.0 / 298.15) - 273.15;
//}


class AnalogPin{
public:
    AnalogPin(unsigned char pinNumber):
        pinNumber(pinNumber){
            BIT_CLEAR(DDRC,pinNumber);            
        }
        uint16_t analogRead();
private:    
    unsigned char pinNumber;
};

#endif // __ANALOG_PIN_H