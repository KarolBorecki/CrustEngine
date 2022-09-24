#ifndef _RENDEROBJECT_HPP_
#define _RENDEROBJECT_HPP_

#include <vector>

#include <Physics/Vector3.hpp>
#include <Rendering/Objects/Object.hpp>
#include <Rendering/Mesh.hpp>

/**
* @brief Represents object present on the scene.
*/
class RenderObject : public Object {
public:
  /**
  * @param pos Object's position.
  * @param _mesh Mesh that will be rendered for this object on the scene that contains this object.
  */
  RenderObject(Vector3* pos, Mesh* _mesh);
  /**
  * @param posX Object's x position.
  * @param posY Object's y position.
  * @param posZ Object's z position.
  * @param _mesh Mesh that will be rendered for this object on the scene that contains this object.
  */
  RenderObject(double posX, double posY, double posZ, Mesh* _mesh);
  /**
  * @param _mesh Mesh that will be rendered for this object on the scene that contains this object.
  */
  RenderObject(Mesh* _mesh);
  ~RenderObject();

  /**
  * @brief Getter for #mesh field.
  *
  * @return Handler to #mesh field.
  */
  Mesh* GetMesh();

  /**
  * @brief Converts RenderObject's mesh to std::string, so it can be written on any output.
  *
  * @return std::string containing the triangles that represents this RednerObject's mesh.
  */
  std::string ToString();

private:
  Mesh* mesh; //!< Mesh that is rendered in this object position.
};

inline RenderObject::RenderObject(Vector3* pos, Mesh* _mesh) : mesh(_mesh), Object(pos) {}

inline RenderObject::RenderObject(double posX, double posY, double posZ, Mesh* _mesh) : mesh(_mesh), Object(posX, posY, posZ) {}

inline RenderObject::RenderObject(Mesh* _mesh) : mesh(_mesh), Object() {}

inline RenderObject::~RenderObject() {}

inline Mesh* RenderObject::GetMesh() { return mesh; }

std::string RenderObject::ToString() {
  std::string result = "";
  result += "Mesh:\n";
  Mesh* mesh = GetMesh();
  for(int i = 0; i < mesh->GetTrianglesCount(); i++) {
    for(int j = 0; j < 3; j++) {
      result += "(" + std::to_string(mesh->GetPoint(i, j)->X()) + ", " + std::to_string(mesh->GetPoint(i, j)->Y()) + ", " + std::to_string(mesh->GetPoint(i, j)->Z()) + ") ";
    }
    result += "\n";
  }
  return result;
}

#endif /* _RENDEROBJECT_HPP_ */
