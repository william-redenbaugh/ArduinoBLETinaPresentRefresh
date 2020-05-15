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

enum Animation{
    NONE = 0, 
    SWIPE_LEFT = 1, 
    SWIPE_RIGHT = 2, 
    SWIPE_UP = 3,
    SWIPE_DOWN = 4
};

const uint32_t animation_flag = 0x1;
const uint32_t animation_complete_flag = 0x2;

/**************************************************************************/
/*!
    @brief Animation Handler that should make dealing with matrix animations easier and reliant on the rtos. 
*/
/**************************************************************************/
class MatrixAnimationHandler{
    public: 
        void begin(Adafruit_IS31FL3731 *matrix_ptr);
        
        bool set_next_animation(uint16_t next_ani);
        bool wait_animation_end(void);

        void _run(void);
    private: 
        // Pointer to the matrix driver. 
        Adafruit_IS31FL3731 *matrix_ptr;

        // Thread handler
        rtos::Thread animation_thread; 

        // We grab onto this mutex everytime an animation happens. 
        rtos::Mutex animation_mutex;
        volatile uint16_t next_animation; 
        volatile bool animation_complete = true; 
};

}

#endif 