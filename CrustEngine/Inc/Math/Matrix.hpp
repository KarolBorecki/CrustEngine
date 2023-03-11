#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>
#include <string>

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
  Matrix(uint32_t height, uint32_t width); // TODO 8bits for matrix size is too low
  /**
   * @brief If width or height argument is zero then no space for matrix's array will be allocated.
   * @param Height Amount of Height in the matrix.
   * @param Width Amount of Width in the matrix.
   * @param defaultVal The value that will be placed on each position in matrix.
   */
  Matrix(uint32_t height, uint32_t width, T defaultVal);
  /**
   * @details If #mat is not null deletes it from the heap.
   */
  ~Matrix();

  /**
   * @brief Getter for #Height field.
   *
   * @return Amount of Height in matrix.
   */
  uint8_t Height() const;
  /**
   * @brief Getter for #Width field.
   *
   * @return Amount of Width in matrix
   */
  uint8_t Width() const;

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
  uint32_t height{0}; //!< Amount of Height in the matrix.
  uint32_t width{0};  //!< Amount of Width in the matrix.
  uint32_t totalSize{0}; //!< Total size is a multiplied values of a height and a width. It is a count f elements in an array of #mat.

  T *mat { nullptr }; //!< Array of matrix's values. It is linear despite matrix being 2-dimensional. It is more efficiently.
};

template <class E>
inline Matrix<E>::Matrix() : height(0), width(0)
{
  totalSize = 0;
}

template <class E>
inline Matrix<E>::Matrix(uint32_t _height, uint32_t _width) : height(_height), width(_width)
{
  totalSize = _height * _width;
  if (totalSize == 0)
    return;
  mat = new E[totalSize];
}

template <class E>
inline Matrix<E>::Matrix(uint32_t _height, uint32_t _width, E _defaultVal) : height(_height), width(_width)
{
  totalSize = _height * _width;
  if (totalSize == 0)
    return;
  mat = new E[totalSize];

  *this = { _defaultVal };
}

template <class E>
inline Matrix<E>::~Matrix()
{
  if(mat != nullptr) 
    delete[] mat;
}

template <class E>
inline uint8_t Matrix<E>::Height() const { return height; }

template <class E>
inline uint8_t Matrix<E>::Width() const { return width; }

template <class E>
Matrix<E> &Matrix<E>::operator+=(const Matrix<E> &other) noexcept
{
  if (height != other.Height() || width != other.Width())
    return *this; // TODO add warning

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
    return *this; // TODO add warning

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
    return *this; // TODO add warning

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
    return *this; // TODO add warning

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

template <class E>
Matrix<E> &Matrix<E>::operator*=(const Matrix<E> &other) noexcept
{
  if (width != other.height)
    return *this; // TODO add warning

  Matrix<E> result(width, other.height, 0.0);
  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < other.Height(); x++)
    {
      for (int i = 0; i < other.Height(); i++)
      {
        result[x][y] += (*this)[i][y] * other[x][i];
      }
    }
  }
  
  *this = result; // TODO it is kinda not good
  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator*=(std::initializer_list<E> l) noexcept
{
  Matrix<E> other(l.size() / height, l.size() / width);
  other = l;

  if (width != other.height)
    return *this; // TODO add warning

  Matrix<E> result(height, other.width);
  E *matPointer;
  for (int x = 0; x < other.width; x++)
  {
    matPointer = *this[x];
    for (int y = 0; y < height; y++)
    {
      result[x][y] *= 0;
      for (int i = 0; i < other.height; i++)
      {
        result[x][y] += *this[i][y] * other[x][i];
      }
    }
  }
  *this = result; // TODO it is kind not good
  return *this;
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
    return *this; // TODO add warning

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
  if (this == &other)
    return *this;

  if (totalSize != (other.Height() * other.Width()))
  {
    delete[] mat;
    mat = nullptr;
    mat = new E[other.totalSize];
  }

  height = other.Height();
  width = other.Width();
  totalSize = width * height;

  memcpy(mat, other.mat, sizeof(E) * totalSize);

  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator=(std::initializer_list<E> l) noexcept
{
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
  if(height != other.Height() || width != other.Width())
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
