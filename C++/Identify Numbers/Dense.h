#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

/**
 * Dense is a class that represent a layer in neural network
 * methods and constructors description in Dense.cpp
 */
class Dense
{
 public:
  Dense (const Matrix &weight, const Matrix &bias, activation_func activation_function);
  Matrix get_weights () const;
  Matrix get_bias () const;
  activation_func get_activation () const;
  Matrix operator() (const Matrix &mat) const;

 private:
  Matrix _weights;
  Matrix _bias;
  activation_func _activation_func;
};

#endif //DENSE_H
