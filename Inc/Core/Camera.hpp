#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <math.h>

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

class Camera {
public:
  Camera(int _fieldOfView, double _fNear, double _fFar);
  virtual ~Camera() = default;

  int GetFieldOfViewDeg();
  double GetFNear();
  double GetFFar();
  double GetFFovRad();

private:
  int fieldOfViewDeg { 0 };
  double fNear { 0.0 };
  double fFar { 0.0 };
  double fFovRad { 0.0 };
};

inline Camera::Camera(int _fieldOfViewDeg, double _fNear, double _fFar) : fieldOfViewDeg(_fieldOfViewDeg), fNear(_fNear), fFar(_fFar) {
  fFovRad = 1.0 / tan(degToRad(_fieldOfViewDeg * 0.5));
}

inline int Camera::GetFieldOfViewDeg() { return fieldOfViewDeg; }

inline double Camera::GetFNear() { return fNear; }

inline double Camera::GetFFar() { return fFar; }

inline double Camera::GetFFovRad() { return fFovRad; }

#endif /* _CAMERA_HPP_ */
