#include "objects/RenderObject.h"

namespace Crust {
    RenderObject::RenderObject(const char *p_mesh_path) : Object() {
        MeshLoader::loadMesh(p_mesh_path, &m_mesh);
        m_material.setDiffuse({1.0f, 1.0f, 1.0f, 1.0f});
        m_material.setSpecular({0.5f, 0.5f, 0.5f, 1.0f});
        m_material.setShininess(32); // TODO move to defaults
    };

    Mesh &RenderObject::getMesh() {
        return m_mesh;
    }

    Material &RenderObject::getMaterial() {
        return m_material;
    }
}