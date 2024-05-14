#include "rendering/Renderer.h"

namespace Crust {
    Renderer::Renderer() : m_width(0), m_height(0), m_lib_2d() {
        setProjector(Projection::PERSPECTIVE);
    }

    Renderer::Renderer(uint16_t p_width, uint16_t p_height) : m_width(p_width), m_height(p_height), m_lib_2d() {
        setProjector(Projection::PERSPECTIVE); // TODO delete
    }

    Renderer::~Renderer() {
        if (m_projector == nullptr) {
            return;
        }

        delete m_projector;
    }

    void Renderer::renderScene(Scene &scene) {
        m_lib_2d.onDrawStart();

        m_projector->setupCamera(scene.getMainCamera());
        if (!scene.getLights().empty()) {
            m_projector->setupLightning(*scene.getLights()[0]);
        } else {
            Logger::warning("No lights in the scene!");
        }

        for (auto obj: scene.getRenderObjects()) {
            m_projector->project(*obj);
        }

        for (auto data: m_projector->retrieveProjections()) {
#ifndef CRUST_RENDERER_DRAW_WIREFRAME
            m_lib_2d.drawTriangle(data.v1.x(), data.v1.y(), data.v2.x(), data.v2.y(), data.v3.x(), data.v3.y(),
                                  data.r * data.light / 255, data.g * data.light / 255, data.b * data.light / 255,
                                  data.a);
#else
            m_lib_2d.drawLine(data.v1.x(), data.v1.y(), data.v2.x(), data.v2.y(), data.r * data.light / 255, data.g * data.light / 255, data.b * data.light / 255, data.a);
            m_lib_2d.drawLine(data.v2.x(), data.v2.y(), data.v3.x(), data.v3.y(), data.r * data.light / 255, data.g * data.light / 255, data.b * data.light / 255, data.a;
            m_lib_2d.drawLine(data.v3.x(), data.v3.y(), data.v1.x(), data.v1.y(), data.r * data.light / 255, data.g * data.light / 255, data.b * data.light / 255, data.a);
#endif
        }

        m_projector->clearProjections();

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
        m_projector->resize(p_width, p_height);
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

    bool Renderer::shouldClose() {
        return m_lib_2d.shouldClose();
    }
}
