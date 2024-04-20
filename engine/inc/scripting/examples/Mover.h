#ifndef CRUSTENGINE_MOVER_H
#define CRUSTENGINE_MOVER_H

#include "scripting/Script.h"

#include "input/InputHandler.h"

namespace Crust {
    class Mover : public Script {
    public:
        Mover() = default;

        void start() override;

        void update(float p_delta_time) override;

    private:
        float m_dx{1.0f};
        float m_dy{1.0f};
        float m_dz{1.0f};
    };

    inline void Mover::start() {}

    inline void Mover::update(float p_delta_time) {
        if (InputHandler::isPressed(Key::KeyCode::KEY_W)) {
            m_object->transform().translate(0.0f, m_dy * p_delta_time, 0.0f);
            Logger::info("W (%d)", m_object->transform().position().x());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_S)) {
            m_object->transform().translate(0.0f, -m_dy * p_delta_time, 0.0f);
            Logger::info("S (%d)", m_object->transform().position().x());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_A)) {
            m_object->transform().translate(m_dx * p_delta_time, 0.0f, 0.0f);
            Logger::info("A (%d)", m_object->transform().position().y());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_D)) {
            m_object->transform().translate(-m_dx * p_delta_time, 0.0f, 0.0f);
            Logger::info("D (%d)", m_object->transform().position().y());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_Q)) {
            m_object->transform().translate(0.0f, 0.0f, m_dz * p_delta_time);
            Logger::info("Q (%d)", m_object->transform().position().z());
        }
        if (InputHandler::isPressed(Key::KeyCode::KEY_E)) {
            m_object->transform().translate(0.0f, 0.0f, -m_dz * p_delta_time);
            Logger::info("E (%d)", m_object->transform().position().z());
        }
    }
}


#endif /* CRUSTENGINE_MOVER_H */
