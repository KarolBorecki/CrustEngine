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
  Mesh &r_mesh; //!< Mesh that is rendered in this object position.
};

inline RenderObject::RenderObject(Mesh &_mesh) : r_mesh(_mesh), Object() {}

inline Mesh &RenderObject::GetMesh() { return r_mesh; }

#endif /* _RENDEROBJECT_HPP_ */
