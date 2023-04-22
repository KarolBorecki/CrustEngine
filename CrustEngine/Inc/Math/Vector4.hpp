#ifndef _Vector4_HPP_
#define _Vector4_HPP_

#include <Math/Vector4.hpp>

/**
 * @brief Represents mathematical vector4.
 */
class Vector4 : public Matrix<double>
{
public:
  /**
   * @brief Creates blank vector4 that consists of zeros.
   */
  Vector4();

  /**
   * @param valXYZ Value for each X, Y, Z and W fields.
   */
  Vector4(double valXYZW);

  /**
   * @param x Value for X field.
   * @param y Value for Y field.
   * @param z Value for Z field.
   * @param w Value for W field.
   */
  Vector4(double x, double y, double z, double w);
  ~Vector4();

    /**
   * @brief Getter for Vector4 x value.
   */
  double X() const;
  /**
   * @brief Getter for Vector4 y value.
   */
  double Y() const;
  /**
   * @brief Getter for Vector4 z value.
   */
  double Z() const;

    /**
   * @brief Getter for Vector4 z value.
   */
  double W() const;

  /**
   * @brief Setter for Vector4 x value.
   *
   * @param valX New value of vector's x.
   */
  void SetX(double valX);

  /**
   * @brief Setter for Vector4 y value.
   *
   * @param valY New value of vector's y.
   */
  void SetY(double valY);

  /**
   * @brief Setter for Vector4 z value.
   *
   * @param valZ New value of vector's z.
   */
  void SetZ(double valZ);

  /**
   * @brief Setter for Vector4 w value.
   *
   * @param valW New value of vector's w.
   */
  void SetW(double valW);

private:
  static inline constexpr uint8_t VECTOR4_WIDTH{4};
  static inline constexpr uint8_t VECTOR4_HEIGHT{1};
};

inline Vector4::Vector4() : Vector4(0, 0, 0, 0) {}

inline Vector4::Vector4(double valXYZW) : Vector4(valXYZW, valXYZW, valXYZW, valXYZW) {}

inline Vector4::Vector4(double x, double y, double z, double w) : Matrix<double>(VECTOR4_HEIGHT, VECTOR4_WIDTH)
{
  SetX(x);
  SetY(y);
  SetZ(z);
  SetW(w);
}

inline Vector4::~Vector4() {}

inline double Vector4::X() const { return (*this)[0][0]; }

inline double Vector4::Y() const { return (*this)[1][0]; }

inline double Vector4::Z() const { return (*this)[2][0]; }

inline double Vector4::W() const { return (*this)[3][0]; }

inline void Vector4::SetX(double valX) { (*this)[0][0] = valX; }

inline void Vector4::SetY(double valY) { (*this)[1][0] = valY; }

inline void Vector4::SetZ(double valZ) { (*this)[2][0] = valZ; }

inline void Vector4::SetW(double valW) { (*this)[3][0] = valW; }

#endif /* _Vector4_HPP_ */
