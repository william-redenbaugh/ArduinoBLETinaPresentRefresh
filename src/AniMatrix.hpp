#ifndef _ANIMATRIX_HPP
#define _ANIMATRIX_HPP

// Including Arduino, mbed and rtos libraries
#include "Arduino.h"
#include "mbed.h"
#include "rtos.h"

// Including Adafruit GFX and CharliePlex Libraries. 
#include "Adafruit_GFX.h"
#include "Adafruit_IS31FL3731.h"

namespace AniMatrix{

/**************************************************************************/
/*!
    @brief Animation Handler that should make dealing with matrix animations easier and reliant on the rtos. 
*/
/**************************************************************************/
class MatrixAnimationHandler{
    public: 
        void begin(Adafruit_IS31FL3731 *matrix_ptr);
    private: 

        Adafruit_IS31FL3731 *matrix_ptr;
};

}

#endif 