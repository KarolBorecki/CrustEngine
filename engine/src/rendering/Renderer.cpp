#include "rendering/Renderer.h"

namespace Crust {
    Renderer::Renderer() : m_width(0), m_height(0), m_lib_2d(0, 0), m_projector(0, 0) {}

    Renderer::Renderer(uint16_t p_width, uint16_t p_height) : m_width(p_width), m_height(p_height), m_lib_2d(p_width, p_height), m_projector(p_width, p_height) {}

    void Renderer::renderScene(Scene &scene) {
        // TODO: Implement
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
}
