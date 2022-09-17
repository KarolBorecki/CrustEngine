#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <math.h>

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)


/**
* @brief Class representing the camera on a scene from which's perespective the renderer can render Mesh.
*/
class Camera {
public:
  /**
  * @details Also calculates the fFovRad for given input.
  *
  * @param _fieldOfView Field of view in degress.
  * @param _fNear fNear.
  * @param _fFar fFar.
  */
  Camera(int _fieldOfView, double _fNear, double _fFar);
  virtual ~Camera() = default;

  /**
  * @brief Getter for #fieldOfViewDeg field.
  *
  * @return Value of #fieldOfViewDeg.
  */
  int GetFieldOfViewDeg();
  /**
  * @brief Getter for #fNear field.
  *
  * @return Value of #fNear.
  */
  double GetFNear();
  /**
  * @brief Getter for #fFar field.
  *
  * @return Value of #fFar.
  */
  double GetFFar();
  /**
  * @brief Getter for #fFovRad field.
  *
  * @return Value of #fFovRad.
  */
  double GetFFovRad();

private:
  int fieldOfViewDeg { 0 }; //!< Represents the field of view of the camera as the angle value in degrees.
  double fNear { 0.0 }; //!< Represents the distance between the virtual eye and the rendered plane.
  double fFar { 0.0 }; //!< Represents the maximum depth of the viewed image.
  double fFovRad { 0.0 }; //!< Represents the field of view in radians.
};

inline Camera::Camera(int _fieldOfViewDeg, double _fNear, double _fFar) : fieldOfViewDeg(_fieldOfViewDeg), fNear(_fNear), fFar(_fFar) {
  fFovRad = 1.0 / tan(degToRad(_fieldOfViewDeg * 0.5));
}

inline int Camera::GetFieldOfViewDeg() { return fieldOfViewDeg; }

inline double Camera::GetFNear() { return fNear; }

inline double Camera::GetFFar() { return fFar; }

inline double Camera::GetFFovRad() { return fFovRad; }

#endif /* _CAMERA_HPP_ */
