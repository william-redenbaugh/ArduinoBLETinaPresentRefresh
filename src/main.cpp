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

// Arduino FFT handler code that computes all the fft stuff!
#include "arduinoFFT.h"

using namespace sense_read; 

/*!
* @brief Getting the densor data.  
*/
SensorReadThread sensors; 

/*!
* @brief Arduino FFT handler. 
*/

arduinoFFT FFT = arduinoFFT();

/*!
* @brief Number of samples we are reading for our FFT stuff
*/
#define SAMPLES 64            

/*!
* @brief Arrays that help us computer FFT
*/
double vReal[SAMPLES];
double vImag[SAMPLES];

/*!
* @brief Helps us manage decrementing our FFT animation array
*/
volatile int decrement_counter = 0;

/*!
* @brief Arrray that holds our animated FFT data. 
*/
static uint8_t intensity_arr[SAMPLES]; 

/*!
* @brief Array pointer to the microphone data. 
*/
static short *mic_data; 

/*!
* @brief Function declarations
*/
static inline void compute_fft(void); 
static inline void peak_finding(void); 

void setup() {
  // Setup the serial interface. 
  Serial.begin(9600);
  delay(3000);

  // Gets a pointer to the microphone data. 
  mic_data = get_latest_microphone_data(); 

  // Reads the data from our microphones. 
  start_sensor_read_runtime();
  start_led_strip_runtime(intensity_arr); 
  start_charliexplex_runtime(intensity_arr);
}

/*!
* @brief FFT computations
*/
static inline void compute_fft(void){
  // ++ Sampling
  for(int i=0; i<SAMPLES; i++){
      vReal[i]= mic_data[i]/2;                      // Copy to bins after compressing
      vImag[i] = 0;                         
  }

  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
}

/*!
* @brief Peak finding computations
*/
static inline void peak_finding(void){
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
}

void loop() {
  compute_fft(); 
  peak_finding(); 

  rtos::ThisThread::sleep_for(15); 
}