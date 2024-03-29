#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>
#include <string>

#include <Logging/ExceptionsHandler.hpp>
#include <Math/Math.hpp>

/**
 * @brief Represents the mathematical matrix and is able to preform matrix calculations.
 *
 * @details This matrix class assumes that x value is the number of a column and y value is the number of a row.
 * This means that matrix[3][2] is value in 3rd row and 2nd column.
 * Also height says how many rows there are and width says how many columns there are.
 *
 * @tparam T Types of values held in this matrix.
 */
template <class T>
class Matrix
{
public:
  /**
   * @brief This constructor does not reserves the memory for the matrix's array. It only creates memory space for matrix pointer.
   * This means that pointer will be accesiable but no value can be put inside of if. The matrix will be of size 0x0.
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

  /**
   * @brief Adds #other matrix to this one. Each value at according x and y position will be added to each other. If sizes of matrixes do not match no changes will be done.
   *
   * @param other Added matrix. No changes will be done on this matrix.
   * @return Matrix<T>& Reference to *this matrix with values added.
   */
  Matrix<T> &operator+=(const Matrix<T> &other) noexcept;

  /**
   * @brief Adds #l list to this matrix. If sizes of matrixes do not match no changes will be done.
   *
   * @param l initializer list that fits the convention of #mat convention. For example for 3x3 matrix it will be: {x11, x21, x31, x12, x22, x32, x13, x23, x33}
   * @return Matrix<T>& Reference to *this matrix with values added.
   */
  Matrix<T> &operator+=(std::initializer_list<T> l) noexcept;

  /**
   * @brief Adds #value to each value in this matrix.
   *
   * @param value Value that will be added to each positions in this matrix.
   * @return Matrix<T>& Reference to *this matrix with values added.
   */
  Matrix<T> &operator+=(const T value) noexcept;

  /**
   * @brief Substracts #other matrix to this one. Each value at according x and y position will be substracted to each other. If sizes of matrixes do not match no changes will be done.
   *
   * @param other Substracted matrix. No changes will be done on this matrix.
   * @return Matrix<T>& Reference to *this matrix with values substracted.
   */
  Matrix<T> &operator-=(const Matrix<T> &other) noexcept;

  /**
   * @brief Substracts #l list to this matrix. If sizes of matrixes do not match no changes will be done.
   *
   * @param l initializer list that fits the convention of #mat convention. For example for 3x3 matrix it will be: {x11, x21, x31, x12, x22, x32, x13, x23, x33}
   * @return Matrix<T>& Reference to *this matrix with values substracted.
   */
  Matrix<T> &operator-=(std::initializer_list<T> l) noexcept;

  /**
   * @brief Substracts #value to each value in this matrix.
   *
   * @param value Value that will be substracted to each positions in this matrix.
   * @return Matrix<T>& Reference to *this matrix with values substracted.
   */
  Matrix<T> &operator-=(const T value) noexcept;

  /**
   * @brief Multiplies this matrix by #other. If sizes of matrixes do not match no changes will be done.
   *
   * @param other Matrix by which this one will be multiplied. #other matrix will remain unchanged.
   * @return Matrix<T>& Reference to *this matrix multiplied by #other.
   */
  Matrix<T> &operator*=(const Matrix<T> &other) noexcept;

  /**
   * @brief Multiplies this matrix by matrix made from #l initializer list.
   *
   * @param l initializer list that fits the convention of #mat convention. For example for 3x3 matrix it will be: {x11, x21, x31, x12, x22, x32, x13, x23, x33}
   * @return Matrix<T>& Reference to *this matrix that was multiplied by matrix created from #l list.
   */
  Matrix<T> &operator*=(std::initializer_list<T> l) noexcept;

  /**
   * @brief Multiplies each value of this matrix by #value.
   *
   * @param value Value by which value at each position of this matrix will be multiplied.
   * @return Matrix<T>& Reference to *this matrix with values multiplied.
   */
  Matrix<T> &operator*=(const T value) noexcept;

  /**
   * @brief Divides this matrix by #other matrix. Each value at according x and y position will be divided to each other. If sizes of matrixes do not match no changes will be done.
   *
   * @param other Matrix by which values this matrix will be divided. No changes will be done on this matrix.
   * @return Matrix<T>& Reference to *this matrix with values divided.
   */
  Matrix<T> &operator/=(const Matrix<T> &other) noexcept;

  /**
   * @brief Divides each value of this matrix by #value.
   *
   * @param value Value by which value at each position of this matrix will be divided.
   * @return Matrix<T>& Reference to *this matrix with values divided.
   */
  Matrix<T> &operator/=(const T value) noexcept;

  /**
   * @brief Mimic #other matrix. Takes it's height, width and values and copies it to self.
   * @details No changes will be done on #other matrix. Data held until this point on this matrix will be lost.
   * It rewrites this matrix to fit #other matrix size (Only if needed realloc will be done - if this matrix is bigger or equal to #other matrix size only #height and #width values will change).
   * Then using memcpy copies values stored in #other matrix.
   *
   * @param other Matrix from which copy will be performed.
   * @return Matrix<T>& Reference to *this matrix with values and size exactly the same as #other matrix.
   */
  Matrix<T> &operator=(const Matrix<T> &other) noexcept;

  /**
   * @brief Mimic values stored in #l initializer list.
   * @details It takes values stored in #l list and copies it into this matrix array. If reallocation is needed it will be done (Only if the size of this matrix is too small).
   * It allows us to set matrix's values at each position or one value for every position.
   * For example for matrix mat of size 2x2 You can perform mat = {1, 3, 2, 4}; which will result in matrix with first row = [1, 2] and second row = [3, 4]
   * Or You can perfoem mat = {1}; which will result in first row = [1, 1] and second row = [1, 1].
   *
   * @param l initializer list that fits the convention of #mat convention. For example for 3x3 matrix it will be: {x11, x21, x31, x12, x22, x32, x13, x23, x33}
   * @return Matrix<T>& Reference to *this matrix with values and size exactly the same as #l initializer list says.
   */
  Matrix<T> &operator=(std::initializer_list<T> l) noexcept;

  /**
   * @brief Method comparing two matrixes. It firstly checks the sizes. Then the types and at last values at each position.
   *
   * @param other Value to which this one is compared.
   * @return true If everything is eaxctly the same in these matrixes.
   * @return false If something is not the same in these matrixes.
   */
  bool operator==(const Matrix<T> &other) noexcept;

  /**
   * @brief Method comparing two matrixes. It firstly checks the sizes. Then the types and at last values at each position.
   *
   * @param other Value to which this one is compared.
   * @return true If something is not the same in these matrixes.
   * @return false If everything is eaxctly the same in these matrixes.
   */
  bool operator!=(const Matrix<T> &other) noexcept;

  /**
   * @brief Getter for values in this matrix. It allows us to perform 2D array-style value getting or getter for pointer to each column.
   * @details For example for matrix mat of size 2x2 with first row = [1, 2] and second row = [3, 4]
   * You will get: mat[0][0] = 1, mat[0][1] = 3, mat[1, 0] = 3, mat[1][1] = 4
   * And also: mat[0] will give You pointer to first column which is [1, 3].
   *
   * @param x Index of an column
   * @return T* Pointer to the column. You can the recursivly perform another [] operator to get the 'y' value of this matrix.
   */
  T *operator[](int x) const noexcept;

  /**
   * @brief Resets matrix's values. Whole matrix will be filled with #val value.
   *
   * @param val Value that will be set to each position of this matrix.
   */
  void Reset(T val) noexcept;

  /**
   * @brief Tranform this matrix to identity matrix. It will lost all values saved in a matrix.
   *
   * @details Creates identity matrix of size #height x #width and copies it to this matrix. Regardless of it's size.
   * If matrix is not quadtaric it will be filled with zeros and first (looking from left) diagonale will be filled with ones.
   */
  void MakeIdentity() noexcept;

  static constexpr uint32_t MAX_MATRIX_SIZE{4096}; //!< Maximum size of a matrix that calculation will be performed on. This is a theoreticall value and if some calculation will be done on bigger matrix bad things happens.

protected:
  uint32_t _height{0};    //!< Amount of Height in the matrix.
  uint32_t _width{0};     //!< Amount of Width in the matrix.
  uint32_t _totalSize{0}; //!< Total size is a multiplied values of a height and a width. It is a count f elements in an array of #mat.

  T *p_mat{nullptr}; //!< Array of matrix's values. It is linear despite matrix being 2-dimensional. It is more efficiently.

  inline static T _TMPMAT[Matrix::MAX_MATRIX_SIZE]; //!< second matrix allocated only once. This matrix is used for calculation purposes. It allows us to safely multiply matrixes without a need to allocate more memory.
};

template <class E>
inline Matrix<E>::Matrix() : _height(0), _width(0)
{
  _totalSize = 0;
}

template <class E>
inline Matrix<E>::Matrix(uint32_t _height, uint32_t _width) : _height(_height), _width(_width)
{
  _totalSize = _height * _width;
  if (_totalSize == 0)
    return;
  p_mat = new E[_totalSize];
}

template <class E>
inline Matrix<E>::Matrix(uint32_t _height, uint32_t _width, E _defaultVal) : _height(_height), _width(_width)
{
  _totalSize = _height * _width;
  if (_totalSize == 0)
    return;
  p_mat = new E[_totalSize];

  *this = {_defaultVal};
}

template <class E>
Matrix<E>::Matrix(Matrix<E> &other) : _height(other.Height()), _width(other.Width())
{
  // if (totalSize != (other.Height() * other.Width()))
  // {
  //   if (mat != nullptr)
  //     delete[] mat;
  //   mat = nullptr;
  //    // TODO use realloc!!!!
  // }
  _totalSize = _height * _width;
  p_mat = new E[_totalSize];

  memcpy(p_mat, other.p_mat, sizeof(E) * _totalSize);
}

template <class E>
inline Matrix<E>::~Matrix()
{
  if (p_mat != nullptr)
    delete[] p_mat;
}

template <class E>
inline uint32_t Matrix<E>::Height() const { return _height; }

template <class E>
inline uint32_t Matrix<E>::Width() const { return _width; }

template <class E>
Matrix<E> &Matrix<E>::operator+=(const Matrix<E> &other) noexcept
{
  if (_height != other.Height() || _width != other.Width())
  {
    Logger::Log("%zu %zu", _height, _width);
    ExceptionsHandler::ThrowWarning("Trying to add matrixes with different sizes! (%zu x %zu) | (%zu x %zu)", _height, _width, other._height, other._width);
    return *this;
  }

  for (int i = 0; i < _totalSize; i++)
  {
    p_mat[i] += other.p_mat[i];
  }

  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator+=(std::initializer_list<E> l) noexcept
{
  if (_totalSize != l.size())
  {
    ExceptionsHandler::ThrowWarning("Trying to add matrixes with different sizes! (%d) | {%d}", _totalSize, l.size());
    return *this;
  }

  for (int i = 0; i < _totalSize; i++)
  {
    p_mat[i] += l.begin()[i];
  }

  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator+=(const E value) noexcept
{
  for (int i = 0; i < _totalSize; i++)
  {
    p_mat[i] += value;
  }
  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator-=(const Matrix<E> &other) noexcept
{
  if (_height != other._height || _width != other._width)
  {
    ExceptionsHandler::ThrowWarning("Trying to substract matrixes with different sizes! (%zu x %zu) | (%zu x %zu)", _height, _width, other._height, other._width);
    return *this;
  }

  for (int i = 0; i < _totalSize; i++)
  {
    p_mat[i] -= other.p_mat[i];
  }

  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator-=(std::initializer_list<E> l) noexcept
{
  if (_totalSize != l.size())
  {
    ExceptionsHandler::ThrowWarning("Trying to substract matrixes with different sizes! (%d) | {%d }", _totalSize, l.size());
    return *this;
  }

  for (int i = 0; i < _totalSize; i++)
  {
    p_mat[i] -= l.begin()[i];
  }

  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator-=(const E value) noexcept
{
  for (int i = 0; i < _totalSize; i++)
  {
    p_mat[i] -= value;
  }
  return *this;
}

template <class E> // TODO refactor
Matrix<E> &Matrix<E>::operator*=(const Matrix<E> &other) noexcept
{
  if (_width != other._height)
  {
    Logger::Log("%zu %zu", _width, _height);
    ExceptionsHandler::ThrowWarning("Trying to multiply matrixes with not compatible sizes! (%zu x %zu) | (%zu x %zu)", _height, _width, other._height, other._width);
    return *this;
  }

  for (int y = 0; y < _height; y++)
  {
    for (int x = 0; x < other.Height(); x++)
    {
      *(_TMPMAT + (x * _height) + y) *= 0.0;
      for (int i = 0; i < other.Height(); i++)
      {
        *(_TMPMAT + (x * _height) + y) += (*this)[i][y] * other[x][i];
      }
    }
  }
  _width = other._width;
  if (_height * _width > _totalSize)
  {
    delete[] p_mat; // TODO use realloc!!!!
    p_mat = new E[_height * _width];
  }
  _totalSize = _width * _height;
  memcpy(p_mat, _TMPMAT, _totalSize * sizeof(E));
  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator*=(std::initializer_list<E> l) noexcept
{
  static uint32_t otherWidth;
  static uint32_t otherHeight;
  otherWidth = l.size() / _width;
  otherHeight = l.size() / _height;

  if (_width != otherHeight)
  {
    ExceptionsHandler::ThrowWarning("Trying to muyltiply matrixes with not comaptible sizes! (%d x %d) | {%d x %d}", _height, _width, otherHeight, otherWidth);
    return *this;
  }

  for (int y = 0; y < _height; y++)
  {
    for (int x = 0; x < otherHeight; x++)
    {
      *(_TMPMAT + (x * _height) + y) *= 0.0;
      for (int i = 0; i < otherHeight; i++)
      {
        *(_TMPMAT + (x * _height) + y) += (*this)[i][y] * (*(l.begin() + (x * otherHeight) + i));
      }
    }
  }

  _width = otherWidth;
  _totalSize = _width * _height;
  memcpy(p_mat, _TMPMAT, _totalSize * sizeof(E));

  return *this; // TODO wywołuje powstanie nowej macierzy
}

template <class E>
Matrix<E> &Matrix<E>::operator*=(const E value) noexcept
{
  for (int i = 0; i < _totalSize; i++)
  {
    p_mat[i] *= value;
  }
  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator/=(const Matrix<E> &other) noexcept
{
  if (_height != other._height || _width != other._width)
  {
    ExceptionsHandler::ThrowWarning("Trying to divide matrixes with different sizes! (%zu x %zu) | (%zu x %zu)", _height, _width ,  other._height, other._width);
    return *this;
  }

  for (int i = 0; i < _totalSize; i++)
  {
    p_mat[i] /= other.p_mat[i];
  }

  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator/=(const E value) noexcept
{
  for (int i = 0; i < _totalSize; i++)
  {
    p_mat[i] /= value;
  }
  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator=(const Matrix<E> &other) noexcept
{
  // Logger::Log("Start = with matrix");
  if (this == &other)
    return *this;

  if (_totalSize != (other.Height() * other.Width()))
  {
    if (p_mat != nullptr)
      delete[] p_mat;
    p_mat = nullptr;
    p_mat = new E[other._totalSize]; // TODO use realloc!!!!
  }

  _height = other.Height();
  _width = other.Width();
  _totalSize = _width * _height;

  memcpy(p_mat, other.p_mat, sizeof(E) * _totalSize);
  // Logger::Log("End = with matrix");
  return *this;
}

template <class E>
Matrix<E> &Matrix<E>::operator=(std::initializer_list<E> l) noexcept
{
  // Logger::Log("Start = with init list");
  const E *ptL = l.begin();

  if (l.size() == 1)
  {
    for (uint32_t i = 0; i < _totalSize; i++)
      p_mat[i] = *l.begin();
  }
  else if (l.size() == _totalSize)
  {
    memcpy(p_mat, l.begin(), _totalSize * sizeof(E));
  }
  // Logger::Log("End = with init list");
  return *this;
}

template <class E>
E *Matrix<E>::operator[](int x) const noexcept
{
  return p_mat + ((x * Height()) % _totalSize);
}

template <class E>
bool Matrix<E>::operator==(const Matrix<E> &other) noexcept
{
  if (_height != other.Height() || _width != other.Width())
    return false;

  for (uint32_t x = 0; x < _width; x++)
  {
    for (uint32_t y = 0; y < _height; y++)
      if ((*this)[x][y] != other[x][y]) // FIXME double equals does not fir parametrized class!!!!
      {
        return false;
      }
  }

  return true;
}

template <class E>
bool Matrix<E>::operator!=(const Matrix<E> &other) noexcept
{
  if (_height != other.Height() || _width != other.Width())
    return true;

  for (uint32_t x = 0; x < _width; x++)
  {
    for (uint32_t y = 0; y < _height; y++)
      if ((*this)[x][y] != other[x][y]) // FIXME double equals does not fir parametrized class!!!!
      {
        return true;
      }
  }

  return false;
}

template <class E>
void Matrix<E>::Reset(E val) noexcept
{
  for (uint32_t i = 0; i < _totalSize; i++)
    p_mat[i] = val;
}

template <class E>
void Matrix<E>::MakeIdentity() noexcept // FIXME does not work for different matrixes than numeric-wise
{
  Reset(0.0);
  uint32_t minSize = _width < _height ? _width : _height;
  for (uint32_t i = 0; i < minSize; i++)
    (*this)[i][i] = 1.0;
}

#endif /* _MATRIX_HPP_ */
