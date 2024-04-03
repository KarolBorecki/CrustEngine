#ifndef CRUSTENGINE_ROTATOR_H
#define CRUSTENGINE_ROTATOR_H

#include "scripting/Script.h"

namespace Crust {
    class Rotator : public Script {
    public:
        Rotator() = default;
        Rotator(float p_dx, float p_dy, float p_dz);

        void start() override;
        void update(float p_delta_time) override;

    private:
        float m_dx { 1.0f };
        float m_dy { 1.0f };
        float m_dz { 1.0f };
    };

    Rotator::Rotator(float p_dx, float p_dy, float p_dz) : m_dx(p_dx), m_dy(p_dy), m_dz(p_dz) { }

    inline void Rotator::start() {}

    inline void Rotator::update(float p_delta_time) {
        if (InputHandler::isPressed(Key::KeyCode::KEY_W)) {
            m_object->transform().rotateEuler(m_dx * p_delta_time, 0.0f, 0.0f);
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_S)) {
            m_object->transform().rotateEuler(-m_dx * p_delta_time, 0.0f, 0.0f);
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_A)) {
            m_object->transform().rotateEuler(0.0f, m_dy * p_delta_time, 0.0f);
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_D)) {
            m_object->transform().rotateEuler(0.0f, -m_dy * p_delta_time, 0.0f);
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_Q)) {
            m_object->transform().rotateEuler(0.0f, 0.0f, m_dz * p_delta_time);
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_E)) {
            m_object->transform().rotateEuler(0.0f, 0.0f, -m_dz * p_delta_time);
        }
    }
}


#endif /* CRUSTENGINE_ROTATOR_H */
