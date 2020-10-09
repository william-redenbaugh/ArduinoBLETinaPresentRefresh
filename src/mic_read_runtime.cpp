#include "mic_read_runtime.hpp"

/*!
*   @brief Handler that lets us get microphone data 
*/
rtos::Thread mic_read_thread_handler; 

/*!
*   @brief Micrphone buffer data
*/
static const unsigned int microphone_buffer_size = 64; 
static short microphone_buffer[microphone_buffer_size]; 
static int samples_read = 0; 

/*!
*   @brief Function Declarations 
*/
short* get_latest_microphone_data(void){return microphone_buffer;} 
void start_sensor_read_runtime(void); 
static void microphone_capture_thread(void); 
static void mic_data_capture_callback(void); 

/*!
*   @brief Starts up the thread(s) requried to collect data from all the sensors
*/
void start_sensor_read_runtime(void){
    PDM.onReceive(mic_data_capture_callback); 
    PDM.setBufferSize(128);
    PDM.setGain(235); 
    if(!PDM.begin(1, 16000)){
        Serial.println("Microphone could not initialize"); 
        for(;;)
            rtos::ThisThread::sleep_for(1000); 
    }
    Serial.println("Microphone initialized properly!"); 
}

static void mic_data_capture_callback(void){
    int bytes_available = PDM.available(); 
    PDM.read(microphone_buffer, bytes_available); 
    samples_read = bytes_available / 2; 
}