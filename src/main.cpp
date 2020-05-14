// Arduino and mbed libaries. 
#include <Arduino.h>
#include <mbed.h>
#include "platform/Callback.h"
#include "events/EventQueue.h"
#include "platform/NonCopyable.h"
#include "rtos.h"

// Bluetooth libraries. 
#include "ble/BLE.h"
#include "ble/GattServer.h"
#include "BluetoothStatus.hpp"

// Driver libraries for all our different hardware peripherals. 
#include "Adafruit_IS31FL3731.h"
#include "Arduino_LSM9DS1.h"
#include "Arduino_LPS22HB.h"
#include "Arduino_HTS221.h"
#include "Arduino_APDS9960.h"
#include "PDM.h"
#include "SensorReadThread.hpp"

// If you're using the wing version
Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731_Wing();

SensorReadThread sensor_thread_handler;

void setup() {
  // Setup the serial interface. 
  Serial.begin(9600);

  // Setting up the charlieplex led matrix
  if(!matrix.begin()){
    Serial.println("CharliePlex Matrix not found");
    while(1) 
      delay(1000);
  }

  // Setting up our sensor read handler. 
  sensor_thread_handler.init_sensors();
  sensor_thread_handler.set_enable(0);
  sensor_thread_handler.init_thread();
}

void loop() {
  // Currenting doing nothing, other than waking up every second...
 rtos::Thread::wait(osWaitForever);
}