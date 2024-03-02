#ifndef CRUSTENGINE_SCENE_H
#define CRUSTENGINE_SCENE_H

#include <string>

#include "static/Config.h"
#include "objects/Object.h"
#include "objects/Camera.h"
#include "objects/RenderObject.h"
#include "objects/LightSource.h"

namespace Crust {
    /**
     * @brief Scene class. It's a container for all objects rendered onto the window.
     *
     */
    class Scene {
    public:
        /**
         * @brief Construct a new Scene object with name set to default scene name and main camera set to nullptr.
         */
        Scene();

        /**
         * @brief Construct a new Scene object with name set to #p_name and main camera set to nullptr.
         *
         * @param p_name Name of the scene.
         */
        Scene(const char* p_name);

        /**
         * @brief Construct a new Scene object with name set to default scene name and main camera set to #main_camera.
         *
         * @param name Name of the scene.
         * @param main_camera Main camera of the scene.
         */
        explicit Scene(Camera& main_camera);

        /**
         * @brief Construct a new Scene object with name set to #p_name and main camera set to #p_main_camera.
         *
         * @param p_name Name of the scene.
         * @param p_main_camera Main camera of the scene.
         */
        Scene(const char* p_name, Camera& p_main_camera);

        /**
         * @brief Destroy the Scene object. Remember that it will not delete any objects in the scene.
         */
        virtual ~Scene() = default;

        /**
         * @brief Called when scene is loaded. Sets #m_loaded to true. calls #start method if not started yet and #reload method otherwise.
         */
        void onLoad();

        /**
         * @brief Called when scene is unloaded. Sets #m_loaded to false and #m_started to false.
         */
        void onUnLoad();

        /**
         * @brief Called when scene is started. Sets #m_started to true. Calls start method on every script in this scene.
         */
        void start();

        /**
         * @brief Called in each frame. Calls update method on every script in this scene.
         */
        void update();

        /**
         * @brief Called when scene is reloaded. Calls reload method on every script in this scene.
         */
        void reload();

        /**
         * @brief Getter for #m_name field.
         *
         * @return Name of the scene.
         */
        const char* getName() const;

        /**
         * @brief Getter for #m_camera field.
         *
         * @return Pointer to camera, which will be new main camera (From it's perspective the world will be rendered).
         *
         * @sa Camera.hpp
         */
        Camera& getMainCamera() const;

        /**
         * @brief Setter for #m_camera field.
         *
         * @param p_camera New main camera.
         */
        void setMainCamera(Camera& p_camera);

        /**
         * @brief Getter for #m_loaded field. Determines whether scene is being rendered onto the window.
         *
         * @return #m_loaded field.
         */
        bool isLoaded() const;

        /**
         * @brief Getter for #m_started field. Determines whether scene was already started.
         *
         * @return #m_started field.
         */
        bool isStarted() const;

        /**
         * @brief Getter for #m_objects field.
         *
         * @return #m_objects field.
         */
        std::vector<Object*> getObjects() const;

        /**
         * @brief Getter for #m_lights field.
         *
         * @return #m_lights field.
         */
        std::vector<LightSource*> getLights() const;

        /**
         * @brief Getter for #m_render_objects field.
         *
         * @return #m_render_objects field.
         */
        std::vector<RenderObject*> getRenderObjects() const;

        /**
         * @brief Adds object to the scene.
         *
         * @param p_object Object to be added to the scene.
         */
        Status addObject(Object& p_object);

    private:
        bool m_loaded { false }; /**< Determines whether scene is being rendered onto the window. */
        bool m_started { false }; /**< Determines whether scene was already started. */

        const char* m_name; /**< Name of the scene. */

        //TODO remember to show no camera info on the screen when camera is nullptr
        Camera* m_camera { nullptr }; /**< Main camera of the scene. */

        std::vector<Object*> m_objects; /**< Objects in the scene. */
        std::vector<LightSource*> m_lights; /**< Light sources in the scene. */
        std::vector<RenderObject*> m_render_objects; /**< Renderable objects in the scene. */
    };
}

#endif /* CRUSTENGINE_SCENE_H */
