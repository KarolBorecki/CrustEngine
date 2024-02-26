#include "objects/RenderObject.h"

namespace Crust {
    RenderObject::RenderObject(Mesh& p_mesh) : m_mesh(p_mesh), Object() {};

    Mesh& RenderObject::getMesh() const {
        return m_mesh;
    }
}