#ifndef _RENDEROBJECT_HPP_
#define _RENDEROBJECT_HPP_

#include <vector>

#include <Rendering/Objects/Object.hpp>

#include <Physics/Vector3.hpp>

typedef struct Mesh {
  std::vector<Vector3> triangles;
} Mesh;

class RenderObject : public Object {
public:
  RenderObject(Mesh mesh);

private:
};

#endif /* _RENDEROBJECT_HPP_ */
