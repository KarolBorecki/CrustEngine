#include "objects/RenderObject.h"

namespace Crust {
    RenderObject::RenderObject(const char *p_mesh_path) : Object() {
        MeshLoader::loadMesh(p_mesh_path, &m_mesh);
        m_material.setDiffuse({255, 255, 255, 255});
    };

    Mesh &RenderObject::getMesh() {
        return m_mesh;
    }

    Material &RenderObject::getMaterial() {
        return m_material;
    }
}