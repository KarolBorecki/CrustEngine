#ifndef _MESH_HPP_
#define _MESH_HPP_

#include <vector>

#include <Physics/Triangle.hpp>

class Vector3;

/**
* @brief Represents 3D model as mesh consisted of 3D triangles.
*/
class Mesh {
public:
  Mesh();
  /**
  * @brief Deletes all of the triangles of this mesh
  */
  ~Mesh();

  /**
  * @brief Adds the triangle to mesh.
  *
  * @param tri Handler to added triangle.
  */
  void AddTriangle(Triangle* tri);

  /**
  * @brief Getter for triangle.
  *
  * @param index The index in #triangles for got triangle.
  */
  Triangle* GetTriangle(uint8_t index);
  /**
  * @brief Getter for point of triangle of specified index.
  *
  * @param triIndex Triangle index.
  * @param pointIndex Triangle's point index.
  */
  Vector3* GetPoint(uint8_t triIndex, uint8_t pointIndex);

  /**
  * @brief Getter for triangles count.
  *
  * @return Triangles count.
  */
  uint8_t GetTrianglesCount();

private:
  std::vector<Triangle*> triangles; //!< Triangles, from which the mesh consists.
};

Mesh::Mesh() {}

Mesh::~Mesh() {
  for(auto tri : triangles)
    delete tri;
}

inline void Mesh::AddTriangle(Triangle* tri) { triangles.push_back(tri); }

inline Triangle* Mesh::GetTriangle(uint8_t index) { return triangles[index]; }

inline Vector3* Mesh::GetPoint(uint8_t triIndex, uint8_t pointIndex) { return triangles[triIndex]->GetPoint(pointIndex); }

inline uint8_t Mesh::GetTrianglesCount() { return triangles.size(); }

#endif /* _MESH_HPP_ */
