#ifndef _MICROPHONE_HPP
#define _MICROPHONE_HPP

#include "Arduino.h"
#include "PDM.h"

// Microphone stuff. 
namespace mic{
class Microphone{
    public: 
        void begin(void);

    private: 

        uint16_t sample_buffer[256];
        volatile int samples_read;
        int bytes_avaiable;
};

}

#endif 