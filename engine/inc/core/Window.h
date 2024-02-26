#ifndef CRUSTENGINE_WINDOW_H
#define CRUSTENGINE_WINDOW_H

#include <cstdint>

#include "Scene.h"
#include "static/Definitions.h"
#include "rendering/Renderer.h"
#include "utils/TimeProvider.h"

namespace Crust {
    /**
     * @brief Window class is responsible for creating and managing the engine's window.
     *
     * @details It also manages the scene that is being rendered on the window.
     */
    class Window {
    public:
        /**
         * @brief Construct a new Window object with specified width and height.
         *
         * @param p_width The width of the window.
         * @param p_height The height of the window.
         */
        Window(uint16_t p_width, uint16_t p_height);

        /**
         * @brief Destroy the Window object. It also unloads the scene from the window. It will not delete the scene.
         */
        ~Window();

        /**
         * @brief Loads the scene into the window. This scene will be rendered on the window.
         *
         * @param p_scene Scene to be loaded.
         * @return Status::OK if scene was loaded successfully, Status::ERROR otherwise.
         */
        Status loadScene(Scene& p_scene);

        /**
         * @brief Unloads the scene from the window. Remember that this method doesn't delete the scene and scene's start method will not be called ever again.
         *
         * @return Status::OK if scene was unloaded successfully, Status::ERROR otherwise.
         */
        Status unLoadScene();

        /**
         * @brief Opens the window. It also starts the rendering loop.
         */
        void open();

        /**
         * @brief Closes the window. It also stops the rendering loop.
         */
        void close();

    private:
        Renderer& m_renderer; /**< Renderer used to render the scene. */
        Scene& m_scene; /**< Scene that is being rendered on the window. */

        TimeProvider& m_time_provider; /**< Time provider used to get the time and manage time-oriented tasks like FPS calculations. */

        uint16_t m_width { 0 }; /**< Width of the window. */
        uint16_t m_height { 0 }; /**< Height of the window. */
    };

}

#endif /* CRUSTENGINE_WINDOW_H */
