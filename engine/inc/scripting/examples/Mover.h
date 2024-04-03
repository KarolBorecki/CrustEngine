#ifndef CRUSTENGINE_MOVER_H
#define CRUSTENGINE_MOVER_H

#include "scripting/Script.h"

namespace Crust {
    class Mover : public Script {
    public:
        Mover() = default;

        void start() override;
        void update(float p_delta_time) override;

    private:
        float m_dx { 1.0f };
        float m_dy { 1.0f };
        float m_dz { 0.0f };
    };

    inline void Mover::start() {}

    inline void Mover::update(float p_delta_time) {
//        if (m_object->transform().position().x() > 10.0f) {
//            m_dx = -1.0f;
//        } else if (m_object->transform().position().x() < -10.0f) {
//            m_dx = 1.0f;
//        }

        if (m_object->transform().position().y() > 1.0f) {
            m_dy = -0.1f;
        } else if (m_object->transform().position().y() < -1.0f) {
            m_dy = 0.1f;
        }

        if (m_object->transform().position().z() > 1.0f) {
            m_dz = -0.1f;
        } else if (m_object->transform().position().z() < -1.0f) {
            m_dz = 0.1f;
        }

        m_object->transform().translate(m_dx * p_delta_time,
                                        m_dy * p_delta_time,
                                        m_dz * p_delta_time);
    }
}


#endif /* CRUSTENGINE_MOVER_H */
