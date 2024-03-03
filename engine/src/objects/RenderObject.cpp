#include "objects/RenderObject.h"

namespace Crust {
    RenderObject::RenderObject(const char* p_mesh_path) : Object() {
        MeshLoader::loadMesh(p_mesh_path, &m_mesh);
    };

    Mesh& RenderObject::getMesh() {
        return m_mesh;
    }
}