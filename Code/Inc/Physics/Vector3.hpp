#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

#include <Physics/Matrix.hpp>

/**
* @brief Represents mathematical vector.
*/
class Vector3 : public Matrix{
public:
  Vector3(double _x, double _y, double _z);
  ~Vector3();

  /**
  * @brief Getter for Vector3 x value.
  */
  double X();
  /**
  * @brief Getter for Vector3 y value.
  */
  double Y();
  /**
  * @brief Getter for Vector3 z value.
  */
  double Z();
private:
};

inline Vector3::Vector3(double _x, double _y, double _z) : Matrix(1, 3) {
  PutValue(0, 0, _x);
  PutValue(0, 1, _y);
  PutValue(0, 2, _z);
  Logger::Info("Vector of id: %d created", GetID());
}

inline Vector3::~Vector3() {
  Logger::Info("[X] Deleting Vec3D<%d>", GetID());
}

inline double Vector3::X() { return GetValue(0, 0); }

inline double Vector3::Y() { return GetValue(0, 1); }

inline double Vector3::Z() { return GetValue(0, 2); }

#endif /* _VECTOR3_HPP_ */
