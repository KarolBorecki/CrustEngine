#ifndef CRUSTENGINE_CAMERA_CONTROLLER_H
#define CRUSTENGINE_CAMERA_CONTROLLER_H

#include "scripting/Script.h"

#include "input/InputHandler.h"

namespace Crust {
    class CameraController : public Script {
    public:
        CameraController() = default;

        CameraController(double p_dx, double p_dy, double p_dz);

        void start() override;

        void update(double p_delta_time) override;

    private:
        double m_dx{1.0};
        double m_dy{1.0};
        double m_dz{1.0};
    };

    CameraController::CameraController(double p_dx, double p_dy, double p_dz) : m_dx(p_dx), m_dy(p_dy), m_dz(p_dz) {}

    inline void CameraController::start() {}

    inline void CameraController::update(double p_delta_time) {
        if (InputHandler::isPressed(Key::KeyCode::KEY_1)) {
            m_object->transform().rotateEuler(m_dx * p_delta_time, 0.0, 0.0);
            Logger::log("Rotating object by dx: %f\n", m_object->transform().eulerRotation().x());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_2)) {
            m_object->transform().rotateEuler(-m_dx * p_delta_time, 0.0, 0.0);
            Logger::log("Rotating object by -dx: %f\n", m_object->transform().eulerRotation().x());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_3)) {
            m_object->transform().rotateEuler(0.0, m_dy * p_delta_time, 0.0);
            Logger::log("Rotating object by dy: %f\n", m_object->transform().eulerRotation().y());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_4)) {
            m_object->transform().rotateEuler(0.0, -m_dy * p_delta_time, 0.0);
            Logger::log("Rotating object by -dy: %f\n", m_object->transform().eulerRotation().y());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_5)) {
            m_object->transform().rotateEuler(0.0, 0.0, m_dz * p_delta_time);
            Logger::log("Rotating object by dz: %f\n", m_object->transform().eulerRotation().z());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_6)) {
            m_object->transform().rotateEuler(0.0, 0.0, -m_dz * p_delta_time);
            Logger::log("Rotating object by -dz: %f\n", m_object->transform().eulerRotation().z());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_W)) {
            m_object->transform().translate(0.0, -m_dy * p_delta_time, 0.0);
            Logger::info("W (%d)", m_object->transform().position().x());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_S)) {
            m_object->transform().translate(0.0, m_dy * p_delta_time, 0.0);
            Logger::info("S (%d)", m_object->transform().position().x());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_A)) {
            m_object->transform().translate(m_dx * p_delta_time, 0.0, 0.0);
            Logger::info("A (%d)", m_object->transform().position().y());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_D)) {
            m_object->transform().translate(-m_dx * p_delta_time, 0.0, 0.0);
            Logger::info("D (%d)", m_object->transform().position().y());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_Q)) {
            m_object->transform().translate(0.0, 0.0, -m_dz * p_delta_time);
            Logger::info("Q (%d)", m_object->transform().position().z());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_E)) {
            m_object->transform().translate(0.0, 0.0, m_dz * p_delta_time);
            Logger::info("E (%d)", m_object->transform().position().z());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_K)) {
            m_object->transform().setSize(1.0, 1.0, 1.0);
            m_object->transform().setPosition(0.0, 0.0, 0.0);
            m_object->transform().setEulerRotation(0.0, 0.0, 0.0);

        }
    }
}


#endif /* CRUSTENGINE_CAMERA_CONTROLLER_H */
