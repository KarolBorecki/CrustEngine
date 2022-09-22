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
  * @param _rows Amount of rows in the matrix.
  * @param _columns Amount of columns in the matrix.
  */
  Matrix(int _rows, int _columns);
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
  double GetValue(int row, int column);
  /**
  * @brief Puts the given value on the given position.
  *
  * @param row The y index of the position in matrix.
  * @param column The x index of the position in matrix.
  */
  void PutValue(int row, int column, double value);

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
  int Rows();
  /**
  * @brief Getter for #columns field.
  *
  * @return Amount of columns in matrix
  */
  int Columns();

  /**
  * @brief Multiplies given matrixes.
  *
  * @details Multiplies matrixes as the mat1 * mat2 and returns new object of type matrix being te result of multiplication.
  * The original mat1 and mat2 objects remains not modified by this method.
  *
  * @param mat1 First matrix.
  * @param mat2 Second matrix, by which first is being multiplied.
  */
  static Matrix Multiply(Matrix* mat1, Matrix* mat2);

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
  int rows { 0 }; //!< Amount of rows in the matrix.
  int columns { 0 }; //!< Amount of columns in the matrix.
  double** mat { nullptr }; //!< Array of matrix's values.

  uint8_t ID; //!< Matrix's ID.
  static inline uint8_t nextID { 0 }; //!< Next matrix ID. Also holds amount of matrixes created on engine work. Only for debug purposes.
};

inline Matrix::Matrix(int _rows, int _columns) : rows(_rows), columns(_columns) {
  ID = nextID++;
  mat = new double*[rows];
  for (int i = 0; i < rows; ++i)
      mat[i] = new double[columns];
}

inline Matrix::~Matrix() {
  Logger::Info("[X] Deleting Mat<%d> %dx%d", GetID(), Rows(), Columns());
  if (mat == nullptr) return;
  for (int i = 0; i < rows; ++i)
    delete [] mat[i];
delete [] mat;
}

inline double Matrix::GetValue(int row, int column) {
  return mat[row][column];
}

inline void Matrix::PutValue(int row, int column, double value) {
  mat[row][column] = value;
}

inline double** Matrix::GetMatrix() { return mat; }

inline int Matrix::Rows() { return rows; }

inline int Matrix::Columns() { return columns; }

/* TODO TEST */
Matrix Matrix::Multiply(Matrix* mat1, Matrix* mat2) {
  int resultRows = mat1->Rows();
  int resultColumns = mat2->Columns();
  Matrix resultMat(resultRows, resultColumns);

  if(mat1->Columns() != mat2->Rows()) {
    Logger::Error("Trying to multiply matrix of size %dx%d by matrix of size %dx%d, which cannot be done!", mat1->Rows(), mat1->Columns(), mat2->Rows(), mat2->Columns());
    return resultMat; // TODO error?? read throw std::runtime_error()
  }

  for(int r=0; r<resultRows; r++) {
    for(int c=0; c<resultColumns; c++) {
      double value = 0;
      for(int i=0; i<mat2->Rows(); i++) {
        value += mat1->GetValue(r, i) * mat2->GetValue(i, c);
      }
      resultMat.PutValue(r, c, value);
    }
  }
  return resultMat;
}

std::string Matrix::ToString() {
  std::string result = "";
  result += "Matrix of size: " + std::to_string(rows) + "x" + std::to_string(columns) + "\n";
  for(int r=0; r<rows; r++){
    for(int c=0; c<columns; c++){
      result += "(" + std::to_string(r) + "," + std::to_string(c) + ")" +std::to_string(GetValue(r, c)) + " ";
    }
    result += "\n";
  }
  return result;
}

inline uint8_t Matrix::GetID() { return ID; }

#endif /* _MATRIX_HPP_ */
