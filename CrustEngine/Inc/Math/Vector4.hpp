#ifndef _Vector4_HPP_
#define _Vector4_HPP_

#include <Math/Vector3.hpp>

/**
 * @brief Represents mathematical vector4.
 */
class Vector4 : public Vector3
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
   * @brief Getter for Vector4 z value.
   */
  double W() const;

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

inline Vector4::Vector4(double x, double y, double z, double w)
{
  width = VECTOR4_WIDTH;
  height = VECTOR4_HEIGHT;
  totalSize = VECTOR4_WIDTH;
  mat = new double[VECTOR4_WIDTH];

  SetX(x);
  SetY(y);
  SetZ(z);
  SetW(w);
}

inline Vector4::~Vector4() {}

inline double Vector4::W() const { return (*this)[3][0]; }

inline void Vector4::SetW(double valW) { (*this)[3][0] = valW; }

#endif /* _Vector4_HPP_ */
