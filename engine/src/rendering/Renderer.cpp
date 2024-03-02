#include "rendering/Renderer.h"

namespace Crust {
    Renderer::Renderer(uint16_t p_width, uint16_t p_height) : m_width(p_width), m_height(p_height) {
        m_lib_2d = new Library2DWrapper(p_width, p_height);
        m_projector = new PerspectiveProjector(p_width, p_height);
    }

    Renderer::~Renderer() {
        delete m_lib_2d;
        delete m_projector;
    }

    void Renderer::renderScene(Scene &scene) {
        // TODO: Implement
    }

    Status Renderer::setProjector(Projection p_projection_model) {
        switch (p_projection_model) {
            case Projection::PERSPECTIVE:
                delete m_projector;
                m_projector = new PerspectiveProjector(m_width, m_height);
                return OK;
        }
        return ERROR;
    }
}
