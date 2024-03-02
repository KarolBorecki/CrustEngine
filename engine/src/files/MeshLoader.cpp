#include "files/MeshLoader.h"

namespace Crust {
    Mesh& MeshLoader::loadMesh(const char* p_path) {
        return *new Mesh();
    }
}