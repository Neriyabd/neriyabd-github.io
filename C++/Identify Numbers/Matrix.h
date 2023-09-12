// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <fstream>
#define OUT_OF_RANGE_ERROR_MSG "out of range"
#define RUNTIME_ERROR_MSG "run time error"
#define LENGTH_ERROR_MSG "Wrong Length"
#define DIFFERENT_SIZE_MATRIX_ERROR_MSG "Can't add matrices with \
different size of columns and rows"
#define MULTIPLY_LENGTH_ERROR_MSG "First matrix columns are different than \
second matrix rows"
#define SPACE " "
#define TENTH 0.1
#define ONE 1
#define DOUBLE_DOT "**"
#define DOUBLE_SPACE "  "

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

/**
 * class of matrix with floats in it's elements
 * All methods and operators function description are in Matrix.cpp
 */
class Matrix
{
 public:
  // constructors
  Matrix ();
  Matrix (int rows, int cols);

  // copy constructor
  Matrix (const Matrix &mat);

  // destructor
  ~Matrix ();

  // gets methods
  int get_rows () const;
  int get_cols () const;

  // methods on called matrix
  Matrix &transpose ();
  Matrix &vectorize ();
  void plain_print () const;
  float norm () const;

  // multiply each element and create new matrix
  Matrix dot (const Matrix &mat) const;

  // operators
  Matrix operator+ (const Matrix &mat) const;
  Matrix operator* (float scalar) const;
  friend Matrix operator* (float scalar, const Matrix &mat);
  Matrix operator* (const Matrix &mat) const;
  Matrix &operator= (const Matrix &mat);
  Matrix &operator+= (const Matrix &mat);

  // index operators
  float operator() (int i, int j) const;
  float &operator() (int i, int j);
  float operator[] (int i) const;
  float &operator[] (int i);

  // streams operator
  friend std::ostream &operator<< (std::ostream &stream, const Matrix &mat);
  friend std::istream &operator>> (std::istream &stream, Matrix &mat);

 private:
  int _rows;
  int _cols;
  float *_matrix_elements;
};

#endif //MATRIX_H

