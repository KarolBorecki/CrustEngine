#ifndef _RENDEROBJECT_HPP_
#define _RENDEROBJECT_HPP_

#include <vector>

#include <Rendering/Objects/Object.hpp>
#include <Physics/Vector3.hpp>

/**
* @brief Represents flat triangled plane in 3D space as 3 points.
*/
typedef struct Triangle {
  Vector3 point[3];
} Triangle;

/**
* @brief Represents 3D model as mesh consisted of 3D triagnles.
*/
typedef struct Mesh {
  std::vector<Triangle> triangles;
} Mesh;


/**
* @brief Represents object present on the scene.
*/
class RenderObject : public Object {
public:
  /**
  * @param _mesh Mesh that will be rendered for this object on the scene that contains this object.
  */
  RenderObject(Mesh* _mesh);
  virtual ~RenderObject() = default;

  /**
  * @brief Getter for #mesh field.
  *
  * @return Handler to #mesh field.
  */
  Mesh* GetMesh();

private:
  Mesh* mesh; //!< Mesh that is rendered in this object position.
};

inline RenderObject::RenderObject(Mesh* _mesh) : mesh(_mesh) {
  Logger::Log("Trying write mesh");
  Logger::Log(_mesh->triangles.begin()->point[1].ToString().c_str());
}

inline Mesh* RenderObject::GetMesh() { return mesh; }

#endif /* _RENDEROBJECT_HPP_ */
