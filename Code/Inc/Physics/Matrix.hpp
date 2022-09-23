#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>
#include <string>

/**
* @brief Represents the mathematical matrix and is able to preform matrix calculations.
*/
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
  Matrix(uint8_t rows, uint8_t columns, double defaultVal);
  /**
  * @details If #mat is not null deletes it from the heap.
  */
  ~Matrix();

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
  void PutValue(uint8_t row, uint8_t column, double value);

  /**
  * @brief Function resets the matrix so each value of it is the same.
  *
  * @param val The value that will be placed on each position in matrix.
  */
  void ResetMatrix(double val);

  /**
  * @brief Getter for #mat field.
  *
  * @return Pointer to matrix array.
  */
  double** GetMatrix();
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
  * @brief Multiplies given matrixes.
  *
  * @details Multiplies matrixes as the mat1 * mat2 and returns new object of type matrix being te result of multiplication.
  * The original mat1 and mat2 objects remains not modified by this method.
  *
  * @param mat1 First matrix.
  * @param mat2 Second matrix, by which first is being multiplied.
  * @param outMat The output matrix.
  */
  static void Multiply(Matrix* mat1, Matrix* mat2, Matrix& outMat);

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
  uint8_t GetID();

private:
  uint8_t rows { 0 }; //!< Amount of rows in the matrix.
  uint8_t columns { 0 }; //!< Amount of columns in the matrix.
  double** mat; //!< Array of matrix's values.

  uint8_t ID; //!< Matrix's ID.
  static inline uint8_t nextID { 0 }; //!< Next matrix ID. Also holds amount of matrixes created on engine work. Only for debug purposes.

  void Init(uint8_t rows, uint8_t columns, double defaultVal);
};

inline Matrix::Matrix(uint8_t rows, uint8_t columns) : rows(rows), columns(columns) { Init(rows, columns, 0.0); }

inline Matrix::Matrix(uint8_t rows, uint8_t columns, double defaultVal) : rows(rows), columns(columns) { Init(rows, columns, defaultVal); }

inline Matrix::~Matrix() {
  Logger::Log(Logger::FontColor::PINK, "[X] Deleting Matrix<%d> of size %dx%d", GetID(), Rows(), Columns());
  for(uint8_t i = 0; i < rows; ++i)
    delete [] mat[i];
  delete [] mat;
}

inline double Matrix::GetValue(uint8_t row, uint8_t column) { return mat[row][column]; }

inline void Matrix::PutValue(uint8_t row, uint8_t column, double value) { mat[row][column] = value; }

void Matrix::ResetMatrix(double val) {
  for(uint8_t i=0; i < Rows(); i++)
    for(uint8_t j=0; j < Columns(); j++)
      PutValue(i, j, val);
}

inline double** Matrix::GetMatrix() { return mat; }

inline uint8_t Matrix::Rows() { return rows; }

inline uint8_t Matrix::Columns() { return columns; }

void Matrix::Multiply(Matrix* mat1, Matrix* mat2, Matrix& outMat) {
  uint8_t resultRows = mat1->Rows();
  uint8_t resultColumns = mat2->Columns();
  //TODO outMat resultMat
  if(mat1->Columns() != mat2->Rows()) {
    Logger::Error("Trying to multiply matrix of size %dx%d by matrix of size %dx%d, which cannot be done!", mat1->Rows(), mat1->Columns(), mat2->Rows(), mat2->Columns());
    return; // TODO error?? read throw std::runtime_error()
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

std::string Matrix::ToString() {
  std::string result = "";
  result += "Matrix<" + std::to_string(GetID()) + "> of size: " + std::to_string(rows) + "x" + std::to_string(columns) + "\n";
  for(int r=0; r<rows; r++){
    for(int c=0; c<columns; c++){
      result += "(" + std::to_string(r) + "," + std::to_string(c) + ")" +std::to_string(GetValue(r, c)) + " ";
    }
    result += "\n";
  }
  return result;
}

inline uint8_t Matrix::GetID() { return ID; }

inline void Matrix::Init(uint8_t rows, uint8_t columns, double defaultVal) {
  ID = nextID++;
  mat = new double*[rows];
  for(int i = 0; i < rows; i++)
      mat[i] = new double[columns];

  ResetMatrix(defaultVal);
  Logger::Log(Logger::FontColor::GREEN, "[+] Creating matrix of size %dx%d", rows, columns);
}

#endif /* _MATRIX_HPP_ */
