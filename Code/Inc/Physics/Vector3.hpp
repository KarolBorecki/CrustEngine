#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

/**
* @brief Represents mathematical vector.
*/
class Vector3 {
public:
  Vector3(double _x, double _y, double _z);
  virtual ~Vector3() {};
  
  double x; //!< Vector's x value.
  double y; //!< Vector's y value.
  double z; //!< Vector's z value.
private:
};

inline Vector3::Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

#endif /* _VECTOR3_HPP_ */
