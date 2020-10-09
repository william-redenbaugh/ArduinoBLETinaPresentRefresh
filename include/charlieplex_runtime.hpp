#ifndef _CHARLIEPLEX_RUNTIME_H
#define _CHARLIEPLEX_RUNTIME_H

// Arduino and mbed libaries. 
#include <Arduino.h>
#include <mbed.h>
#include "platform/Callback.h"
#include "events/EventQueue.h"
#include "platform/NonCopyable.h"
#include "rtos.h"

// Driver libraries for controlling our charlieplex matrix display
#include "Adafruit_IS31FL3731.h"

void start_charliexplex_runtime(uint8_t *fft_arr); 

#endif