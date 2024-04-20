#include "objects/transforms/CameraTransform.h"

namespace Crust {
    CameraTransform::CameraTransform() : Transform::Transform() {
    }

    void CameraTransform::recalculateTransformMatrix() {

    }

    // TODO optimize
    Matrix4x4f &CameraTransform::transformMatrix() {
        Matrix4x4f m_rotation_z_mat;
        m_rotation_z_mat(0, 0) = Math::cos(m_rotation.z());
        m_rotation_z_mat(1, 0) = -Math::sin(m_rotation.z());
        m_rotation_z_mat(0, 1) = Math::sin(m_rotation.z());
        m_rotation_z_mat(1, 1) = Math::cos(m_rotation.z());
        m_rotation_z_mat(2, 2) = 1.0f;
        m_rotation_z_mat(3, 3) = 1.0f;

        Matrix4x4f m_rotation_x_mat;
        m_rotation_x_mat(0, 0) = 1.0f;
        m_rotation_x_mat(1, 1) = Math::cos(m_rotation.x());
        m_rotation_x_mat(2, 1) = -Math::sin(m_rotation.x());
        m_rotation_x_mat(1, 2) = Math::sin(m_rotation.x());
        m_rotation_x_mat(2, 2) = Math::cos(m_rotation.x());
        m_rotation_x_mat(3, 3) = 1.0f;

        Matrix4x4f m_rotation_y_mat;
        m_rotation_y_mat(0, 0) = Math::cos(m_rotation.y());
        m_rotation_y_mat(2, 0) = -Math::sin(m_rotation.y());
        m_rotation_y_mat(0, 2) = Math::sin(m_rotation.y());
        m_rotation_y_mat(1, 1) = 1.0f;
        m_rotation_y_mat(2, 2) = Math::cos(m_rotation.y());
        m_rotation_y_mat(3, 3) = 1.0f;

        Matrix4x4f m_rotation_mat = m_rotation_z_mat * m_rotation_x_mat * m_rotation_y_mat;

        Vector3 Q = {m_position.x(), m_position.y(), m_position.z()};
        Vector4 v4_U = WORLD_RIGHT; // X
        v4_U *= m_rotation_mat;
        Vector4 v4_V = WORLD_UP;// Y
        v4_V *= m_rotation_mat;
        Vector4 v4_W = WORLD_FORWARD; // Z
        v4_W *= m_rotation_mat;

        Vector3 U = {v4_U.x(), v4_U.y(), v4_U.z()};
        Vector3 V = {v4_V.x(), v4_V.y(), v4_V.z()};
        Vector3 W = {v4_W.x(), v4_W.y(), v4_W.z()};

        m_transform_mat(0, 0) = U(0);
        m_transform_mat(1, 0) = U(1);
        m_transform_mat(2, 0) = U(2);
        m_transform_mat(3, 0) = -Q.dot(U);

        m_transform_mat(0, 1) = V(0);
        m_transform_mat(1, 1) = V(1);
        m_transform_mat(2, 1) = V(2);
        m_transform_mat(3, 1) = -Q.dot(V);

        m_transform_mat(0, 2) = W(0);
        m_transform_mat(1, 2) = W(1);
        m_transform_mat(2, 2) = W(2);
        m_transform_mat(3, 2) = -Q.dot(W);

        m_transform_mat(0, 3) = 0.0f;
        m_transform_mat(1, 3) = 0.0f;
        m_transform_mat(2, 3) = 0.0f;
        m_transform_mat(3, 3) = 1.0f;

        return m_transform_mat;
    }
}