#ifndef _MESH_HPP_
#define _MESH_HPP_

#include <vector>

#include <Math/Vector3.hpp>
#include <Rendering/Polygon.hpp>

#define DEFAULT_MESH_NAME "NO NAME"

class Vector3;

/**
 * @brief Represents 3D model as mesh consisted of 3D polygons.
 */
class Mesh
{
public:
  Mesh();
  Mesh(std::string name);
  /**
   * @brief Deletes all of the polygons of this mesh
   */
  ~Mesh();

  /**
   * @brief Adds the triangle to mesh.
   *
   * @param tri Handler to added triangle.
   */
  void AddPolygon(Polygon &tri);

  /**
   * @brief Getter for triangle.
   *
   * @param index The index in #polygons for got triangle.
   */
  Polygon &GetPolygon(const uint32_t index) const;
  /**
   * @brief Getter for point of triangle of specified index.
   *
   * @param triIndex Triangle index.
   * @param pointIndex Triangle's point index.
   */
  Vector3 &GetPoint(const uint32_t triIndex, const uint32_t pointIndex) const;

  /**
   * @brief Getter for polygons count.
   *
   * @return polygons count.
   */
  uint32_t GetPolygonsCount() const;

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
  std::string GetName() const;

private:
  std::string name; //!< Mesh name. For *.obj file it is 'o' value. For others file: mesh's file path.

  std::vector<Polygon*> polygons; //!< Polygons, of which the mesh consists.
};

inline Mesh::Mesh() : name(DEFAULT_MESH_NAME) {}

inline Mesh::Mesh(std::string meshName) : name(meshName) {}

Mesh::~Mesh()
{
  // TODO not created? Then dont delete!
  for (auto tri : polygons)
    delete tri;
}

inline void Mesh::AddPolygon(Polygon &tri) { polygons.push_back(&tri); } // TODO hold copies

inline Polygon &Mesh::GetPolygon(const uint32_t index) const { return *(polygons[index]); }

inline Vector3 &Mesh::GetPoint(const uint32_t triIndex, const uint32_t pointIndex) const { return *(polygons[triIndex]->GetPoint(pointIndex)); }

inline uint32_t Mesh::GetPolygonsCount() const { return polygons.size(); }

inline void Mesh::SetName(std::string newName) { name = newName; }

inline std::string Mesh::GetName() const { return name; }

#endif /* _MESH_HPP_ */
