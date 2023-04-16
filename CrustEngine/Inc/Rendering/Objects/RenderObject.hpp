#ifndef _RENDEROBJECT_HPP_
#define _RENDEROBJECT_HPP_

#include <vector>

#include <Rendering/Objects/Object.hpp>
#include <Rendering/Mesh.hpp>

/**
 * @brief Represents renderable object present on the scene.
 */
class RenderObject : public Object
{
public:
  /**
   * @param _mesh Mesh that will be rendered for this object on the scene that contains this object.
   */
  RenderObject(Mesh &_mesh);

  /**
   * @brief Getter for #mesh field.
   *
   * @return Handler to #mesh field.
   */
  Mesh &GetMesh();

private:
  Mesh &mesh; //!< Mesh that is rendered in this object position.
};

inline RenderObject::RenderObject(Mesh &_mesh) : mesh(_mesh), Object() {}

inline Mesh &RenderObject::GetMesh() { return mesh; }

#endif /* _RENDEROBJECT_HPP_ */
