#include "AniMatrix.hpp"

/**************************************************************************/
/*!
    @brief Initialization for our matrix animation handler, requires a matrix to manipulate which is passed in as a pointer. 
*/
/**************************************************************************/
void AniMatrix::MatrixAnimationHandler::begin(Adafruit_IS31FL3731 *matrix_ptr){
    this->matrix_ptr = matrix_ptr;
}