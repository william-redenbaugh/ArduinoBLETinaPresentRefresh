// Arduino and mbed libaries. 
#include <Arduino.h>
#include <mbed.h>
#include "platform/Callback.h"
#include "events/EventQueue.h"
#include "platform/NonCopyable.h"
#include "rtos.h"

// All the stuff required to control our mic reading stuff
#include "mic_read_runtime.hpp"

// All the stuff required to control our sensor reading stuff
#include "SensorReadThread.hpp"

using namespace sense_read;

/*!
* @brief Copy of mic data. 
*/
short *mic_data; 

/*!
* @brief Getting the densor data.  
*/
SensorReadThread sensors; 


void setup() {
  // Setup the serial interface. 
  Serial.begin(9600);
  delay(3000);

  // Gets a pointer to the microphone data. 
  mic_data = get_latest_microphone_data(); 

  // Reads the data from our microphones. 
  start_sensor_read_runtime();
  sensors.begin(); 

}

void loop() {
  rtos::ThisThread::sleep_for(15); 
}