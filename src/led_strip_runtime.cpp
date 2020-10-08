#include "led_strip_runtime.hpp"
#include "hsv_rgb_conv.hpp"

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


        HsvColor col = {20, 255, 255}; 
        RgbColor rgb_col = HsvToRgb(col); 

        for(int n = 0; n < 45; n++){
            pixels.setPixelColor(n, rgb_col.r, rgb_col.g, rgb_col.b, 0); 
        }
        pixels.show(); 
        
        rtos::ThisThread::sleep_for(100); 
    }
}