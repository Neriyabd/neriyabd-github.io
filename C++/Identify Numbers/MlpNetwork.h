//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

#define NUMBERS_OF_DIGITS 10
/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit
{
    unsigned int value;
    float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64,  128},
                                    {20,  64},
                                    {10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
                                 {64,  1},
                                 {20,  1},
                                 {10,  1}};

/**
 * a class that will be used to arrange different layers in a network
 * allows an input of network and obtain an appropriate output/
 * constructor and methods description in MlpNetwork.cpp
 */
class MlpNetwork
{
 public:
  MlpNetwork (Matrix weight[], Matrix _biases[]);
  digit operator() (const Matrix &vector);

 private:
  Matrix _weight[MLP_SIZE];
  Matrix _biases[MLP_SIZE];
};

#endif // MLPNETWORK_H