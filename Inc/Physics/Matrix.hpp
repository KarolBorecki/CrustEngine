#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>
#include <string>

class Matrix {
public:
  Matrix(int _rows, int _columns);
  virtual ~Matrix();

  double GetValue(int row, int column);
  void PutValue(int row, int column, double value);

  double** GetMatrix();
  int Rows();
  int Columns();

  static Matrix Multiply(Matrix* mat1, Matrix* mat2);

  std::string ToString();

private:
  int rows { 0 };
  int columns { 0 };
  double** mat { nullptr };
};

inline Matrix::Matrix(int _rows, int _columns) : rows(_rows), columns(_columns) {
  mat = new double*[rows];
  for (int i = 0; i < rows; ++i)
      mat[i] = new double[columns];
}

inline Matrix::~Matrix() {
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

  if(mat1->Columns() != mat2->Rows()) return resultMat; // TODO error?? read throw std::runtime_error()

  for(int r=0; r<resultRows; r++) {
    for(int c=0; c<resultColumns; c++) {
      double value = 0;
      for(int i=0; i<mat1->Rows(); i++) {
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

#endif /* _MATRIX_HPP_ */
