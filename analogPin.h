#ifndef __ANALOG_PIN_H
#define  __ANALOG_PIN_H
#include <stdint.h>
#include <math.h>
#include "bitmacros.h"

//1. Tips "lottery"
    // Company A buys 5000 lottery tickets 0-4999
    // Company B buys 3000 lottery tickets 5000-7999
    // Company C buys 1000 lottery tickets 8000-8999

    //0 - 8999


//2. Rest of the day - get going with Assigmnent  Embedded system
//                      I help you  get going

//3. The one who wants: I'll do Ntc class in 10 minutes!

// 4. SUPPORT!!! 



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


class Ntc {
public:
    Ntc(AnalogPin pin):pin(pin)
    {}

    float getTemp(){
        uint16_t value = pin.analogRead();
        float celsius = 1 / (log(1 / (1023. / value - 1)) / BETA + 1.0 / 298.15) - 273.15;
        return celsius;
    }
private:
    const float BETA = 3950;
    AnalogPin pin;
};

#endif // __ANALOG_PIN_H