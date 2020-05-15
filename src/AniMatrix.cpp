#include "AniMatrix.hpp"

void animatrix_thread_func(AniMatrix::MatrixAnimationHandler *self_thread){
    while(1){
        self_thread->_run();
    }
}

/**************************************************************************/
/*!
    @brief Initialization for our matrix animation handler, requires a matrix to manipulate which is passed in as a pointer. 
*/
/**************************************************************************/
void AniMatrix::MatrixAnimationHandler::begin(Adafruit_IS31FL3731 *matrix_ptr){
    this->matrix_ptr = matrix_ptr;
    this->animation_thread.start(animatrix_thread_func, this);
}

/**************************************************************************/
/*!
    @brief background run function for our matrix animation handler
*/
/**************************************************************************/
void AniMatrix::MatrixAnimationHandler::_run(void){
    // Wait for signal for next animation
    rtos::Thread::signal_wait(AniMatrix::animation_flag);    
    rtos::Thread::signal_clr(AniMatrix::animation_flag);

    switch(this->next_animation){
        case(AniMatrix::SWIPE_LEFT):
        Serial.println("Swiping left...");
        break;

        case(AniMatrix::SWIPE_RIGHT):
        Serial.println("Swiping right...");
            
        break;

        case(AniMatrix::SWIPE_UP):
        Serial.println("Swiping up...");    
        break;

        case(AniMatrix::SWIPE_DOWN):
        Serial.println("Swiping down...");
        break;
        default:
        break;
    }
    this->next_animation = AniMatrix::NONE;
    this->animation_complete = true; 
}

/**************************************************************************/
/*!
    @brief Set the next animation in our animation handler. 
*/
/**************************************************************************/
bool AniMatrix::MatrixAnimationHandler::set_next_animation(uint16_t next_ani){
    // If the animation isn't complete yet, then we report success as false. 
    if(!this->animation_complete)
        return false; 

    this->next_animation = next_ani; 
    this->animation_complete = false; 
    this->animation_thread.signal_set(AniMatrix::animation_flag);
}