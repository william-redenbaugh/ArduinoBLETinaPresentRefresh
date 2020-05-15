#ifndef _SENSOR_READ_THREAD_HPP
#define _SENSOR_READ_THREAD_HPP
// Arduino, mbed and rtos libraries. 
#include <Arduino.h>
#include <mbed.h>
#include "platform/Callback.h"
#include "events/EventQueue.h"
#include "platform/NonCopyable.h"
#include "rtos.h"

// Driver libraries for our different sesnsors. 
#include "Arduino_LSM9DS1.h"
#include "Arduino_LPS22HB.h"
#include "Arduino_HTS221.h"
#include "Arduino_APDS9960.h"
#include "PDM.h"

namespace sense_read{
    
/**************************************************************************/
/*!
    @brief Bitmask for easy enabling and disabling of our sensor
*/
/**************************************************************************/
enum SensorEnableBitmask{
    ENAB_BARO = 0b00000001,
    ENAB_MIC = 0b00000010, 
    ENAB_IMU = 0b00000100,
    ENAB_HTEMP = 0b00001000, 
    ENAB_PROX = 0b00010000
};

struct AccelData{
    float x, y, z; 
};

struct GyroData{
   float x, y, z;  
};

struct MagData{
    float x, y, z;
};

struct ColorData{
    int r, g, b;
};

struct GestureProxData{
    int gesture, proximity; 
};

struct TempHumData{
    float tempurature, humidity;
};

/**************************************************************************/
/*!
    @brief Constructor for thread that will periodically read all our sensors
*/
/**************************************************************************/
class SensorReadThread{
    public: 
        
        void init_sensors(void);
        void deinit_sensors(void);

        void init_thread(void);
        void deinit_thread(void);

        void set_enable(uint8_t bitmask);
        void set_thread_period_val(void);

        void _internal_thread_func(void);
    
    private: 
        // Private functions that aid in helping us read/filter data. 
        void read_pressure_sensor(void);
        void read_mic(void);
        void read_imu(void);
        void read_prox_color(void);
        void read_temp_humd(void);

        // Thread handler that we use to start and end our reading thread
        rtos::Thread thread_handler; 

        // Bitmask that tells us which sensors we enabled to read or not
        uint8_t enable_bitmask = 0b00000000;
        // Period in which we delay our program.
        uint16_t delay_ms = 100;
        
        // pressure data from our barometric pressure sensor. 
        float barometric_pressure = 0.0;

        // IMU data. 
        AccelData accel_data; 
        GyroData gyro_data; 
        MagData mag_data; 

        // Color data
        ColorData color_data; 
        // Gesture and proximity data
        GestureProxData gesture_prox_data; 

        // Tempurature and humidity data
        TempHumData temp_hum_data;  
};

}

#endif