#include "objects/RenderObject.h"

namespace Crust {
    RenderObject::RenderObject(const char* p_mesh_path) : m_mesh(*MeshLoader::loadMesh(p_mesh_path)), Object() {
        Logger::info("Created new render object with mesh: %s", p_mesh_path);
    };

    RenderObject::~RenderObject() {
        delete &m_mesh;
    }

    Mesh& RenderObject::getMesh() const {
        return m_mesh;
    }
}