#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>
#include <string>

#include <Logging/ExceptionsHandler.hpp>
#include <Math/Math.hpp>

/**
 * @brief Represents the mathematical matrix and is able to preform matrix calculations.
 */
template <class T>
class Matrix
{
public:
  /**
   * @brief This constructor does not reserves the memory for the matrix's array. It only creates memory space for matrix pointer
   */
  Matrix();

  /**
   * @brief If any argument is zero then no space for matrix's array will be allocated.
   * @param Height Amount of Height in the matrix.
   * @param Width Amount of Width in the matrix.
   */
  Matrix(uint32_t height, uint32_t width);
  /**
   * @brief If width or height argument is zero then no space for matrix's array will be allocated.
   * @param Height Amount of Height in the matrix.
   * @param Width Amount of Width in the matrix.
   * @param defaultVal The value that will be placed on each position in matrix.
   */
  Matrix(uint32_t height, uint32_t width, T defaultVal);

  Matrix(Matrix<T> &other); // Rule of 3/5/0
  /**
   * @details If #mat is not null deletes it from the heap.
   */
  ~Matrix();

  /**
   * @brief Getter for #Height field.
   *
   * @return Amount of Height in matrix.
   */
  uint32_t Height() const;
  /**
   * @brief Getter for #Width field.
   *
   * @return Amount of Width in matrix
   */
  uint32_t Width() const;

  Matrix<T> &operator+=(const Matrix<T> &other) noexcept;

  Matrix<T> &operator+=(std::initializer_list<T> l) noexcept;

  Matrix<T> &operator+=(const T value) noexcept;

  Matrix<T> &operator-=(const Matrix<T> &other) noexcept;

  Matrix<T> &operator-=(std::initializer_list<T> l) noexcept;

  Matrix<T> &operator-=(const T value) noexcept;

  Matrix<T> &operator*=(const Matrix<T> &other) noexcept;

  Matrix<T> &operator*=(std::initializer_list<T> l) noexcept;

  Matrix<T> &operator*=(const T value) noexcept;

  Matrix<T> &operator/=(const Matrix<T> &other) noexcept;

  Matrix<T> &operator/=(const T value) noexcept;

  Matrix<T> &operator=(const Matrix<T> &other) noexcept;

  Matrix<T> &operator=(std::initializer_list<T> l) noexcept;

  bool operator==(const Matrix<T> &other) noexcept;

  bool operator!=(const Matrix<T> &other) noexcept;

  T *operator[](int x) const noexcept;

protected:
  uint32_t height{0};    //!< Amount of Height in the matrix.
  uint32_t width{0};     //!< Amount of Width in the matrix.
  uint32_t totalSize{0}; //!< Total size is a multiplied values of a height and a width. It is a count f elements in an array of #mat.

  T *mat{nullptr}; //!< Array of matrix's values. It is linear despite matrix being 2-dimensional. It is more efficiently.

  inline static T *tmpMat{nullptr};
  static constexpr uint32_t MAX_MATRIX_SIZE{4096};
};

template <class E>
inline Matrix<E>::Matrix() : height(0), width(0)
{
  if (tmpMat == nullptr)
    tmpMat = new E[MAX_MATRIX_SIZE * MAX_MATRIX_SIZE];
  totalSize = 0;
}

template <class E>
inline Matrix<E>::Matrix(uint32_t _height, uint32_t _width) : height(_height), width(_width)
{
  if (tmpMat == nullptr)
    tmpMat = new E[MAX_MATRIX_SIZE * MAX_MATRIX_SIZE];

  totalSize = _height * _width;
  if (totalSize == 0)
    return;
  mat = new E[totalSize];
}

template <class E>
inline Matrix<E>::Matrix(uint32_t _height, uint32_t _width, E _defaultVal) : height(_height), width(_width)
{
  if (tmpMat == nullptr)
    tmpMat = new E[MAX_MATRIX_SIZE * MAX_MATRIX_SIZE];
  totalSize = _height * _width;
  if (totalSize == 0)
    return;
  mat = new E[totalSize];

  *this = {_defaultVal};
}

template <class E>
Matrix<E>::Matrix(Matrix<E> &other) : height(other.Height()), width(other.Width())
{
  if (totalSize != (other.Height() * other.Width()))
  {
    if (mat != nullptr)
      delete[] mat;
    mat = nullptr;
    mat = new E[other.totalSize]; // TODO use realloc!!!!
  }

  totalSize = width * height;

  memcpy(mat, other.mat, sizeof(E) * totalSize);
}

template <class E>
inline Matrix<E>::~Matrix()
{
  if (mat != nullptr)
    delete[] mat;
}

template <class E>
inline uint32_t Matrix<E>::Height() const { return height; }

template <class E>
inline uint32_t Matrix<E>::Width() const { return width; }

template <class E>
Matrix<E> &Matrix<E>::operator+=(const Matrix<E> &other) noexcept
{
  if (height != other.Height() || width != other.Width())
  {
    ExceptionsHandler::ThrowWarning("Trying to add matrixes with different sizes!");
    return *this;
  }

  for (int i = 0; i < totalSize; i++)
  {
    mat[i] += other.mat[i];
  }

  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator+=(std::initializer_list<E> l) noexcept
{
  if (totalSize != l.size())
  {
    ExceptionsHandler::ThrowWarning("Trying to add matrixes with different sizes!");
    return *this;
  }

  for (int i = 0; i < totalSize; i++)
  {
    mat[i] += l.begin()[i];
  }

  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator+=(const E value) noexcept
{
  for (int i = 0; i < totalSize; i++)
  {
    mat[i] += value;
  }
  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator-=(const Matrix<E> &other) noexcept
{
  if (height != other.height || width != other.width)
  {
    ExceptionsHandler::ThrowWarning("Trying to substract matrixes with different sizes!");
    return *this;
  }

  for (int i = 0; i < totalSize; i++)
  {
    mat[i] -= other.mat[i];
  }

  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator-=(std::initializer_list<E> l) noexcept
{
  if (totalSize != l.size())
  {
    ExceptionsHandler::ThrowWarning("Trying to substract matrixes with different sizes!");
    return *this;
  }

  for (int i = 0; i < totalSize; i++)
  {
    mat[i] -= l.begin()[i];
  }

  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator-=(const E value) noexcept
{
  for (int i = 0; i < totalSize; i++)
  {
    mat[i] -= value;
  }
  return *this;
}

template <class E> // TODO refactor
Matrix<E> &Matrix<E>::operator*=(const Matrix<E> &other) noexcept
{
  if (width != other.height)
  {
    ExceptionsHandler::ThrowWarning("Trying to multiply matrixes with not compatible sizes!");
    return *this;
  }

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < other.Height(); x++)
    {
      *(tmpMat + (x * width) + y) *= 0.0;
      for (int i = 0; i < other.Height(); i++)
      {
        *(tmpMat + (x * width) + y) += (*this)[i][y] * other[x][i];
      }
    }
  }

  height = width;
  width = other.height;
  if (height * width > totalSize)
  {
    delete[] mat;
    mat = new E[height * width];
  }
  totalSize = width * height;
  memcpy(mat, tmpMat, totalSize * sizeof(E));
  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator*=(std::initializer_list<E> l) noexcept
{
  static uint32_t otherWidth;
  static uint32_t otherHeight;
  otherWidth = l.size() / width;
  otherHeight = l.size() / height;

  if (width != otherHeight)
  {
    ExceptionsHandler::ThrowWarning("Trying to muyltiply matrixes with not comaptible sizes!");
    return *this;
  }

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < otherHeight; x++)
    {
      *(tmpMat + (x * width) + y) *= 0.0;
      for (int i = 0; i < otherHeight; i++)
      {
        *(tmpMat + (x * width) + y) += (*this)[i][y] * (*(l.begin() + (x * otherHeight) + i));
      }
    }
  }

  height = width;
  width = otherHeight;
  totalSize = width * height;
  memcpy(mat, tmpMat, totalSize * sizeof(E));

  return *this; // TODO wywołujepowstanie nowej macierzy
}

template <class E>
Matrix<E> &Matrix<E>::operator*=(const E value) noexcept
{
  for (int i = 0; i < totalSize; i++)
  {
    mat[i] *= value;
  }
  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator/=(const Matrix<E> &other) noexcept
{
  if (height != other.height || width != other.width)
  {
    ExceptionsHandler::ThrowWarning("Trying to divide matrixes with different sizes!");
    return *this;
  }

  for (int i = 0; i < totalSize; i++)
  {
    mat[i] /= other.mat[i];
  }

  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator/=(const E value) noexcept
{
  for (int i = 0; i < totalSize; i++)
  {
    mat[i] /= value;
  }
  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator=(const Matrix<E> &other) noexcept
{
  // Logger::Log("Start = with matrix");
  if (this == &other)
    return *this;

  if (totalSize != (other.Height() * other.Width()))
  {
    if (mat != nullptr)
      delete[] mat;
    mat = nullptr;
    mat = new E[other.totalSize]; // TODO use realloc!!!!
  }

  height = other.Height();
  width = other.Width();
  totalSize = width * height;

  memcpy(mat, other.mat, sizeof(E) * totalSize);
  // Logger::Log("End = with matrix");
  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator=(std::initializer_list<E> l) noexcept
{
  // Logger::Log("Start = with init list");
  const double *ptL = l.begin();

  if (l.size() == 1)
  {
    for (uint32_t i = 0; i < totalSize; i++)
      mat[i] = *l.begin();
  }
  else if (l.size() == totalSize)
  {
    memcpy(mat, l.begin(), totalSize * sizeof(E));
  }
  // Logger::Log("End = with init list");
  return *this;
}

template <class E>
E *Matrix<E>::operator[](int x) const noexcept
{
  return mat + ((x * Height()) % totalSize);
}

template <class E>
bool Matrix<E>::operator==(const Matrix<E> &other) noexcept
{
  if (height != other.Height() || width != other.Width())
    return false;

  for (uint32_t x = 0; x < width; x++)
  {
    for (uint32_t y = 0; y < height; y++)
      if (!Math::DoubleEquals((*this)[x][y], other[x][y]))
      {
        return false;
      }
  }

  return true;
}

template <class E>
bool Matrix<E>::operator!=(const Matrix<E> &other) noexcept
{
  if (height != other.Height() || width != other.Width())
    return true;

  for (uint32_t x = 0; x < width; x++)
  {
    for (uint32_t y = 0; y < height; y++)
      if (!Math::DoubleEquals((*this)[x][y], other[x][y]))
      {
        return true;
      }
  }

  return false;
}
#endif /* _MATRIX_HPP_ */
