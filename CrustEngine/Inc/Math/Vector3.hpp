#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

#include <Math/Matrix.hpp>

/**
 * @brief Represents mathematical vector3.
 */
template<class T = float, typename E = typename std::enable_if<std::is_floating_point<T>::value>::type>
class Vector3 : public Matrix<T>
{
public:
  /**
   * @brief Creates blank vector that consists of zeros.
   */
  Vector3();
  /**
   * @param valXYZ Value for each X, Y and Z fields.
   */
  Vector3(T valXYZ);
  /**
   * @param x Value for X field.
   * @param y Value for Y field.
   * @param z Value for Z field.
   */
  Vector3(T x, T y, T z);
  ~Vector3();

  /**
   * @brief Getter for Vector3 x value.
   */
  T X() const;
  /**
   * @brief Getter for Vector3 y value.
   */
  T Y() const;
  /**
   * @brief Getter for Vector3 z value.
   */
  T Z() const;

  /**
   * @brief Setter for Vector3 x value.
   *
   * @param valX New value of vector's x.
   */
  void SetX(T valX);

  /**
   * @brief Setter for Vector3 y value.
   *
   * @param valY New value of vector's y.
   */
  void SetY(T valY);

  /**
   * @brief Setter for Vector3 z value.
   *
   * @param valZ New value of vector's z.
   */
  void SetZ(T valZ);

private:
  static inline constexpr uint8_t _VECTOR3_WIDTH{3};
  static inline constexpr uint8_t _VECTOR3_HEIGHT{1};
};

template <typename T, typename E>
inline Vector3<T, E>::Vector3() : Vector3(0, 0, 0) {}

template <typename T, typename E>
inline Vector3<T, E>::Vector3(T valXYZ) : Vector3(valXYZ, valXYZ, valXYZ) {}

template <class T, typename E>
inline Vector3<T, E>::Vector3(T x, T y, T z) : Matrix<T>(_VECTOR3_HEIGHT, _VECTOR3_WIDTH)
{
  SetX(x);
  SetY(y);
  SetZ(z);
}

template <typename T, typename E>
inline Vector3<T, E>::~Vector3() {}

template <typename T, typename E>
inline T Vector3<T, E>::X() const { return (*this)[0][0]; }

template <typename T, typename E>
inline T Vector3<T, E>::Y() const { return (*this)[1][0]; }

template <typename T, typename E>
inline T Vector3<T, E>::Z() const { return (*this)[2][0]; }

template <typename T, typename E>
inline void Vector3<T, E>::SetX(T valX) { (*this)[0][0] = valX; }

template <typename T, typename E>
inline void Vector3<T, E>::SetY(T valY) { (*this)[1][0] = valY; }

template <typename T, typename E>
inline void Vector3<T, E>::SetZ(T valZ) { (*this)[2][0] = valZ; }

#endif /* _VECTOR3_HPP_ */
