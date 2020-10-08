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

// All the stuff required to control our sensor reading stuff
#include "sensor_read_runtime.hpp"

// All the stuff required to control our bluetooth communication
#include "bluetooth_runtime.hpp"

void setup() {
  // Setup the serial interface. 
  Serial.begin(9600);

  start_led_strip_runtime(); 
  start_sensor_read_runtime(); 
  
}

void loop() {
  rtos::ThisThread::sleep_for(1000); 
}