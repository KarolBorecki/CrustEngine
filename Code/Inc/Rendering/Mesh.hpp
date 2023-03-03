#ifndef _MESH_HPP_
#define _MESH_HPP_

#include <vector>

#include <Physics/Triangle.hpp>

#define DEFAULT_MESH_NAME "NO NAME"

class Vector3;

/**
* @brief Represents 3D model as mesh consisted of 3D triangles.
*/
class Mesh {
public:
  Mesh();
  Mesh(std::string name);
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

  /**
  * @brief Setter for #name field.
  *
  * @param newName new mesh's name.
  */
  void SetName(std::string newName);

  /**
  * @brief Getter fir #name field.
  *
  * @return The mesh's file name.
  */
  std::string GetName();

private:
  std::string name; //!< Mesh name. For *.obj file it is 'o' value. For others file: mesh's file path.

  std::vector<Triangle*> triangles; //!< Triangles, from which the mesh consists.
};

inline Mesh::Mesh() : name(DEFAULT_MESH_NAME) { }

inline Mesh::Mesh(std::string meshName) : name(meshName) { }

Mesh::~Mesh() {
  // TODO not created? Then dont delete!
  for(auto tri : triangles)
    delete tri;
}

inline void Mesh::AddTriangle(Triangle* tri) { triangles.push_back(tri); } // TODO hold copies

inline Triangle* Mesh::GetTriangle(uint8_t index) { return triangles[index]; }

inline Vector3* Mesh::GetPoint(uint8_t triIndex, uint8_t pointIndex) { return triangles[triIndex]->GetPoint(pointIndex); }

inline uint8_t Mesh::GetTrianglesCount() { return triangles.size(); }

inline void Mesh::SetName(std::string newName) { name = newName; }

inline std::string Mesh::GetName() { return name; }

#endif /* _MESH_HPP_ */
