#include "objects/Transform.h"

namespace Crust {
    Transform::Transform() :
        m_position(*(new Vector3<>(0.0f, 0.0f, 0.0f))),
        m_rotation(*(new Vector3<>(0.0f, 0.0f, 0.0f))),
        m_scale(*(new Vector3<>(1.0f, 1.0f, 1.0f))) {}


    inline Crust::Vector3<> &Transform::getPosition() { return m_position; }

    inline Crust::Vector3<> &Transform::getScale() { return m_scale; }

    inline Crust::Vector3<> &Transform::getEulerRotation() { return m_rotation; }

    inline void Transform::setPosition(float p_x, float p_y, float p_z) { m_position = {p_x, p_y, p_z}; }

    inline void Transform::setScale(float p_x, float p_y, float p_z) { m_scale = {p_x, p_y, p_z}; }

    inline void Transform::setEulerRotation(float p_x, float p_y, float p_z) { m_rotation = {p_x, p_y, p_z}; }

    inline void Transform::translate(float p_dx, float p_dy, float p_dz) {
        m_position(0) += p_dx;
        m_position(0) += p_dy;
        m_position(0) += p_dz;
    }

    inline void Transform::scale(float p_dx, float p_dy, float p_dz) {
        m_scale(0) += p_dx;
        m_scale(0) += p_dy;
        m_scale(0) += p_dz;
    }

    inline void Transform::rotateEuler(float p_dx, float p_dy, float p_dz) {
        m_rotation(0) += p_dx;
        m_rotation(0) += p_dy;
        m_rotation(0) += p_dz;
    }
}