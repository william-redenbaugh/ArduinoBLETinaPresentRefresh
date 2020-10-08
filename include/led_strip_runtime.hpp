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

void start_led_strip_runtime(void); 

#endif