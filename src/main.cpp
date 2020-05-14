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
#include "rtos.h"
// If you're using the wing version
Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731_Wing();
rtos::Thread animation_thread; 

volatile int gesture;
volatile bool animation = false; 

void animation_thread_func(void);

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
  animation_thread.start(animation_thread_func);
}

void animation_thread_func(void){
  while(1){
  if(animation){
    switch (gesture) {
      case GESTURE_UP:
      {
        for(uint8_t x = 16; x > 0; x--){
          matrix.displayFrame(1);

          matrix.setFrame(0);
          for(uint8_t y = 0; y < 8; y++){
            matrix.drawPixel(x, y, 50);
          }
          matrix.displayFrame(0);
          matrix.setFrame(1);
          for(uint8_t y = 0; y < 8; y++){
            matrix.drawPixel(x, y, 50);
          }
          rtos::Thread::wait(10);
        }

        for(uint8_t x = 16; x > 0; x--){
          matrix.displayFrame(1);

          matrix.setFrame(0);
          for(uint8_t y = 0; y < 8; y++){
            matrix.drawPixel(x, y, 0);
          }
          matrix.displayFrame(0);
          matrix.setFrame(1);
          for(uint8_t y = 0; y < 8; y++){
            matrix.drawPixel(x, y, 0);
          }
          rtos::Thread::wait(10);
        }
      }
        break;

      case GESTURE_DOWN:
        for(uint8_t x = 0; x < 16; x++){
          matrix.displayFrame(1);

          matrix.setFrame(0);
          for(uint8_t y = 0; y < 8; y++){
            matrix.drawPixel(x, y, 50);
          }
          matrix.displayFrame(0);
          matrix.setFrame(1);
          for(uint8_t y = 0; y < 8; y++){
            matrix.drawPixel(x, y, 50);
          }
          rtos::Thread::wait(10);
        }

        for(uint8_t x = 0; x < 16; x++){
          matrix.displayFrame(1);

          matrix.setFrame(0);
          for(uint8_t y = 0; y < 8; y++){
            matrix.drawPixel(x, y, 0);
          }
          matrix.displayFrame(0);
          matrix.setFrame(1);
          for(uint8_t y = 0; y < 8; y++){
            matrix.drawPixel(x, y, 0);
          }
          rtos::Thread::wait(10);
        }
        break;

      case GESTURE_LEFT:
        for(uint8_t y = 0; y < 8; y++){
          matrix.displayFrame(1);

          matrix.setFrame(0);
          for(uint8_t x = 0; x < 16; x++){
            matrix.drawPixel(x, y, 50);
          }
          matrix.displayFrame(0);
          matrix.setFrame(1);
          for(uint8_t x = 0; x < 16; x++){
            matrix.drawPixel(x, y, 50);
          }
          rtos::Thread::wait(20);
        }

        for(uint8_t y = 0; y < 8; y++){
          matrix.displayFrame(1);

          matrix.setFrame(0);
          for(uint8_t x = 0; x < 16; x++){
            matrix.drawPixel(x, y, 0);
          }
          matrix.displayFrame(0);
          matrix.setFrame(1);
          for(uint8_t x = 0; x < 16; x++){
            matrix.drawPixel(x, y, 0);
          }
          rtos::Thread::wait(20);
        }
        break;

      case GESTURE_RIGHT:
        for(uint8_t y = 8; y > 0; y--){
          matrix.displayFrame(1);

          matrix.setFrame(0);
          for(uint8_t x = 0; x < 16; x++){
            matrix.drawPixel(x, y, 50);
          }
          matrix.displayFrame(0);
          matrix.setFrame(1);
          for(uint8_t x = 0; x < 16; x++){
            matrix.drawPixel(x, y, 50);
          }
          rtos::Thread::wait(20);
        }

        for(uint8_t y = 8; y > 0; y--){
          matrix.displayFrame(1);

          matrix.setFrame(0);
          for(uint8_t x = 0; x < 16; x++){
            matrix.drawPixel(x, y, 0);
          }
          matrix.displayFrame(0);
          matrix.setFrame(1);
          for(uint8_t x = 0; x < 16; x++){
            matrix.drawPixel(x, y, 0);
          }
          rtos::Thread::wait(20);
        }
        break;

      default:
        // ignore
        break;
    }
    animation = false; 
  }
  rtos::Thread::wait(100);
  }
}

void loop() {
 if (APDS.gestureAvailable()) {
    // a gesture was detected, read and print to serial monitor
   gesture = APDS.readGesture();
   animation = true; 
 }

 rtos::Thread::wait(100);
}