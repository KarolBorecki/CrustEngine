#ifndef CRUSTENGINE_MESHLOADER_H
#define CRUSTENGINE_MESHLOADER_H

#include <string>
#include <cstdint>
#include <vector>
#include <fstream>

#include "math/Vector3.h"
#include "math/geometry/Polygon.h"
#include "math/geometry/Triangle.h"
#include "objects/Mesh.h"
#include "logging/ExceptionsHandler.h"

namespace Crust {
    /**
     * @brief The MeshLoader class is a utility class to load meshes from files.
     */
    class MeshLoader {
    public:
        /**
         * @brief Load a mesh from the specified file and if cannot do it returns nullptr.
         *
         * @param p_path The path to the mesh file.
         * @para p_out_mesh The mesh to load to.
         * @return The loaded mesh pointer. Remember to delete it after using.
         */
        static Status loadMesh(const char* p_path, Mesh* p_out_mesh);
    private:
        /**
         * @brief Load a mesh from the specified .obj file.
         *
         * @param p_path The path to the .obj file.
         * @param p_out_mesh The mesh to load to.
         * @return The status of the operation.
         */
        static Status loadObj(const char* p_path, Mesh* p_out_mesh);
    };
}

#endif /* CRUSTENGINE_MESHLOADER_H */
