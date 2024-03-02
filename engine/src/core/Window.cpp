#include "core/Window.h"

namespace Crust {
    Window::Window(uint16_t p_width, uint16_t p_height) : m_renderer(p_width, p_height) {
        Logger::info("Window created with width: %d and height: %d", p_width, p_height);
    }

    Window::~Window() {
        Logger::log("Window destroyed.");
        unLoadScene();
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
        m_renderer.openWindow(m_width, m_height);
    }

    void Window::close() {
        unLoadScene();
    }

    Status Window::changeProjection(Projection p_projection_model) {
        return m_renderer.setProjector(p_projection_model);
    }
}