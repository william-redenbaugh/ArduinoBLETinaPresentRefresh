#ifndef _LED_STRIP_RUNTIME_H
#define _LED_STRIP_RUNTIME_H

// Arduino and mbed libaries. 
#include <Arduino.h>
#include <mbed.h>
#include "platform/Callback.h"
#include "events/EventQueue.h"
#include "platform/NonCopyable.h"
#include "rtos.h"

#include "Adafruit_NeoPixel.h"
#include "hsv_rgb_conv.hpp"

void start_led_strip_runtime(uint8_t *fft_arr_ptr); 

#endif