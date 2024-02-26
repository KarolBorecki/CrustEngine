#ifndef CRUSTENGINE_RENDEROBJECT_H
#define CRUSTENGINE_RENDEROBJECT_H

#include "Object.h"
#include "Mesh.h"

namespace Crust {
    /**
     * @brief A renderable object.
     */
    class RenderObject : public Object {
    public:
        /**
         * @brief Construct a new RenderObject object with the specified mesh.
         *
         * @param p_mesh The mesh to render.
         */
        RenderObject(Mesh& p_mesh);

        /**
         * @brief Destroy the RenderObject object with it's mesh.
         */
        ~RenderObject() = default;

        /**
         * @brief Get the mesh to render.
         *
         * @return The mesh to render.
         */
        Mesh& getMesh() const;

        private:
            Mesh& m_mesh; /** !< The mesh to render. */
    };
}

#endif /* CRUSTENGINE_RENDEROBJECT_H */
