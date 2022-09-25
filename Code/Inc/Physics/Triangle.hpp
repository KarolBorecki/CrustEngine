#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include <string.h>

#include <Physics/Vector3.hpp>

/**
* @brief Represents flat triangled plane in 3D space as 3 points.
*/
class Triangle {
public:
  Triangle();

  Triangle(double p1X, double p1Y, double p1Z, double p2X, double p2Y, double p2Z, double p3X, double p3Y, double p3Z);
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

  void SetPoints(double p1X, double p1Y, double p1Z, double p2X, double p2Y, double p2Z, double p3X, double p3Y, double p3Z);

  /**
  * @brief
  */
  std::string ToString();


private:
  Vector3* point[3]; //!< Three points representing the triangle in 3D space.
};

Triangle::Triangle() {
  point[0] = new Vector3();
  point[1] = new Vector3();
  point[2] = new Vector3();
  Logger::Log(Logger::FontColor::GREEN, "[+] Creating Triangle");
}

Triangle::Triangle(double p1X, double p1Y, double p1Z, double p2X, double p2Y, double p2Z, double p3X, double p3Y, double p3Z) {
  point[0] = new Vector3(p1X, p1Y, p1Z);
  point[1] = new Vector3(p2X, p2Y, p2Z);
  point[2] = new Vector3(p3X, p3Y, p3Z);
  Logger::Log(Logger::FontColor::GREEN, "[+] Creating Triangle");
}

Triangle::Triangle(Vector3* point1, Vector3* point2, Vector3* point3) {
  point[0] = new Vector3(point1->X(), point1->Y(), point1->Z());
  point[1] = new Vector3(point2->X(), point2->Y(), point2->Z());
  point[2] = new Vector3(point3->X(), point3->Y(), point3->Z());
  Logger::Log(Logger::FontColor::GREEN, "[+] Creating Triangle");
}

Triangle::~Triangle() {
  delete point[0];
  delete point[1];
  delete point[2];
}

inline Vector3* Triangle::GetPoint(uint8_t index) { return point[index]; }

void Triangle::SetPoints(double p1X, double p1Y, double p1Z, double p2X, double p2Y, double p2Z, double p3X, double p3Y, double p3Z) {
  point[0]->SetXYZ(p1X, p1Y, p1Z);
  point[1]->SetXYZ(p2X, p2Y, p2Z);
  point[2]->SetXYZ(p3X, p3Y, p3Z);
}

std::string Triangle::ToString() {
  std::string result = "";
  result += "Triangle:\n";
  result += GetPoint(0)->ToString();
  result += GetPoint(1)->ToString();
  result += GetPoint(2)->ToString();
  result += "\n";
  return result;
}

#endif /* _TRIANGLE_HPP_ */
