#include "sensor_read_runtime.hpp"

/*!
*   @brief Handler that lets us get microphone data 
*/
rtos::Thread mic_read_thread_handler; 

/*!
*   @brief Function Declarations 
*/
void start_sensor_read_runtime(void); 
static void microphone_capture_thread(void); 

/*!
*   @brief Starts up the thread(s) requried to collect data from all the sensors
*/
void start_sensor_read_runtime(void){
    mic_read_thread_handler.start(microphone_capture_thread); 
}

/*!
*   @brief Primary Thread that records as much sensor data as possible 
*/
static void microphone_capture_thread(void){

    for(;;){
        
    }
}