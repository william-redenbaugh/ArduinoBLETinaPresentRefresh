#include "AniMatrix.hpp"

void AniMatrix::MatrixAnimationHandler::begin(Adafruit_IS31FL3731 *matrix_ptr){
    this->matrix_ptr = matrix_ptr;
}