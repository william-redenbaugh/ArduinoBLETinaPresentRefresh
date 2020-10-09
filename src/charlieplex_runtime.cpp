#include "charlieplex_runtime.hpp"

static uint8_t *intensity_arr; 

/*!
*   @brief Thread handler for the charlieplex thread. 
*/
static rtos::Thread charlieplex_thread_handler; 

/*!
*   @brief Controler module for dealing with the CharliePlex Module
*/
static Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731_Wing();

/*!
*   @brief Function Declarations
*/
void start_charliexplex_runtime(uint8_t *fft_arr); 
static void charlieplex_control_thread(void);

void start_charliexplex_runtime(uint8_t *fft_arr){ 
    intensity_arr = fft_arr; 
    charlieplex_thread_handler.start(charlieplex_control_thread); 
}

static void charlieplex_control_thread(void){
    // Setting up the charlieplex led matrix
    // If we can't properly initialize the charlieplex we sleep the thread
    if(!matrix.begin()){
        Serial.println("CharliePlex Matrix not found");
        while(1)
            rtos::ThisThread::sleep_for(1000);
    }  

    uint32_t restart_matrix = 0; 
    uint8_t frame = 0; 
    for(;;){
        matrix.setFrame(frame); 
        for(int x = 0; x < 15; x++){  
            uint8_t intensity = intensity_arr[x * 4] / 32; 
            for(int y = 0; y < intensity; y++){
                matrix.drawPixel(x, y, 255); 
            }
            for(int y = intensity; y < 7; y++){
                matrix.drawPixel(x, y, 0); 
            }
        }
        matrix.displayFrame(frame); 

        // Reset which frame we are using
        if(frame)
            frame = 0; 
        frame++; 

        if(restart_matrix == 1024){
            matrix.begin(); 
            restart_matrix = 0; 
        }
        restart_matrix++; 
    
        rtos::ThisThread::sleep_for(20);  
    }
}