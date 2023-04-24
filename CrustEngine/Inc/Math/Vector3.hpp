#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

#include <Math/Matrix.hpp>

//TODO add optional template for this class so wwe are able to use float instead of double 
/**
 * @brief Represents mathematical vector3.
 */
//template<typename T=float, typename = std::enable_if_t<std::is_floating_point_v<T>>>
template<class T = float, typename W = typename std::enable_if<std::is_floating_point<T>::value>::type>
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
  static inline constexpr uint8_t VECTOR3_WIDTH{3};
  static inline constexpr uint8_t VECTOR3_HEIGHT{1};
};

template <typename T, typename W>
inline Vector3<T, W>::Vector3() : Vector3(0, 0, 0) {}

template <typename T, typename W>
inline Vector3<T, W>::Vector3(T valXYZ) : Vector3(valXYZ, valXYZ, valXYZ) {}

template <class T, typename W>
inline Vector3<T, W>::Vector3(T x, T y, T z) : Matrix<T>(VECTOR3_HEIGHT, VECTOR3_WIDTH)
{
  SetX(x);
  SetY(y);
  SetZ(z);
}

template <typename T, typename W>
inline Vector3<T, W>::~Vector3() {}

template <typename T, typename W>
inline T Vector3<T, W>::X() const { return (*this)[0][0]; }

template <typename T, typename W>
inline T Vector3<T, W>::Y() const { return (*this)[1][0]; }

template <typename T, typename W>
inline T Vector3<T, W>::Z() const { return (*this)[2][0]; }

template <typename T, typename W>
inline void Vector3<T, W>::SetX(T valX) { (*this)[0][0] = valX; }

template <typename T, typename W>
inline void Vector3<T, W>::SetY(T valY) { (*this)[1][0] = valY; }

template <typename T, typename W>
inline void Vector3<T, W>::SetZ(T valZ) { (*this)[2][0] = valZ; }

#endif /* _VECTOR3_HPP_ */
