#include "core/Window.h"

namespace Crust {
    Window::Window(uint16_t p_width, uint16_t p_height) {
        Logger::info("Window created with width: %d and height: %d", p_width, p_height);
        m_renderer = new Renderer(p_width, p_height);
        m_time_provider = new TimeProvider();
    }

    Window::~Window() {
        unLoadScene();
        delete m_renderer;
        delete m_time_provider;
    }

    Status Window::loadScene(Scene& p_scene) {
        if (p_scene.isLoaded() || m_scene != nullptr) {
            return ERROR;
        }
        m_scene = &p_scene;
        m_scene->onLoad();
        return OK;
    }

    Status Window::unLoadScene() {
        if  (m_scene == nullptr) {
            return OK;
        }
        m_scene->onUnLoad();
        m_scene = nullptr;
        return OK;
    }

    void Window::open() {
        // TODO Implement
    }

    void Window::close() {
        unLoadScene();
    }

    Status Window::changeProjection(Projection p_projection_model) {
        return m_renderer->setProjector(p_projection_model);
    }
}