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

#include "arduinoFFT.h"

using namespace sense_read; 

/*!
* @brief Getting the densor data.  
*/
SensorReadThread sensors; 

arduinoFFT FFT = arduinoFFT();
#define SAMPLES 64            //Must be a power of 2
double vReal[SAMPLES];
double vImag[SAMPLES];
volatile int decrement_counter = 0;
static uint8_t intensity_arr[SAMPLES]; 

void setup() {
  // Setup the serial interface. 
  Serial.begin(9600);
  delay(3000);

  start_sensor_read_runtime();
  start_led_strip_runtime(intensity_arr); 
  start_charliexplex_runtime(intensity_arr);
}

void loop() {
  short *arr = get_latest_microphone_data(); 
  // ++ Sampling
  for(int i=0; i<SAMPLES; i++){
      vReal[i]= arr[i]/2;                      // Copy to bins after compressing
      vImag[i] = 0;                         
  }

  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  // Find peaks
  for(int n = 0; n < 64; n++){
      int h = abs(vReal[n + 8]); 
      if(h > 255)
          h = 255; 
      if(intensity_arr[n] < h)
          intensity_arr[n] = h; 
  }

  decrement_counter++; 
  if(decrement_counter == 1){
    for(int n = 0; n < 64; n++){
      if(intensity_arr[n] >= 20)
          intensity_arr[n] -= 20; 
      else
        intensity_arr[n] = 0; 
    }
    decrement_counter = 0; 
  }

  rtos::ThisThread::sleep_for(15); 
}