#include "Matrix.h"

/***************************/
/**    Constructors        */
/***************************/


/**
 * Constructor that initializes Matrix object with rows x cols.
 * inits all element of matrix of type float to 0.
 * @param rows an int for numbers of rows to create in matrix
 * @param cols an int for numbers of columns to create in matrix
 */
Matrix::Matrix (int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
  {
    throw std::length_error (LENGTH_ERROR_MSG);
  }
  _cols = cols;
  _rows = rows;
  _matrix_elements = new float[_rows * _cols];
  for (int i = 0; i < _rows * _cols; i++)
  {
    _matrix_elements[i] = 0;
  }
}

/**
 * Default constructor for class Matrix
 * initialize a matrix 1 x 1 with 0 value
 */
Matrix::Matrix ()
{
  _rows = ONE;
  _cols = ONE;
  _matrix_elements = new float[_rows * _cols];
  _matrix_elements[0] = 0;
}

// copy constructor
/**
 * constructs a new matrix from another matrix mat (matrix in param)
 * @param mat - mat to copy its data from
 */
Matrix::Matrix (const Matrix &mat)
{
  this->_matrix_elements = new float[mat.get_rows () * mat.get_cols ()];
  this->_cols = mat.get_cols ();
  this->_rows = mat.get_rows ();
  for (int i = 0; i < mat._cols * mat._rows; i++)
  {
    this->_matrix_elements[i] = mat._matrix_elements[i];
  }
}

/**
 * destructor that deletes all allocated memory that was allocated in
 * Matrix class
 */
Matrix::~Matrix ()
{
  delete[] _matrix_elements;
}

/***************************/
/**       Getters          */
/***************************/

/**
 * gets method for number of columns in matrix
 * @return an int of number of rows
 */
int Matrix::get_rows () const
{
  return this->_rows;
}

/**
 * gets method for number of columns in matrix
 * @return an int of number of columns
 */
int Matrix::get_cols () const
{
  return this->_cols;
}

/**
 * transpose a given matrix
 * @return a transformed transposed matrix
 */
Matrix &Matrix::transpose ()
{
  int trans_rows = this->_cols, trans_cols = this->_rows;
  Matrix trans (trans_rows, trans_cols);
  for (int i = 0; i < trans_rows; i++)
  {
    for (int j = 0; j < trans_cols; j++)
    {
      trans (i, j) = (*this) (j, i);
    }
  }
  (*this) = trans;
  return (*this);
}

/**
 * change a given matrix to a vector as follows:
 * vector rows = number of rows in matrix * number of cols in matrix.
 * @return a vector of class Matrix
 */
Matrix &Matrix::vectorize ()
{
  int cur_rows = this->_rows;
  this->_rows = cur_rows * _cols;
  this->_cols = ONE;
  return (*this);
}

/**
 * prints to the std cout
 */
void Matrix::plain_print () const
{
  for (int i = 0; i < this->_rows; i++)
  {
    for (int j = 0; j < this->_cols; j++)
    {
      std::cout << (*this) (i, j) << SPACE;
    }
    std::cout << std::endl;
  }
}

/**
 * given 2 matrices (mark them A, B), create a new matrix C with elements
 * C[i][j] = A[i][j] * B[i][j] for every i, j
 * @param mat a new matrix with multiplied elements
 * @return a new matrix
 */
Matrix Matrix::dot (const Matrix &mat) const
{
  if (this->_rows != mat.get_rows () || this->_cols != mat.get_cols ())
  {
    throw std::length_error (DIFFERENT_SIZE_MATRIX_ERROR_MSG);
  }
  Matrix new_mat (this->_rows, this->_cols);
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      new_mat (i, j) = (*this) (i, j) * mat (i, j);
    }
  }
  return new_mat;
}

/**
 * calculate the norm of a given matrix
 * @return a float that represent the norm
 */
float Matrix::norm () const
{
  float normal = 0;
  for (int i = 0; i < _rows * _cols; i++)
  {
    normal += (*this)[i] * (*this)[i];
  }
  return std::sqrt (normal);
}

/***************************/
/**       Operators        */
/***************************/

/**
 * given two matrices (A, B), creates a new matrix C such that C = A + B
 * @param mat - a given matrix to add with matrix that was called from class
 * method
 * @return new matrix
 */
Matrix Matrix::operator+ (const Matrix &mat) const
{
  if (this->_rows != mat.get_rows () || this->_cols != mat.get_cols ())
  {
    throw std::length_error (DIFFERENT_SIZE_MATRIX_ERROR_MSG);
  }
  Matrix new_mat (this->_rows, this->_cols);
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      new_mat (i, j) = (*this) (i, j) + mat (i, j);
    }
  }
  return new_mat;
}

/**
 * given a matrix A, creates a new matrix B such that B = A * scalar
 * @param scalar - a float to manipulate a matrix with
 * @return a new matrix
 */
Matrix Matrix::operator* (float scalar) const
{
  Matrix new_mat (this->_rows, this->_cols);
  for (int i = 0; i < new_mat._rows * new_mat._cols; i++)
  {
    new_mat[i] = (*this)[i] * scalar;
  }
  return new_mat;
}

/**
 * given a matrix A, creates a new matrix B such that B = scalar * A
 * @param scalar a float to manipulate a matrix with
 * @param mat matrix to manipulate with scalar
 * @return a new matrix
 */
Matrix operator* (float scalar, const Matrix &mat)
{
  Matrix new_mat (mat._rows, mat._cols);
  for (int i = 0; i < new_mat._cols * new_mat._rows; i++)
  {
    new_mat[i] = mat[i] * scalar;
  }
  return new_mat;
}

/**
 * given two matrices (A, B), creates a new matrix C such that C = A * B
 * @param mat matrix to manipulate with another matrix
 * @return a new matrix
 */
Matrix Matrix::operator* (const Matrix &mat) const
{
  if (this->_cols != mat.get_rows ())
  {
    throw std::length_error (MULTIPLY_LENGTH_ERROR_MSG);
  }
  Matrix multiply_mat (this->_rows, mat.get_cols ());
  for (int i = 0; i < this->_rows; i++)
  {
    for (int j = 0; j < mat.get_cols (); j++)
    {
      for (int m = 0; m < this->get_cols (); m++)
      {
        multiply_mat (i, j) += (*this) (i, m) * mat (m, j);
      }
    }
  }
  return multiply_mat;
}

/**
 * assign the matrix that called the method with elements in mat
 * @param mat mat to assign to the class matrix
 * @return a reference to the matrix that called the method
 */
Matrix &Matrix::operator= (const Matrix &mat)
{
  if (&mat == this)
  {
    return *this;
  }
  delete[] this->_matrix_elements;
  _rows = mat._rows;
  _cols = mat._cols;
  _matrix_elements = new float[_rows * _cols];
  for (int i = 0; i < _rows * _cols; i++)
  {
    (*this)[i] = mat[i];
  }
  return *this;
}

/**
 * adds the matrix element in the mat (matrix in param) to the matrix that
 * called the method
 * @param mat a matrix to add to the given matrix of the class
 * @return a reference to the matrix that called the method
 */
Matrix &Matrix::operator+= (const Matrix &mat)
{
  if ((mat._cols != this->_cols) && (mat._rows != this->_rows))
  {
    throw std::length_error (LENGTH_ERROR_MSG);
  }
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      (*this) (i, j) += mat (i, j);
    }
  }
  return *this;
}

/**
 * calculate element in matrix[i][j] place
 * @param i - an int that represent the row of matrix in class
 * @param j - an int that represent the column of matrix in class
 * @return a float that in row i and column j in matrix
 */
float Matrix::operator() (int i, int j) const
{
  if (0 > i || i >= this->_rows || j >= this->_cols || j < 0)
  {
    throw std::out_of_range (OUT_OF_RANGE_ERROR_MSG);
  }
  return this->_matrix_elements[i * this->_cols + j];
}

/**
 * calculate element in matrix[i][j] place
 * @param i - an int that represent the row of matrix in class
 * @param j - an int that represent the column of matrix in class
 * @return a reference to the float element
 * that in row i and column j in matrix
 */
float &Matrix::operator() (int i, int j)
{
  if (0 > i || i >= this->_rows || j >= this->_cols || j < 0)
  {
    throw std::out_of_range (OUT_OF_RANGE_ERROR_MSG);
  }
  return this->_matrix_elements[i * _cols + j];
}

float &Matrix::operator[] (int n)
/**
 * find the n'th element in matrix
 * @param n - an int that represent the n'th element
 * @return a reference to the float element in the n'th place in matrix
 */
{
  if (n < 0 || n >= (this->_cols) * (this->_rows))
  {
    throw std::out_of_range (OUT_OF_RANGE_ERROR_MSG);
  }
  return this->_matrix_elements[n];
}

/**
 * find the n'th element in matrix
 * @param n - an int that represent the n'th element
 * @return the float value of the n'th element in matrix
 */
float Matrix::operator[] (int n) const
{
  if (n < 0 || n >= (this->_cols) * (this->_rows))
  {
    throw std::out_of_range (OUT_OF_RANGE_ERROR_MSG);
  }
  return this->_matrix_elements[n];
}

/***************************/
/**   Stream Operators     */
/***************************/

/**
 * prints a "**" or "  " based on matrix value in element
 * @param stream - a stream to print to
 * @param mat - matrix to print from
 * @return a stream
 */
std::ostream &operator<< (std::ostream &stream, const Matrix &mat)
{
  for (int i = 0; i < mat.get_rows (); i++)
  {
    for (int j = 0; j < mat.get_cols (); j++)
    {
      if (mat (i, j) > TENTH)
      {
        std::cout << DOUBLE_DOT;
      }
      else
      {
        std::cout << DOUBLE_SPACE;
      }
    }
    std::cout << std::endl;
  }
  return stream;
}

/**
 * read a binary file to the stream
 * @param stream - a stream to read to
 * @param mat - matrix to read from
 * @return an is stream
 */
std::istream &operator>> (std::istream &stream, Matrix &mat)
{
  if (!stream)
  {
    throw std::runtime_error (RUNTIME_ERROR_MSG);
  }
  stream.seekg (0, std::ifstream::end);
  unsigned long long int len = stream.tellg ();
  stream.seekg (0, std::ifstream::beg);
  unsigned long long length =
      mat.get_rows () * mat.get_cols () * sizeof (float);
  if (len != length)
  {
    throw std::runtime_error (RUNTIME_ERROR_MSG);
  }
  stream.read ((char *) (mat._matrix_elements), sizeof (float)
                                                * mat.get_cols ()
                                                * mat.get_rows ());
  return stream;
}
