#ifndef _Vector4_HPP_
#define _Vector4_HPP_

#include <Math/Vector4.hpp>

/**
 * @brief Represents mathematical vector4.
 */
template<class T = float, typename E = typename std::enable_if<std::is_floating_point<float>::value>::type>
class Vector4 : public Matrix<T>
{
public:
  /**
   * @brief Creates blank vector4 that consists of zeros.
   */
  Vector4();

  /**
   * @param valXYZ Value for each X, Y, Z and E fields.
   */
  Vector4(T valXYZW);

  /**
   * @param x Value for X field.
   * @param y Value for Y field.
   * @param z Value for Z field.
   * @param w Value for E field.
   */
  Vector4(T x, T y, T z, T w);
  ~Vector4();

    /**
   * @brief Getter for Vector4 x value.
   */
  T X() const;
  /**
   * @brief Getter for Vector4 y value.
   */
  T Y() const;
  /**
   * @brief Getter for Vector4 z value.
   */
  T Z() const;

    /**
   * @brief Getter for Vector4 z value.
   */
  T W() const;

  /**
   * @brief Setter for Vector4 x value.
   *
   * @param valX New value of vector's x.
   */
  void SetX(T valX);

  /**
   * @brief Setter for Vector4 y value.
   *
   * @param valY New value of vector's y.
   */
  void SetY(T valY);

  /**
   * @brief Setter for Vector4 z value.
   *
   * @param valZ New value of vector's z.
   */
  void SetZ(T valZ);

  /**
   * @brief Setter for Vector4 w value.
   *
   * @param valW New value of vector's w.
   */
  void SetW(T valW);

private:
  static inline constexpr uint8_t VECTOR4_WIDTH{4};
  static inline constexpr uint8_t VECTOR4_HEIGHT{1};
};

template <typename T, typename E>
inline Vector4<T, E>::Vector4() : Vector4(0, 0, 0, 0) {}

template <typename T, typename E>
inline Vector4<T, E>::Vector4(T valXYZW) : Vector4(valXYZW, valXYZW, valXYZW, valXYZW) {}

template <typename T, typename E>
inline Vector4<T, E>::Vector4(T x, T y, T z, T w) : Matrix<T>(VECTOR4_HEIGHT, VECTOR4_WIDTH)
{
  SetX(x);
  SetY(y);
  SetZ(z);
  SetW(w);
}

template <typename T, typename E>
inline Vector4<T, E>::~Vector4() {}

template <typename T, typename E>
inline T Vector4<T, E>::X() const { return (*this)[0][0]; }

template <typename T, typename E>
inline T Vector4<T, E>::Y() const { return (*this)[1][0]; }

template <typename T, typename E>
inline T Vector4<T, E>::Z() const { return (*this)[2][0]; }

template <typename T, typename E>
inline T Vector4<T, E>::W() const { return (*this)[3][0]; }

template <typename T, typename E>
inline void Vector4<T, E>::SetX(T valX) { (*this)[0][0] = valX; }

template <typename T, typename E>
inline void Vector4<T, E>::SetY(T valY) { (*this)[1][0] = valY; }

template <typename T, typename E>
inline void Vector4<T, E>::SetZ(T valZ) { (*this)[2][0] = valZ; }

template <typename T, typename E>
inline void Vector4<T, E>::SetW(T valW) { (*this)[3][0] = valW; }

#endif /* _Vector4_HPP_ */
