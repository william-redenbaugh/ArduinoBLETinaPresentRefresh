#include "led_strip_runtime.hpp"

/*!
*   @brief Which GPIO pin is our neopixel connected to
*/
static const int PIN = A3; 

/*!
*   @brief How many LEDs is our strip. 
*/
static const int NUMPIXELS = 45; 

/*!
*   @brief Thread handler for our LED strip
*/
static rtos::Thread strip_thread_handler; 

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
static Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

/*!
*   @brief Function declarations
*/
void start_led_strip_runtime(void); 
static void led_strip_thread(void); 

/*!
*   @brief Setting up our LED strip thread. 
*/
void start_led_strip_runtime(void){
    pixels.begin(); 
    pixels.setBrightness(10); 

    strip_thread_handler.start(led_strip_thread); 
}

/*!
*   @brief Thread function
*/
static void led_strip_thread(void){
    for(;;){
        int r = random(255); 
        int g = random(255); 
        int b = random(255); 
        for(int n = 0; n < NUMPIXELS; n++){
        pixels.setPixelColor(n, r, g, b, 0);  
        pixels.show(); 
        rtos::ThisThread::sleep_for(10);   
        }
    }
}