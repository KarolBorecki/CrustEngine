#include "core/Window.h"

namespace Crust {
    Window::Window(uint16_t p_width, uint16_t p_height) : m_renderer(*(new Renderer(p_width, p_height))), m_time_provider(*(new TimeProvider())) {
    }

    Window::~Window() {
        delete &m_renderer;
        unLoadScene();
    }

    Status Window::loadScene(Scene& p_scene) {
        return OK;
    }

    Status Window::unLoadScene() {
        return OK;
    }

    void Window::open() {

    }

    void Window::close() {
        unLoadScene();

    }
}