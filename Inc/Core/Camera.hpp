#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

class Camera {
public:
  Camera(double _fieldOfView);
  virtual ~Camera() = default;
private:
  double fieldOfView { 0 };
};

inline Camera::Camera(double _fieldOfView) : fieldOfView(_fieldOfView) {}

#endif /* _CAMERA_HPP_ */
