#include "SensorReadThread.hpp"

void sensor_read_thread(sense_read::SensorReadThread *self_thread){
    while(1){
        // just calls this function periodically
        self_thread->_internal_thread_func();
    }
}

/**************************************************************************/
/*!
    @brief Sets up all of our sensors on our Nano 33 BLE board. 
*/
/**************************************************************************/
void sense_read::SensorReadThread::init_sensors(void){
    // Setting up the promixity and color sensor
    if (!APDS.begin()) {
        Serial.println("Error initializing APDS9960 sensor!");
        while(1)
            rtos::Thread::wait(1000);
    }

    // Setting up the barometrix pressure sensor. 
    if (!BARO.begin()) {
        Serial.println("Failed to initialize pressure sensor!");
        while (1)
            rtos::Thread::wait(1000);
    }
 
    // Setting up our 9dof imu!
    if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU!");
        while (1)
            rtos::Thread::wait(1000);
    }

    // Setting up our tempurature and humidity sensor.
    if(!HTS.begin()){
        Serial.println("Failed to initialize our Tempurature and Humidity Sensor");
        while(1)
            rtos::Thread::wait(1000);
    }

    if(!PDM.begin(1, 16000)){
        Serial.println("Failed to start PDM :(");
        while(1)
            rtos::Thread::wait(1000);
    }
}

/**************************************************************************/
/*!
    @brief method that allows us to un initialize all of our sensors!
*/
/**************************************************************************/
void sense_read::SensorReadThread::deinit_sensors(void){
    BARO.end();
    IMU.end();
    PDM.end();
    HTS.end();
    APDS.end();
}

/**************************************************************************/
/*!
    @brief method that starts up our sensor read thread. 
*/
/**************************************************************************/
void sense_read::SensorReadThread::init_thread(void){
    this->thread_handler.start(sensor_read_thread, this);
}

/**************************************************************************/
/*!
    @brief method that allows us to stop and deconstruct our thread.
*/
/**************************************************************************/
void sense_read::SensorReadThread::deinit_thread(void){
    this->thread_handler.terminate();
}

/**************************************************************************/
/*!
    @brief Allows us to decide which sensors we are reading or not
*/
/**************************************************************************/
void sense_read::SensorReadThread::set_enable(uint8_t bitmask){
    this->enable_bitmask = bitmask;   
}

/**************************************************************************/
/*!
    @brief function to be called internally for threading purposes
*/
/**************************************************************************/
void sense_read::SensorReadThread::_internal_thread_func(void){
    // Reading our bitmask and checking whichever sensors we should be!
    if(this->enable_bitmask & (ENAB_BARO))
        this->read_pressure_sensor();
    if(this->enable_bitmask & (ENAB_MIC))
        this->read_mic();
    if(this->enable_bitmask & (ENAB_IMU))
        this->read_imu();
    if(this->enable_bitmask & (ENAB_HTEMP))
        this->read_temp_humd();
    if(this->enable_bitmask & (ENAB_PROX))
        this->read_prox_color();

    rtos::Thread::wait(this->delay_ms);
}

/**************************************************************************/
/*!
    @brief internal method that reads/filters our pressure data. 
*/
/**************************************************************************/
void sense_read::SensorReadThread::read_pressure_sensor(void){
    this->barometric_pressure = BARO.readPressure();
}
/**************************************************************************/
/*!
    @brief method that reads and filters our mic data
*/
/**************************************************************************/
void sense_read::SensorReadThread::read_mic(void){

}

/**************************************************************************/
/*!
    @brief method that reads and filters our imu data. 
*/
/**************************************************************************/
void sense_read::SensorReadThread::read_imu(void){
    if(IMU.accelerationAvailable())
        IMU.readAcceleration(this->accel_data.x, this->accel_data.y, this->accel_data.z);
    if(IMU.gyroscopeAvailable())
        IMU.readGyroscope(this->gyro_data.x, this->gyro_data.y, this->gyro_data.z);
    if(IMU.magneticFieldAvailable())
        IMU.readMagneticField(this->mag_data.x, this->mag_data.y, this->mag_data.z);
}

/**************************************************************************/
/*!
    @brief method that reads and filters our proximity and color data
*/
/**************************************************************************/
void sense_read::SensorReadThread::read_prox_color(void){
    if(APDS.colorAvailable())
        APDS.readColor(this->color_data.r, this->color_data.g, this->color_data.b);
    if(APDS.gestureAvailable())
        this->gesture_prox_data.gesture = APDS.readGesture();
    if(APDS.proximityAvailable())
        this->gesture_prox_data.proximity = APDS.readProximity();
}

/**************************************************************************/
/*!
    @brief method that reads/filters our tempurature and humidity data. 
*/
/**************************************************************************/
void sense_read::SensorReadThread::read_temp_humd(void){
    this->temp_hum_data.tempurature = HTS.readTemperature();
    this->temp_hum_data.humidity = HTS.readHumidity();
}