#include "objects/RenderObject.h"

namespace Crust {
    RenderObject::RenderObject(const char* p_mesh_path) : Object() {
        Logger::info("Created new render object with mesh: %s", p_mesh_path);
        MeshLoader::loadMesh(p_mesh_path, &m_mesh);
    };

    Mesh& RenderObject::getMesh() {
        return m_mesh;
    }
}