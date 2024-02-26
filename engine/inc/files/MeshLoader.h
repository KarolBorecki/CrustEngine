#ifndef CRUSTENGINE_MESHLOADER_H
#define CRUSTENGINE_MESHLOADER_H

#include "objects/Mesh.h"

namespace Crust {
    class MeshLoader {
    public:
        MeshLoader() = default;
        virtual ~MeshLoader() = default;

        /**
         * @brief Load a mesh from a file.
         *
         * @param p_path The path to the file.
         * @param p_out_mesh The mesh to load the data into.
         */
        static void loadMesh(const char* p_path, Mesh* p_out_mesh);
    };
}

#endif /* CRUSTENGINE_MESHLOADER_H */
