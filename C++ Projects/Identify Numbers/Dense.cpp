#include "Dense.h"

/**
 * Constructor which inits a new layer with given parameters.
 * accepts 2 matrices and activation function
 * @param weight matrix of weights of this layer
 * @param bias matrix of bias of this layer
 * @param activation_function of this layer
 */
Dense::Dense (const Matrix &weight, const Matrix &bias,
              activation_func activation_function)
{
  _weights = weight;
  _bias = bias;
  _activation_func = activation_function;
}

/**
 * gets method for wights matrix of this layer
 * @return a matrix
 */
Matrix Dense::get_weights () const
{
  return this->_weights;
}

/**
 * gets method for bias matrix of this layer
 * @return a matrix
 */
Matrix Dense::get_bias () const
{
  return this->_bias;
}

/**
 * gets method for activation function of this layer
 * @return pointer to activation function
 */
activation_func Dense::get_activation () const
{
  return _activation_func;
}

/**
 * applies the later on input
 * @param vector a vector to manipulate
 * @return output matrix
 */
Matrix Dense::operator() (const Matrix &vector) const
{
  return _activation_func (_weights * vector + _bias);
}