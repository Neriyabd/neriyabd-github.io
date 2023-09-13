#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

/**
 * typedef for pointer to activation func that gets a const matrix as param
 * and returns a matrix by value
 */
typedef Matrix(*activation_func) (const Matrix &);

/**
 * a declarative region of activation functions
 */
namespace activation
{
    Matrix relu (const Matrix &mat);
    Matrix softmax (const Matrix &mat);
}

#endif //ACTIVATION_H