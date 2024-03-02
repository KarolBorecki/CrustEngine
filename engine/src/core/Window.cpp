#include "core/Window.h"

namespace Crust {
    Window::Window(uint16_t p_width, uint16_t p_height) : m_renderer(*(new Renderer(p_width, p_height))), m_time_provider(*(new TimeProvider())) {
        Logger::info("Window created with width: %d and height: %d", p_width, p_height);
    }

    Window::~Window() {
        delete &m_renderer;
        delete &m_time_provider;
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
}