#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include <Physics/Vector3.hpp>

/**
* @brief Represents flat triangled plane in 3D space as 3 points.
*/
class Triangle {
public:
  /**
  * @param point1 First point of triangle.
  * @param point2 Second point of triangle. In projection next from #point1 in clockwise direction.
  * @param point3 Third point of triangle. In projection next from #point1 in clockwise direction.
  */
  Triangle(Vector3* point1, Vector3* point2, Vector3* point3);
  ~Triangle();

  /**
  * @brief Getter for triangle Vector3 point.
  *
  * @param index Index of the point. 0 represents first point, 1 second and 2 thrid point.
  */
  Vector3* GetPoint(uint8_t index);

private:
  Vector3* point[3]; //!< Three points representing the triangle in 3D space.
};

Triangle::Triangle(Vector3* point1, Vector3* point2, Vector3* point3) {
  point[0] = point1;
  point[1] = point2;
  point[2] = point3;
}

Triangle::~Triangle() {
  for(int i = 0; i < 3; i++)
    delete point[i];
}

inline Vector3* Triangle::GetPoint(uint8_t index) { return point[index]; }

#endif /* _TRIANGLE_HPP_ */
