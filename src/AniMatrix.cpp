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
        case(AniMatrix::SWIPE_UP):
          this->_swipe_up();
        break;

        case(AniMatrix::SWIPE_DOWN):
        this->_swipe_down();
        break;

        case(AniMatrix::SWIPE_LEFT):
        this->_swipe_left();
        break;

        case(AniMatrix::SWIPE_RIGHT):
        this->_swipe_right();    
        break;

        // Don't get here please. 
        default:
        break;
    }
    // Tell the realtime operating system what the next flag 
    // or rather the animation complete flag is. 
    this->next_animation = AniMatrix::NONE;
    this->animation_complete = true; 
    this->animation_thread.signal_set(AniMatrix::animation_complete_flag);
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

/**************************************************************************/
/*!
    @brief Blocks current thread until the animation has completed.  
*/
/**************************************************************************/
bool AniMatrix::MatrixAnimationHandler::wait_animation_end(void){
    this->animation_thread.signal_wait(AniMatrix::animation_complete_flag);
}

/**************************************************************************/
/*!
    @brief  swipe down animation internal function call
*/
/**************************************************************************/
void AniMatrix::MatrixAnimationHandler::_swipe_down(void){
  for(uint8_t x = 0; x < 16; x++){
    
    this->matrix_ptr->displayFrame(1);
    this->matrix_ptr->setFrame(0);

    for(uint8_t y = 0; y < 8; y++)
      this->matrix_ptr->drawPixel(x, y, 50);
    
    this->matrix_ptr->displayFrame(0);
    this->matrix_ptr->setFrame(1);
    
    for(uint8_t y = 0; y < 8; y++)
      this->matrix_ptr->drawPixel(x, y, 50);

    if(this->interrupt_animation)
      return; 

    rtos::ThisThread::sleep_for(10);
  }

  for(uint8_t x = 0; x < 16; x++){
    this->matrix_ptr->displayFrame(1);
    this->matrix_ptr->setFrame(0);
    
    for(uint8_t y = 0; y < 8; y++)
      this->matrix_ptr->drawPixel(x, y, 0);
    
    this->matrix_ptr->displayFrame(0);
    this->matrix_ptr->setFrame(1);
    
    for(uint8_t y = 0; y < 8; y++)
      this->matrix_ptr->drawPixel(x, y, 0);
    
    if(this->interrupt_animation)
      return; 
    
    rtos::ThisThread::sleep_for(10);
  }
}

/**************************************************************************/
/*!
    @brief  swipe up animation internal function call
*/
/**************************************************************************/
void AniMatrix::MatrixAnimationHandler::_swipe_up(void){
  for(uint8_t x = 16; x > 0; x--){
    this->matrix_ptr->displayFrame(1);
    this->matrix_ptr->setFrame(0);
    
    for(uint8_t y = 0; y < 8; y++){
      this->matrix_ptr->drawPixel(x, y, 50);
    }
    
    this->matrix_ptr->displayFrame(0);
    this->matrix_ptr->setFrame(1);

    for(uint8_t y = 0; y < 8; y++)
      this->matrix_ptr->drawPixel(x, y, 50);
    rtos::ThisThread::sleep_for(10);
  }

  for(uint8_t x = 16; x > 0; x--){
    this->matrix_ptr->displayFrame(1);
    this->matrix_ptr->setFrame(0);

    for(uint8_t y = 0; y < 8; y++)
      this->matrix_ptr->drawPixel(x, y, 0);

    this->matrix_ptr->displayFrame(0);
    this->matrix_ptr->setFrame(1);
    
    for(uint8_t y = 0; y < 8; y++)
      this->matrix_ptr->drawPixel(x, y, 0);

    rtos::ThisThread::sleep_for(10);
  }
}

/**************************************************************************/
/*!
    @brief  swipe left animation internal function call
*/
/**************************************************************************/
void AniMatrix::MatrixAnimationHandler::_swipe_left(void){
  for(uint8_t y = 0; y < 8; y++){
    this->matrix_ptr->displayFrame(1);
    this->matrix_ptr->setFrame(0);

    for(uint8_t x = 0; x < 16; x++)
      this->matrix_ptr->drawPixel(x, y, 50);
    
    this->matrix_ptr->displayFrame(0);
    this->matrix_ptr->setFrame(1);

    for(uint8_t x = 0; x < 16; x++)
      this->matrix_ptr->drawPixel(x, y, 50);
    
    rtos::ThisThread::sleep_for(10);
  }

  for(uint8_t y = 0; y < 8; y++){
    this->matrix_ptr->displayFrame(1);
    this->matrix_ptr->setFrame(0);

    for(uint8_t x = 0; x < 16; x++)
      this->matrix_ptr->drawPixel(x, y, 0);
    
    this->matrix_ptr->displayFrame(0);
    this->matrix_ptr->setFrame(1);
    
    for(uint8_t x = 0; x < 16; x++)
      this->matrix_ptr->drawPixel(x, y, 0);
    
    rtos::ThisThread::sleep_for(10);
  }
}

/**************************************************************************/
/*!
    @brief  swipe right animation internal function call
*/
/**************************************************************************/
void AniMatrix::MatrixAnimationHandler::_swipe_right(void){
  for(uint8_t y = 8; y > 0; y--){
    this->matrix_ptr->displayFrame(1);
    this->matrix_ptr->setFrame(0);

    for(uint8_t x = 0; x < 16; x++)
      this->matrix_ptr->drawPixel(x, y, 50);
    
    this->matrix_ptr->displayFrame(0);
    this->matrix_ptr->setFrame(1);
    
    for(uint8_t x = 0; x < 16; x++)
      this->matrix_ptr->drawPixel(x, y, 50);
    
    rtos::ThisThread::sleep_for(10);
  }

  for(uint8_t y = 8; y > 0; y--){
    this->matrix_ptr->displayFrame(1);
    this->matrix_ptr->setFrame(0);

    for(uint8_t x = 0; x < 16; x++)
      this->matrix_ptr->drawPixel(x, y, 0);
    
    this->matrix_ptr->displayFrame(0);
    this->matrix_ptr->setFrame(1);

    for(uint8_t x = 0; x < 16; x++)
      this->matrix_ptr->drawPixel(x, y, 0);
    
    rtos::ThisThread::sleep_for(10);
  }  
}

/**************************************************************************/
/*!
    @brief show text information internal function call. 
*/
/**************************************************************************/
void AniMatrix::MatrixAnimationHandler::_show_text(void){
  
}