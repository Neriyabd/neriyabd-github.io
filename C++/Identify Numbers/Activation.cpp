#include "Activation.h"

/**
 * a function that calculate the final result of a layer in the neural network.
 * @param mat matrix to use copy constructor from.
 * @return a new vector (class Matrix).
 */
Matrix activation::relu (const Matrix &mat)
{
  Matrix new_mat (mat);
  for (int i = 0; i < new_mat.get_rows () * new_mat.get_cols (); i++)
  {
    if (new_mat[i] < 0)
    {
      new_mat[i] = 0;
    }
  }
  return new_mat;
}

/**
 * a function that gets a vector as an input, converts it to distribution
 * vector in a corresponding method to the final output of the neural network.
 * @param mat matrix to use copy constructor from.
 * @return a new vector (class Matrix).
 */
Matrix activation::softmax (const Matrix &mat)
{
  Matrix new_mat (mat);
  float scalar_sum = 0;
  for (int i = 0; i < mat.get_rows () * mat.get_cols (); i++)
  {
    scalar_sum += std::exp (mat[i]);
  }
  scalar_sum = 1 / scalar_sum;
  for (int i = 0; i < mat.get_rows () * mat.get_cols (); i++)
  {
    new_mat[i] = scalar_sum * (std::exp (new_mat[i]));
  }
  return new_mat;
}