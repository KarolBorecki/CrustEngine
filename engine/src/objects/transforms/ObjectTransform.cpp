#include "objects/transforms/ObjectTransform.h"

namespace Crust {
    ObjectTransform::ObjectTransform() : Transform::Transform() {
        recalculateTranslationMatrix();
        recalculateScaleMatrix();
        recalculateRotationMatrix();
        recalculateTransformMatrix();
    }

    Matrix4x4f &ObjectTransform::transformMatrix() {
        return m_transform_mat;
    }

    void ObjectTransform::recalculateTransformMatrix() {
        m_transform_mat = m_scale_mat * m_rotation_z_mat * m_rotation_x_mat * m_rotation_y_mat * m_translation_mat;
    }

    void ObjectTransform::recalculateTranslationMatrix() {
        m_translation_mat = m_translation_mat.Identity();
        m_translation_mat(3, 0) = m_position.x(); // TODO should be minus?
        m_translation_mat(3, 1) = m_position.y();
        m_translation_mat(3, 2) = m_position.z();
    }

    void ObjectTransform::recalculateScaleMatrix() {
        m_scale_mat = m_scale_mat.Identity();
        m_scale_mat(0, 0) = m_scale.x();
        m_scale_mat(1, 1) = m_scale.y();
        m_scale_mat(2, 2) = m_scale.z();
    }

    void ObjectTransform::recalculateRotationMatrix() {
        m_rotation_z_mat(0, 0) = Math::cos(m_rotation.z());
        m_rotation_z_mat(1, 0) = -Math::sin(m_rotation.z());
        m_rotation_z_mat(0, 1) = Math::sin(m_rotation.z());
        m_rotation_z_mat(1, 1) = Math::cos(m_rotation.z());
        m_rotation_z_mat(2, 2) = 1.0f;
        m_rotation_z_mat(3, 3) = 1.0f;

        m_rotation_x_mat(0, 0) = 1.0f;
        m_rotation_x_mat(1, 1) = Math::cos(m_rotation.x());
        m_rotation_x_mat(2, 1) = -Math::sin(m_rotation.x());
        m_rotation_x_mat(1, 2) = Math::sin(m_rotation.x());
        m_rotation_x_mat(2, 2) = Math::cos(m_rotation.x());
        m_rotation_x_mat(3, 3) = 1.0f;

        m_rotation_y_mat(0, 0) = Math::cos(m_rotation.y());
        m_rotation_y_mat(2, 0) = -Math::sin(m_rotation.y());
        m_rotation_y_mat(0, 2) = Math::sin(m_rotation.y());
        m_rotation_y_mat(1, 1) = 1.0f;
        m_rotation_y_mat(2, 2) = Math::cos(m_rotation.y());
        m_rotation_y_mat(3, 3) = 1.0f;
    }
}