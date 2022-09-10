#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

class Vector3 {
public:
  Vector3(double _x, double _y, double _z);
  virtual ~Vector3() = default;

  double x;
  double y;
  double z;
private:
};

inline Vector3::Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z){}

#endif /* _VECTOR3_HPP_ */
