#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include <string.h>

#include <Math/Vector3.hpp>

/**
 * @brief Represents flat triangular plane in 3D space as 3 points.
 */
class Triangle
{
public:
  Triangle();
  /**
   * @param p1X Point 1 x coordinate value in 3D space.
   * @param p1Y Point 1 y coordinate value in 3D space.
   * @param p1Z Point 1 z coordinate value in 3D space.
   * @param p2X Point 2 x coordinate value in 3D space.
   * @param p2Y Point 2 y coordinate value in 3D space.
   * @param p2Z Point 2 z coordinate value in 3D space.
   * @param p3X Point 3 x coordinate value in 3D space.
   * @param p3Y Point 3 y coordinate value in 3D space.
   * @param p3Z Point 3 z coordinate value in 3D space.
   */
  Triangle(float p1X, float p1Y, float p1Z, float p2X, float p2Y, float p2Z, float p3X, float p3Y, float p3Z);

  /**
   * @brief Destroy created vectors representing triangle's points.
   */
  ~Triangle();

  /**
   * @brief Getter for triangle Vector3 point.
   *
   * @param index Index of the point. 0 represents first point, 1 second and 2 thrid point.
   */
  crust::Vector3<> &GetPoint(uint8_t index);

  /**
   * @brief Setter for all 3 points of triangle x, y and z values.
   */
  void SetPoints(float p1X, float p1Y, float p1Z, float p2X, float p2Y, float p2Z, float p3X, float p3Y, float p3Z);

private:
    crust::Vector3<> *_point[3]; //!< Three points representing the triangle in 3D space.
};

inline Triangle::Triangle() : Triangle(0, 0, 0, 0, 0, 0, 0, 0, 0) {}

inline Triangle::Triangle(float p1X, float p1Y, float p1Z, float p2X, float p2Y, float p2Z, float p3X, float p3Y, float p3Z)
{
  _point[0] = new crust::Vector3<>(p1X, p1Y, p1Z);
  _point[1] = new crust::Vector3<>(p2X, p2Y, p2Z);
  _point[2] = new crust::Vector3<>(p3X, p3Y, p3Z);
}

Triangle::~Triangle()
{
  delete _point[0];
  delete _point[1];
  delete _point[2];
}

inline crust::Vector3<> &Triangle::GetPoint(uint8_t index) { return *(_point[index]); }

void Triangle::SetPoints(float p1X, float p1Y, float p1Z, float p2X, float p2Y, float p2Z, float p3X, float p3Y, float p3Z)
{
  (*_point[0]) = {p1X, p1Y, p1Z};
  (*_point[1]) = {p2X, p2Y, p2Z};
  (*_point[2]) = {p3X, p3Y, p3Z};
}

#endif /* _TRIANGLE_HPP_ */
