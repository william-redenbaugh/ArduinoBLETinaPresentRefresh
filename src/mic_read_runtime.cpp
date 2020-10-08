#include "mic_read_runtime.hpp"

/*!
*   @brief Handler that lets us get microphone data 
*/
rtos::Thread mic_read_thread_handler; 

/*!
*   @brief Micrphone buffer data
*/
static const unsigned int microphone_buffer_size = 256; 
short microphone_buffer[microphone_buffer_size]; 

/*!
*   @brief Function Declarations 
*/
void start_sensor_read_runtime(void); 
static void microphone_capture_thread(void); 
static void imu_capture_thread(void); 

/*!
*   @brief Starts up the thread(s) requried to collect data from all the sensors
*/
void start_sensor_read_runtime(void){
    // mic_read_thread_handler.start(microphone_capture_thread); 
}

/*!
*   @brief Primary Thread that records as much sensor data as possible 
*/
static void microphone_capture_thread(void){
    if(!PDM.begin(1, 16000)){
        Serial.println("Microphone could not initialize"); 
        for(;;)
            rtos::ThisThread::sleep_for(1000); 
    }

    PDM.setGain(200);
    for(;;){
        //Reads the micrphone data. 
        PDM.read(microphone_buffer, microphone_buffer_size * 2); 
        
        long ave = 0; 
        for(int n = 0; n < 256; n++){
            ave += microphone_buffer[n]; 
        }
        // ave / 256; 
        //ave = ave / 256;  
        rtos::ThisThread::sleep_for(20);
    }
}

/*!
*   @brief Thread that reads in IMU data
*
*/
static void sensor_capture_thread(void){

    for(;;){
        
    }
}

short* get_latest_microphone_data(void){
    return microphone_buffer; 
}