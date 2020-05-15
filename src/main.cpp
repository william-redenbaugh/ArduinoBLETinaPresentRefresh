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

// Driver librarie for all our different hardware peripherals. 
#include "Adafruit_IS31FL3731.h"
#include "AniMatrix.hpp"

#include "LSM9DS1.h"
#include "BARO.h"
#include "HTS.h"
#include "PDM.h"
#include "Arduino_APDS9960.h"

// If you're using the wing version
Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731_Wing();

void setup() {
  // Setup the serial interface. 
  Serial.begin(9600);

  // Setting up the charlieplex led matrix
  if(!matrix.begin()){
    Serial.println("CharliePlex Matrix not found");
    while(1) 
      delay(1000);
  }

}

void loop() {
  // Currenting doing nothing, other than waking up every second...
 rtos::Thread::wait(1000);
}