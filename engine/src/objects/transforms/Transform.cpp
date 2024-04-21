#include "objects/transforms/Transform.h"

namespace Crust {
    Transform::Transform() : m_position({0.0f, 0.0f, 0.10f}),
                             m_rotation({0.0f, 0.0f, 0.0f}),
                             m_scale({1.0f, 1.0f, 1.0f}) {}

    Crust::Vector3 &Transform::position() { return m_position; }

    Crust::Vector3 &Transform::size() { return m_scale; }

    Crust::Vector3 &Transform::eulerRotation() { return m_rotation; }

    void Transform::setPosition(float p_x, float p_y, float p_z) {
        m_position = {p_x, p_y, p_z};
        recalculateTranslationMatrix();
        recalculateTransformMatrix();
    }

    void Transform::setSize(float p_x, float p_y, float p_z) {
        m_scale = {p_x, p_y, p_z};
        recalculateScaleMatrix();
        recalculateTransformMatrix();
    }

    void Transform::setEulerRotation(float p_x, float p_y, float p_z) {
        m_rotation = {p_x, p_y, p_z};
        recalculateRotationMatrix();
        recalculateTransformMatrix();
    }

    void Transform::translate(float p_dx, float p_dy, float p_dz) {
        m_position(0) -= p_dx;
        m_position(1) -= p_dy;
        m_position(2) -= p_dz;
        recalculateTranslationMatrix();
        recalculateTransformMatrix();
    }

    void Transform::scale(float p_dx, float p_dy, float p_dz) {
        m_scale(0) += p_dx;
        m_scale(1) += p_dy;
        m_scale(2) += p_dz;
        recalculateScaleMatrix();
        recalculateTransformMatrix();
    }

    void Transform::rotateEuler(float p_dx, float p_dy, float p_dz) {
        m_rotation(0) += p_dx;
        m_rotation(1) += p_dy;
        m_rotation(2) += p_dz;
        recalculateRotationMatrix();
        recalculateTransformMatrix();
    }
}