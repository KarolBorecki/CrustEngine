#include "objects/transforms/ObjectTransform.h"

namespace Crust {
    ObjectTransform::ObjectTransform() : Transform::Transform() {
        recalculateTranslationMatrix();
        recalculateScaleMatrix();
        recalculateRotationMatrix();
    }

    void ObjectTransform::setPosition(float p_x, float p_y, float p_z) {
        Transform::setPosition(p_x, p_y, p_z);
        recalculateTranslationMatrix();
    }

    void ObjectTransform::setSize(float p_x, float p_y, float p_z) {
        Transform::setSize(p_x, p_y, p_z);
        recalculateScaleMatrix();
    }

    void ObjectTransform::setEulerRotation(float p_x, float p_y, float p_z) {
        Transform::setEulerRotation(p_x, p_y, p_z);
        recalculateRotationMatrix();
    }

    void ObjectTransform::translate(float p_dx, float p_dy, float p_dz) {
        Transform::translate(p_dx, p_dy, p_dz);
        recalculateTranslationMatrix();
    }

    void ObjectTransform::scale(float p_dx, float p_dy, float p_dz) {
        Transform::scale(p_dx, p_dy, p_dz);
        recalculateScaleMatrix();
    }

    void ObjectTransform::rotateEuler(float p_dx, float p_dy, float p_dz) {
        Transform::rotateEuler(p_dx, p_dy, p_dz);
        recalculateRotationMatrix();
    }

    Matrix4x4f& ObjectTransform::transformMatrix() {
        return m_transform_mat;
    }

    void ObjectTransform::recalculateTransformMatrix() {
        m_transform_mat = m_scale_mat * m_rotation_z_mat * m_rotation_x_mat * m_rotation_y_mat * m_translation_mat;
    }

    void ObjectTransform::recalculateTranslationMatrix() {
        m_translation_mat = m_translation_mat.Identity();
        m_translation_mat(3, 0) = -m_position.x(); // TODO should be minus?
        m_translation_mat(3, 1) = -m_position.y();
        m_translation_mat(3, 2) = -m_position.z();
        recalculateTransformMatrix();
    }

    void ObjectTransform::recalculateScaleMatrix() {
        m_scale_mat = m_scale_mat.Identity();
        m_scale_mat(0, 0) = m_scale.x();
        m_scale_mat(1, 1) = m_scale.y();
        m_scale_mat(2, 2) = m_scale.z();
        recalculateTransformMatrix();
    }

    void ObjectTransform::recalculateRotationMatrix() {
        m_rotation_z_mat = m_rotation_z_mat.Identity();
        m_rotation_z_mat(0, 0) = Math::cos(m_rotation.z());
        m_rotation_z_mat(1, 0) = -Math::sin(m_rotation.z());
        m_rotation_z_mat(0, 1) = Math::sin(m_rotation.z());
        m_rotation_z_mat(1, 1) = Math::cos(m_rotation.z());
        m_rotation_z_mat(2, 2) = 1.0f;
        m_rotation_z_mat(3, 3) = 1.0f;

        m_rotation_x_mat = m_rotation_x_mat.Identity();
        m_rotation_x_mat(0, 0) = 1.0f;
        m_rotation_x_mat(1, 1) = Math::cos(m_rotation.x());
        m_rotation_x_mat(2, 1) = -Math::sin(m_rotation.x());
        m_rotation_x_mat(1, 2) = Math::sin(m_rotation.x());
        m_rotation_x_mat(2, 2) = Math::cos(m_rotation.x());
        m_rotation_x_mat(3, 3) = 1.0f;

        m_rotation_y_mat = m_rotation_y_mat.Identity();
        m_rotation_y_mat(0, 0) = Math::cos(m_rotation.y());
        m_rotation_y_mat(2, 0) = -Math::sin(m_rotation.y());
        m_rotation_y_mat(0, 2) = Math::sin(m_rotation.y());
        m_rotation_y_mat(1, 1) = 1.0f;
        m_rotation_y_mat(2, 2) = Math::cos(m_rotation.y());
        m_rotation_y_mat(3, 3) = 1.0f;
        recalculateTransformMatrix();
    }
}