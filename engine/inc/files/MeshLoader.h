#ifndef CRUSTENGINE_MESHLOADER_H
#define CRUSTENGINE_MESHLOADER_H

#include "objects/Mesh.h"

namespace Crust {
    class MeshLoader {
    public:
        MeshLoader() = default;
        virtual ~MeshLoader() = default;

        /**
         * @brief Load a mesh from the specified file and if cannot do it returns nullptr.
         *
         * @param p_path The path to the mesh file.
         * @para p_out_mesh The mesh to load to.
         * @return The loaded mesh pointer. Remember to delete it after using.
         */
        static Status loadMesh(const char* p_path, Mesh* p_out_mesh);
    };
}

#endif /* CRUSTENGINE_MESHLOADER_H */
