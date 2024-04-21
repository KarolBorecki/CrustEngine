#include "objects/transforms/Transform.h"

namespace Crust {
    Transform::Transform() : m_position({0.0, 0.0, 0.1}),
                             m_rotation({0.0, 0.0, 0.0}),
                             m_scale({1.0, 1.0, 1.0}) {}

    Crust::Vector3 &Transform::position() { return m_position; }

    Crust::Vector3 &Transform::size() { return m_scale; }

    Crust::Vector3 &Transform::eulerRotation() { return m_rotation; }

    void Transform::setPosition(double p_x, double p_y, double p_z) {
        m_position = {p_x, p_y, p_z};
        recalculateTranslationMatrix();
        recalculateTransformMatrix();
    }

    void Transform::setSize(double p_x, double p_y, double p_z) {
        m_scale = {p_x, p_y, p_z};
        recalculateScaleMatrix();
        recalculateTransformMatrix();
    }

    void Transform::setEulerRotation(double p_x, double p_y, double p_z) {
        m_rotation = {p_x, p_y, p_z};
        recalculateRotationMatrix();
        recalculateTransformMatrix();
    }

    void Transform::translate(double p_dx, double p_dy, double p_dz) {
        m_position(0) -= p_dx;
        m_position(1) -= p_dy;
        m_position(2) -= p_dz;
        recalculateTranslationMatrix();
        recalculateTransformMatrix();
    }

    void Transform::scale(double p_dx, double p_dy, double p_dz) {
        m_scale(0) += p_dx;
        m_scale(1) += p_dy;
        m_scale(2) += p_dz;
        recalculateScaleMatrix();
        recalculateTransformMatrix();
    }

    void Transform::rotateEuler(double p_dx, double p_dy, double p_dz) {
        m_rotation(0) += p_dx;
        m_rotation(1) += p_dy;
        m_rotation(2) += p_dz;
        recalculateRotationMatrix();
        recalculateTransformMatrix();
    }
}