#ifndef CRUSTENGINE_RENDEROBJECT_H
#define CRUSTENGINE_RENDEROBJECT_H

#include "logging/Logger.h"
#include "Object.h"
#include "Mesh.h"
#include "files/MeshLoader.h"

namespace Crust {
    /**
     * @brief A renderable object.
     */
    class RenderObject : public Object {
    public:
        /**
         * @brief Construct a new RenderObject object with the specified mesh. Loads the mesh from the file.
         *
         * @param p_mesh_path The path to the mesh file.
         */
        explicit RenderObject(const char* p_mesh_path);

        /**
         * @brief Destroy the RenderObject object with it's mesh.
         */
        ~RenderObject() override = default;

        /**
         * @brief Get the mesh to render.
         *
         * @return The mesh to render.
         */
        Mesh& getMesh();

        private:
            Mesh m_mesh; /** !< The mesh to render. */
    };
}

#endif /* CRUSTENGINE_RENDEROBJECT_H */
