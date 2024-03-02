#ifndef CRUSTENGINE_RENDERER_H
#define CRUSTENGINE_RENDERER_H

#include <cstdint>

#include "core/Scene.h"
#include "Library2DWrapper.h"
#include "rendering/projection/AbstractProjector.h"

namespace Crust {
    /**
     * @brief The renderer class. It is responsible for rendering the scene and managing the objects on the scene.
     */
    class Renderer {
    public:
        /**
         * @brief Construct a new Renderer object with the specified width and height.
         *
         * @param p_width The width of the renderer.
         * @param p_height The height of the renderer.
         */
        Renderer(uint16_t p_width, uint16_t p_height);

        /**
         * @brief Destroy the Renderer object.
         */
        virtual ~Renderer() = default;

        /**
         * @brief Render the scene.
         *
         * @param scene The scene to render.
         */
        void renderScene(Scene& scene);

    private:
        Projection m_projection_model { Projection::PERSPECTIVE }; /** !< The projection model. */

        Library2DWrapper& m_lib_2d; /** !< The 2D library wrapper. */
        AbstractProjector& m_projector; /** !< The projector. */
    };
}


#endif /* CRUSTENGINE_RENDERER_H */
