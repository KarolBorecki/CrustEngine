#ifndef _Vector4_HPP_
#define _Vector4_HPP_

#include <Physics/Matrix.hpp>

/**
* @brief Represents mathematical vector4.
*/
class Vector4 : public Matrix {
public:
  /**
  * @brief Creates blank vector4 that consists of values zero.
  */
  Vector4();

  /**
  * @param valXYZ Value for each X, Y, Z and W fields.
  */
  Vector4(double valXYZW);

  /**
  * @param vecXYZ Vector with values for each X, Y and Z.
  * @param w Value for W field.
  */
  Vector4(Vector3* vecXYZ, double w);

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
  double X();

  /**
  * @brief Getter for Vector4 y value.
  */
  double Y();

  /**
  * @brief Getter for Vector4 z value.
  */
  double Z();

  /**
  * @brief Getter for Vector4 z value.
  */
  double W();

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

  /**
  * @brief Setter for Vector4's values.
  *
  * @param x New value of vector's x.
  * @param y New value of vector's y.
  * @param z New value of vector's z.
  * @param w New value of vector's w.
  */
  void SetXYZW(double x, double y, double z, double w);

  /**
  * @brief Setter for Vector4's values.
  *
  * @param vecXYZ Vector handling xyz values.
  * @param w New value of vector's w.
  */
  void SetXYZW(Vector3* vecXYZ, double w);

  /**
  * @brief Setter for Vector4's values.
  *
  * @param vecXYZW Vector handling x, y, z, w values.
  */
  void SetXYZW(Vector4* vecXYZW);

  /*
  * @brief Adds given x, y, z, w values to given vector.
  *
  * @param vec Modified vector to which values will be added.
  * @param x Value added to #vec x field.
  * @param y Value added to #vec y field.
  * @param z Value added to #vec z field.
  * @param w Value added to #vec w field.
  */
  static void Add(Vector4* vec, double x, double y, double z, double w);

private:
  void Init(double x, double y, double z, double w);
};

inline Vector4::Vector4() : Matrix(1, 4) { Init(0.0, 0.0, 0.0, 0.0); }

inline Vector4::Vector4(double valXYZW) : Matrix(1, 4) { Init(valXYZW, valXYZW, valXYZW, valXYZW); }

inline Vector4::Vector4(Vector3* vecXYZ, double w) : Matrix(1, 4) { Init(vecXYZ->X(), vecXYZ->Y(), vecXYZ->Z(), w); }

inline Vector4::Vector4(double x, double y, double z, double w) : Matrix(1, 4) { Init(x, y, z, w); }

inline Vector4::~Vector4() { }

inline double Vector4::X() { return GetValue(0, 0); }

inline double Vector4::Y() { return GetValue(0, 1); }

inline double Vector4::Z() { return GetValue(0, 2); }

inline double Vector4::W() { return GetValue(0, 3); }

inline void Vector4::SetX(double valX) { PutValue(0, 0, valX); }

inline void Vector4::SetY(double valY) { PutValue(0, 1, valY); }

inline void Vector4::SetZ(double valZ) { PutValue(0, 2, valZ); }

inline void Vector4::SetW(double valW) { PutValue(0, 3, valW); }

void Vector4::SetXYZW(double x, double y, double z, double w) {
  SetX(x);
  SetY(y);
  SetZ(z);
  SetW(w);
}

void Vector4::SetXYZW(Vector3* vecXYZ, double w) {
  SetX(vecXYZ->X());
  SetY(vecXYZ->Y());
  SetZ(vecXYZ->Z());
  SetW(w);
}

void Vector4::SetXYZW(Vector4* vecXYZW) {
  SetX(vecXYZW->X());
  SetY(vecXYZW->Y());
  SetZ(vecXYZW->Z());
  SetW(vecXYZW->W());
}

void Vector4::Add(Vector4* vec, double x, double y, double z, double w) {
  vec->SetX(vec->X() + x);
  vec->SetY(vec->Y() + y);
  vec->SetZ(vec->Z() + z);
  vec->SetW(vec->W() + w);
}

inline void Vector4::Init(double x, double y, double z, double w) {
  SetXYZW(x, y, z, w);
}

#endif /* _Vector4_HPP_ */
