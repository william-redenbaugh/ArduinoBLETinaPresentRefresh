#include "charlieplex_runtime.hpp"

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
void start_charliexplex_runtime(void); 
static void charlieplex_control_thread(void);

void start_charlieplex_runtime(void){ 
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
    
    for(;;){
        rtos::ThisThread::sleep_for(1000); 
    }
}