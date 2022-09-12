#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

#include <Physics/Matrix.hpp>

class Vector3 : public Matrix {
public:
  Vector3(double _x, double _y, double _z);
  virtual ~Vector3() {};

  double X();
  double Y();
  double Z();

private:
};

inline Vector3::Vector3(double _x, double _y, double _z) : Matrix(1, 3) {
  PutValue(0, 0, _x);
  PutValue(0, 1, _y);
  PutValue(0, 2, _z);
}

inline double Vector3::X() { return GetValue(0, 0); }
inline double Vector3::Y() { return GetValue(0, 1); }
inline double Vector3::Z() { return GetValue(0, 2); }

#endif /* _VECTOR3_HPP_ */
