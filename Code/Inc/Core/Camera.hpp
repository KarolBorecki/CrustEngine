#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <math.h>

#include <Rendering/Objects/Object.hpp>

/**
* @brief Converts #angleInDegrees to radians.
*/
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
/**
* @brief Converts #angleInRadians to degrees.
*/
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

/**
* @brief Class representing the camera on a scene from which's perespective the renderer can render Mesh.
*/
class Camera : public Object {
public:
  /**
  * @details Also calculates the fFovRad for given input.
  *
  * @param _fFovDeg Field of view in degress.
  * @param _fNear fNear.
  * @param _fFar fFar.
  */
  Camera(int _fFovDeg, double _fNear, double _fFar);
  virtual ~Camera() = default;

  /**
  * @brief Getter for #fieldOfViewDeg field.
  *
  * @return Value of #fieldOfViewDeg.
  */
  int GetFFovDeg();
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
  int fFovDeg { 0 }; //!< Represents the field of view of the camera as the angle value in degrees.
  double fNear { 0.0 }; //!< Represents the distance between the virtual eye and the rendered plane.
  double fFar { 0.0 }; //!< Represents the maximum depth of the viewed image.
  double fFovRad { 0.0 }; //!< Represents the field of view in radians.
};

inline Camera::Camera(int _fFovDeg, double _fNear, double _fFar) : fFovDeg(_fFovDeg), fNear(_fNear), fFar(_fFar) {
  fFovRad = (1.0 / tan(degToRad(fFovDeg) * 0.5));
}

inline int Camera::GetFFovDeg() { return fFovDeg; }

inline double Camera::GetFNear() { return fNear; }

inline double Camera::GetFFar() { return fFar; }

inline double Camera::GetFFovRad() { return fFovRad; }

#endif /* _CAMERA_HPP_ */
