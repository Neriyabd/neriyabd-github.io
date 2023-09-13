#include "MlpNetwork.h"

using namespace activation;

/**
 * constructor that accepts 2 arrays of matrices, size of MLP_SIZE each.
 * one for weights and one for biases.
 * @param weight
 * @param biases
 */
MlpNetwork::MlpNetwork (Matrix weight[], Matrix biases[])
{
  for (int i = 0; i < MLP_SIZE; i++)
  {
    _weight[i] = weight[i];
    _biases[i] = biases[i];
  }
}

/**
 * applies the entire network on a matrix.
 * given matrix vector in param, copy the matrix and applies relu and softmax
 * function (namespace activation )based on MLP_SIZE to copied matrix
 * finally: adds to digit struct the highest probability number and its value
 * @param vector matrix to copy from and apply layers of dense to the matrix.
 * @return a digit struct.
 */
digit MlpNetwork::operator() (const Matrix &vector)
{
  Matrix copied_vector (vector);
  int size_of_mlp = MLP_SIZE - 1;
  for (int i = 0; i < size_of_mlp; i++)
  {
    Dense cur (_weight[i], _biases[i], activation::relu);
    copied_vector = cur (copied_vector);
  }
  Dense cur (_weight[size_of_mlp], _biases[size_of_mlp], activation::softmax);
  copied_vector = cur (copied_vector);
  digit result_dig = digit{0, 0};
  for (int i = 0; i < NUMBERS_OF_DIGITS; i++)
  {
    if (copied_vector[i] > result_dig.probability)
    {
      result_dig.value = i, result_dig.probability = copied_vector[i];
    }
  }
  return result_dig;
}