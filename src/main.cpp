// Arduino and mbed libaries. 
#include <Arduino.h>
#include <mbed.h>
#include "platform/Callback.h"
#include "events/EventQueue.h"
#include "platform/NonCopyable.h"
#include "rtos.h"

// Contains all of the stuff that allows our LED strips to work
#include "led_strip_runtime.hpp"

// All the stuff required to control our CharliePlex display
#include "charlieplex_runtime.hpp"

// All the stuff required to control our mic reading stuff
#include "mic_read_runtime.hpp"

// All the stuff required to control our sensor reading stuff
#include "SensorReadThread.hpp"

// All the stuff required to control our bluetooth communication
#include "bluetooth_runtime.hpp"

using namespace sense_read; 

/*!
* @brief Getting the densor data.  
*/
SensorReadThread sensors; 


void setup() {
  // Setup the serial interface. 
  Serial.begin(9600);
  delay(3000);

  sensors.begin(); 

  //start_sensor_read_runtime();
  start_led_strip_runtime(); 
}

void loop() {
  rtos::ThisThread::sleep_for(10); 
  sensors.acquire(); 
  AccelData dat = sensors.get_accel_data(); 
  sensors.release(); 

  Serial.print(dat.x); 
  Serial.print(" "); 
  Serial.print(dat.y); 
  Serial.print(" "); 
  Serial.println(dat.z); 

}