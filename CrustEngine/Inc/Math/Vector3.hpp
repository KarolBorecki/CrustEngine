#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

#include <Math/Matrix.hpp>

//TODO add optional template for this class so wwe are able to use float instead of double 
/**
 * @brief Represents mathematical vector3.
 */
class Vector3 : public Matrix<double>
{
public:
  /**
   * @brief Creates blank vector that consists of zeros.
   */
  Vector3();
  /**
   * @param valXYZ Value for each X, Y and Z fields.
   */
  Vector3(double valXYZ);
  /**
   * @param x Value for X field.
   * @param y Value for Y field.
   * @param z Value for Z field.
   */
  Vector3(double x, double y, double z);
  ~Vector3();

  /**
   * @brief Getter for Vector3 x value.
   */
  double X() const;
  /**
   * @brief Getter for Vector3 y value.
   */
  double Y() const;
  /**
   * @brief Getter for Vector3 z value.
   */
  double Z() const;

  /**
   * @brief Setter for Vector3 x value.
   *
   * @param valX New value of vector's x.
   */
  void SetX(double valX);

  /**
   * @brief Setter for Vector3 y value.
   *
   * @param valY New value of vector's y.
   */
  void SetY(double valY);

  /**
   * @brief Setter for Vector3 z value.
   *
   * @param valZ New value of vector's z.
   */
  void SetZ(double valZ);

private:
  static inline constexpr uint8_t VECTOR3_WIDTH{3};
  static inline constexpr uint8_t VECTOR3_HEIGHT{1};
};

inline Vector3::Vector3() : Vector3(0, 0, 0) {}

inline Vector3::Vector3(double valXYZ) : Vector3(valXYZ, valXYZ, valXYZ) {}

inline Vector3::Vector3(double x, double y, double z) : Matrix<double>(VECTOR3_HEIGHT, VECTOR3_WIDTH)
{
  SetX(x);
  SetY(y);
  SetZ(z);
}

inline Vector3::~Vector3() {}

inline double Vector3::X() const { return (*this)[0][0]; }

inline double Vector3::Y() const { return (*this)[1][0]; }

inline double Vector3::Z() const { return (*this)[2][0]; }

inline void Vector3::SetX(double valX) { (*this)[0][0] = valX; }

inline void Vector3::SetY(double valY) { (*this)[1][0] = valY; }

inline void Vector3::SetZ(double valZ) { (*this)[2][0] = valZ; }

#endif /* _VECTOR3_HPP_ */
