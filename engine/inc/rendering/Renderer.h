#ifndef CRUSTENGINE_RENDERER_H
#define CRUSTENGINE_RENDERER_H

#include <cstdint>

#include "static/Definitions.h"
#include "core/Scene.h"
#include "Library2DWrapper.h"
#include "rendering/projection/AbstractProjector.h"
#include "rendering/projection/PerspectiveProjector.h"

namespace Crust {
    /**
     * @brief The renderer class. It is responsible for rendering the scene and managing the objects on the scene.
     */
    class Renderer {
    public:
        /**
         * @brief Construct a new Renderer object with not specified width and height.
         */
        Renderer();

        /**
         * @brief Construct a new Renderer object with the specified width and height.
         *
         * @param p_width The width of the renderer.
         * @param p_height The height of the renderer.
         */
        Renderer(uint16_t p_width, uint16_t p_height);

        /**
         * @brief Destroy the Renderer object with it's lib 2D wrapper and projector.
         */
        virtual ~Renderer() = default;

        /**
         * @brief Render the scene.
         *
         * @param scene The scene to render.
         */
        void renderScene(Scene& p_scene);

        /**
         * @brief Resize the renderer.
         *
         * @details Resizes the window to the specified width and height. Also performs the resizing of the projector and 2D lib.
         *
         * @param p_width The width of the window.
         * @param p_height The height of the window.
         */
        void resize(uint16_t p_width, uint16_t p_height);

        /**
         * @brief Set the projector mathematical model.
         *
         * @param p_projection_model The projection model to set.
         * @return Status::OK if the projector was set successfully, Status::ERROR otherwise.
         */
        Status setProjector(Projection p_projection_model);

    private:
        uint16_t m_width { 0 }; /** !< The width of the projector. */
        uint16_t m_height { 0 }; /** !< The height of the projector. */

        Library2DWrapper m_lib_2d; /** !< The 2D library wrapper. */
        AbstractProjector m_projector; /** !< The projector. */
    };
}


#endif /* CRUSTENGINE_RENDERER_H */
