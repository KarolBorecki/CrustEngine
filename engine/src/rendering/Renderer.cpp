#include "rendering/Renderer.h"

namespace Crust {
    Renderer::Renderer() : m_width(0), m_height(0), m_lib_2d(), m_projector(0, 0) {}

    Renderer::Renderer(uint16_t p_width, uint16_t p_height) : m_width(p_width), m_height(p_height), m_lib_2d(), m_projector(p_width, p_height) {}

    void Renderer::renderScene(Scene &scene) {
        m_lib_2d.onDrawStart();
        m_lib_2d.drawTriangle(600, 0, 0, 0, 300, 500, 255);
        m_lib_2d.onDrawEnd();
    }

    void Renderer::openWindow(uint16_t p_width, uint16_t p_height) {
        Logger::info("Window created with width: %d and height: %d", p_width, p_height);
        m_lib_2d.init();
        m_lib_2d.createWindow(p_width, p_height);
    }

    void Renderer::close() {
        m_lib_2d.close();
    }

    void Renderer::resize(uint16_t p_width, uint16_t p_height) {
        m_width = p_width;
        m_height = p_height;
        m_lib_2d.resize(p_width, p_height);
        m_projector.resize(p_width, p_height);
    }

    Status Renderer::setProjector(Projection p_projection_model) {
        switch (p_projection_model) {
            case Projection::PERSPECTIVE:
                m_projector = PerspectiveProjector(m_width, m_height); // TODO memory leak?
                return OK;
        }
        return ERROR;
    }

    bool Renderer::shouldClose() {
        return m_lib_2d.shouldClose();
    }
}
