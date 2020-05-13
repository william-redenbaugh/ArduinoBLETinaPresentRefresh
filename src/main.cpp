#include <Arduino.h>
#include <mbed.h>
#include "platform/Callback.h"
#include "events/EventQueue.h"
#include "platform/NonCopyable.h"

#include "ble/BLE.h"
#include "ble/GattServer.h"
#include "Adafruit_IS31FL3731.h"
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
  
  // Setting up the promixity and color sensor
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
    while(1)
      delay(1000);
  }

  // Setting up the barometrix pressure sensor. 
  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1){
      delay(1000);
    }
  }

  // Setting up our 9dof imu!
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  wait(1);
}