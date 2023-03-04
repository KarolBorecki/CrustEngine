#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>
#include <string>

// TODO reasearch for operands overloading
/**
* @brief Represents the mathematical matrix and is able to preform matrix calculations.
*/
template<class T>
class Matrix {
public:
  /**
  * @param rows Amount of rows in the matrix.
  * @param columns Amount of columns in the matrix.
  */
  Matrix(uint8_t rows, uint8_t columns);
  /**
  * @param rows Amount of rows in the matrix.
  * @param columns Amount of columns in the matrix.
  * @param defaultVal The value that will be placed on each position in matrix.
  */
  Matrix(uint8_t rows, uint8_t columns, T defaultVal);
  /**
  * @details If #mat is not null deletes it from the heap.
  */
  ~Matrix();

  /**
  * @brief Getter for #rows field.
  *
  * @return Amount of rows in matrix.
  */
  uint8_t Rows();
  /**
  * @brief Getter for #columns field.
  *
  * @return Amount of columns in matrix
  */
  uint8_t Columns();

  /**
  * @brief Getter for #mat field.
  *
  * @return Pointer to matrix array.
  */
  double* GetMatrixArray();

  /**
  * @brief Returns value stored on the given position in matrix.
  *
  * @param row The y index of the position in matrix.
  * @param column The x index of the position in matrix.
  */
  double GetValue(uint8_t row, uint8_t column);

  /**
  * @brief Puts the given value on the given position.
  *
  * @param row The y index of the position in matrix.
  * @param column The x index of the position in matrix.
  */
  void PutValue(uint8_t row, uint8_t column, T value);

  /**
  * @brief Function resets the matrix so each value of it is the same.
  *
  * @param value The value that will be placed on each position in matrix.
  */
  void ResetMatrix(T value);

  /**
  * @brief Adds to given matrix #mat1 another matrix #mat2.
  *
  * @param mat1 Modified matrix.
  * @param mat2 Added matrix.
  */
  static void Add(Matrix<T>* mat1, Matrix<T>* mat2);

  /**
  * @brief Adds to given matrix scalar, constant value.
  *
  * @param mat Matrix to which values scalar will be added.
  * @param scalar Value which will be added.
  */
  static void Add(Matrix<T> *mat, const T scalar);

  /**
   * @brief Substracts from given matrix #mat1 another matrix #mat2.
   *
   * @param mat1 Modified matrix.
   * @param mat2 Added matrix.
   */
  static void Substract(Matrix<T> *mat1, Matrix<T> *mat2);

  /**
  * @brief Multiplies given matrixes.
  *
  * @details Multiplies matrixes as the mat1 * mat2 and returns new object of type matrix being te result of multiplication.
  * The original mat1 and mat2 objects remains not modified by this method.
  *
  * @param mat1 First matrix.
  * @param mat2 Second matrix, by which first is being multiplied.
  * @param outMat The output matrix.
  */
  static void Multiply(Matrix<T> *mat1, Matrix<T> *mat2, Matrix<T> &outMat);
  /**
  * @brief Multiplies given matrix by scalar constant value.
  *
  * @param mat Multiplied Matrix.
  * @param scalar Value by which matrix is being multiplied.
  */
  static void Multiply(Matrix<T> *mat, const T scalar);

  /**
  * @brief Divides given matrix by scalar constant value.
  *
  * @param mat Divided Matrix.
  * @param scalar Value by which matrix is being divided.
  */
  static void Divide(Matrix<T> *mat, const T scalar);

  /**
  * @brief Converts matrix to std::string, so it can be written on any output.
  *
  * @details The returned string is in a following format:<br>
  * First line contains information about the size of the matrix as follows: Matrix of size: <#rows>x<#columns>.<br>
  * Next lines contains the matrix in the correct order of rows and columns.
  */
  std::string ToString();

  /**
  * @brief Getter for matrix ID.
  *
  * @return Matrix's ID.
  */
  uint32_t GetID();

private:
  uint8_t rows { 0 }; //!< Amount of rows in the matrix.
  uint8_t columns { 0 }; //!< Amount of columns in the matrix.
  T* mat; //!< Array of matrix's values.

  uint32_t ID; //!< Matrix's ID.
  static inline uint32_t nextID { 0 }; //!< Next matrix ID. Also holds amount of matrixes created on engine work. Only for debug purposes.

  /**
  * @brief Init function for Matrix. It creates all necessarry arrays and fills it with #defaultVal.
  *
  * @param newRows Amount of rows in created array.
  * @param newColumns Amount of columns in created array.
  * @param defaultVal Value that the matrix will be filled with after creation.
  */
  void Init(uint8_t newRows, uint8_t newColumns, const T defaultVal);
  
  /**
   * @brief Returns matrix's index in array of indexes x=row and y=column.
   * 
   * @details Matrix holds linear array (In order to save space and for it to be more reliable and less time-consuming). 
   * But we use 2-dimensional array in the interface so values are accessed by their's xs and ys (As it is in regular matrixes), This method maps x and y to linear space. 
   * 
   * @param row - searched value's index's x.
   * @param column - searched value's index's y.
  */
  uint8_t GetMatRealIndex(uint8_t row, uint8_t column);
};

template<class E>
inline Matrix<E>::Matrix(uint8_t rows, uint8_t columns) : rows(rows), columns(columns) { Init(rows, columns, 0.0); }

template <class E>
inline Matrix<E>::Matrix(uint8_t rows, uint8_t columns, E defaultVal) : rows(rows), columns(columns) { Init(rows, columns, defaultVal); }

template <class E>
inline Matrix<E>::~Matrix()
{
  delete [] mat;
}

template <class E>
inline uint8_t Matrix<E>::Rows() { return rows; }

template<class E>
inline uint8_t Matrix<E>::Columns() { return columns; }

template<class E>
inline double* Matrix<E>::GetMatrixArray() { return mat; }

template <class E>
inline double Matrix<E>::GetValue(uint8_t row, uint8_t column) { return mat[GetMatRealIndex(row, column)]; }

template<class E>
inline void Matrix<E>::PutValue(uint8_t row, uint8_t column, E value) { mat[GetMatRealIndex(row, column)] = value; }

template <class E>
void Matrix<E>::ResetMatrix(E value)
{
  for(uint8_t i=0; i < rows * columns; i++) mat[i] = value;
}

template <class E>
void Matrix<E>::Add(Matrix<E> *mat1, Matrix<E> *mat2)
{
  if (mat1->Rows() != mat2->Rows() || mat1->Columns() != mat2->Columns())
    return;
  for (uint8_t i = 0; i < mat1->Rows(); i++)
    for (uint8_t j = 0; j < mat1->Columns(); j++)
      mat1->PutValue(i, j, mat1->GetValue(i, j) + mat2->GetValue(i, j));
}

template <class E>
void Matrix<E>::Substract(Matrix<E> *mat1, Matrix<E> *mat2)
{
  if (mat1->Rows() != mat2->Rows() || mat1->Columns() != mat2->Columns())
    return;
  for (uint8_t i = 0; i < mat1->Rows(); i++)
    for (uint8_t j = 0; j < mat1->Columns(); j++)
      mat1->PutValue(i, j, mat1->GetValue(i, j) - mat2->GetValue(i, j));
}

template <class E>
void Matrix<E>::Add(Matrix<E> *mat, const E scalar)
{
  for(uint8_t i=0; i < mat->Rows(); i++)
    for(uint8_t j=0; j < mat->Columns(); j++)
      mat->PutValue(i, j, mat->GetValue(i, j) + scalar);
}

template <class E>
void Matrix<E>::Multiply(Matrix<E> *mat1, Matrix<E> *mat2, Matrix<E> &outMat)
{
  uint8_t resultRows = mat1->Rows();
  uint8_t resultColumns = mat2->Columns();

  if(mat1->Columns() != mat2->Rows()) {
    Logger::Error("Trying to multiply matrix of size %dx%d by matrix of size %dx%d, which cannot be done!", mat1->Rows(), mat1->Columns(), mat2->Rows(), mat2->Columns());
    throw std::runtime_error("Matrix multiplication failed!"); //TODO use my own error handler
  }

  for(uint8_t r=0; r<resultRows; r++) {
    for(uint8_t c=0; c<resultColumns; c++) {
      double value = 0;
      for(uint8_t i=0; i<mat2->Rows(); i++) {
        value += mat1->GetValue(r, i) * mat2->GetValue(i, c);
      }
      outMat.PutValue(r, c, value);
    }
  }
}

template <class E>
void Matrix<E>::Multiply(Matrix<E> *mat, const E scalar)
{
  for(uint8_t i=0; i < mat->Rows(); i++)
    for(uint8_t j=0; j < mat->Columns(); j++)
      mat->PutValue(i, j, mat->GetValue(i, j) * scalar);
}

template <class E>
void Matrix<E>::Divide(Matrix<E> *mat, const E scalar)
{
  if(scalar == 0.0) return;
  for(uint8_t i=0; i < mat->Rows(); i++)
    for(uint8_t j=0; j < mat->Columns(); j++)
      mat->PutValue(i, j, mat->GetValue(i, j) / scalar);
}

template <class E>
std::string Matrix<E>::ToString()
{
  std::string result = "";
  result += "Matrix<" + std::to_string(GetID()) + "> of size: " + std::to_string(rows) + "x" + std::to_string(columns) + "\n";
  if(rows*columns > 200) return result + "Too big to display\n"; //TODO move 200 value to variable
  for(int r=0; r<rows; r++){
    for(int c=0; c<columns; c++){
      result += "(" + std::to_string(r) + "," + std::to_string(c) + ")" +std::to_string(GetValue(r, c)) + " ";
    }
    result += "\n";
  }
  return result;
}

template <class E>
inline uint32_t Matrix<E>::GetID() { return ID; }

template <class E>
void Matrix<E>::Init(uint8_t newRows, uint8_t newColumns, const E defaultVal)
{
  ID = nextID++;
  mat = new E[newRows * newColumns];

  ResetMatrix(defaultVal);
}

template <class E>
inline uint8_t Matrix<E>::GetMatRealIndex(uint8_t row, uint8_t column) { return column + Columns() * row; }

#endif /* _MATRIX_HPP_ */
