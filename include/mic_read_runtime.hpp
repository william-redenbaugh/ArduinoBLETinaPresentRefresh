#ifndef  _SENSOR_READ_RUNTIME_H
#define _SENSOR_READ_RUNTIME_H

// Arduino and mbed libaries. 
#include <Arduino.h>
#include <mbed.h>
#include "platform/Callback.h"
#include "events/EventQueue.h"
#include "platform/NonCopyable.h"
#include "rtos.h"

#include "LSM9DS1.h"
#include "BARO.h"
#include "HTS.h"
#include "PDM.h"
#include "Arduino_APDS9960.h"

void start_sensor_read_runtime(void); 

short* get_latest_microphone_data(void); 

#endif 