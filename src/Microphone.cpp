#include "Microphone.hpp"

void mic::Microphone::begin(void){
    // Starting up the Microphone
    if(!PDM.begin(1, 16000)){
        Serial.println("Failed to start PDM :(");
        while(1)
            rtos::ThisThread::sleep_for(1000);
    }

     
}