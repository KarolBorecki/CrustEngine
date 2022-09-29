#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

#include <Physics/Matrix.hpp>

/**
* @brief Represents mathematical vector3.
*/
class Vector3 : public Matrix {
public:
  /**
  * @brief Creates blank vector that consists of values zero.
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
  double X();
  /**
  * @brief Getter for Vector3 y value.
  */
  double Y();
  /**
  * @brief Getter for Vector3 z value.
  */
  double Z();

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

  /**
  * @brief Setter for Vector3 values.
  *
  * @param x New value of vector's x.
  * @param y New value of vector's y.
  * @param z New value of vector's z.
  */
  void SetXYZ(double x, double y, double z);

  /**
  * @brief Setter for Vector3 values from another Vector3.
  *
  * @param vec Another vector from which the values will be taken.
  */
  void SetXYZ(Vector3* vecXYZ);

  /*
  * @brief Adds given x, y, z values to given vector.
  *
  * @param vec Modified vector to which values will be added.
  * @param x Value added to #vec x field.
  * @param y Value added to #vec y field.
  * @param z Value added to #vec z field.
  */
  static void Add(Vector3* vec, double x, double y, double z);

  /**
  * @brief Adds given value to given vector.
  *
  * @param vec Modified vector to which values will be added.
  * @param scalar The value added to vector.
  */
  static void Add(Vector3* vec, double scalar);

  /**
  * @brief Adds given x, y, z values to given vector from another vector.
  *
  * @param vec1 Modified vector to which values will be added.
  * @param vec2 Origin of values that will be added to #vec1.
  */
  static void Add(Vector3* vec1, Vector3* vec2);

private:
  void Init(double x, double y, double z);
};

inline Vector3::Vector3() : Matrix(1, 3) { Init(0.0, 0.0, 0.0); }

inline Vector3::Vector3(double valXYZ) : Matrix(1, 3) { Init(valXYZ, valXYZ, valXYZ); }

inline Vector3::Vector3(double x, double y, double z) : Matrix(1, 3) { Init(x, y, z); }

inline Vector3::~Vector3() { Logger::Log(Logger::FontColor::PINK, "   [X] Deleting Vec3D<%d>", GetID()); }

inline double Vector3::X() { return GetValue(0, 0); }

inline double Vector3::Y() { return GetValue(0, 1); }

inline double Vector3::Z() { return GetValue(0, 2); }

inline void Vector3::SetX(double valX) { PutValue(0, 0, valX); }

inline void Vector3::SetY(double valY) { PutValue(0, 1, valY); }

inline void Vector3::SetZ(double valZ) { PutValue(0, 2, valZ); }

void Vector3::SetXYZ(double x, double y, double z) {
  SetX(x);
  SetY(y);
  SetZ(z);
}

void Vector3::SetXYZ(Vector3* vecXYZ) {
  SetX(vecXYZ->X());
  SetY(vecXYZ->Y());
  SetZ(vecXYZ->Z());
}

void Vector3::Add(Vector3* vec, double x, double y, double z) {
  vec->SetX(vec->X() + x);
  vec->SetY(vec->Y() + y);
  vec->SetZ(vec->Z() + z);
}

inline void Vector3::Add(Vector3* vec, double scalar) { Matrix::Add(vec, scalar); }

inline void Vector3::Add(Vector3* vec1, Vector3* vec2) { Vector3::Add(vec1, vec2->X(), vec2->Y(), vec2->Z()); }

inline void Vector3::Init(double x, double y, double z) {
  SetXYZ(x, y, z);
  Logger::Log(Logger::FontColor::GREEN, "   [+] Vector3 of id: %d initzialized", GetID());
}

#endif /* _VECTOR3_HPP_ */
