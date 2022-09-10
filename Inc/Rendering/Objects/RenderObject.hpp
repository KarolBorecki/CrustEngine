#ifndef _RENDEROBJECT_HPP_
#define _RENDEROBJECT_HPP_

#include <vector>

#include <Rendering/Objects/Object.hpp>
#include <Physics/Vector3.hpp>

typedef struct Triangle {
  Vector3 point[3];
} Triangle;

typedef struct Mesh {
  std::vector<Triangle> triangles;
} Mesh;

class RenderObject : public Object {
public:
  RenderObject(Mesh& _mesh);
  virtual ~RenderObject() = default;

  Mesh* GetMesh();

private:
  Mesh mesh;
};

inline RenderObject::RenderObject(Mesh& _mesh) : mesh(_mesh) {}

inline Mesh* RenderObject::GetMesh() { return &mesh; }

#endif /* _RENDEROBJECT_HPP_ */
