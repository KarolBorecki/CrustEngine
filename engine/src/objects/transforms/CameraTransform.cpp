#include "objects/transforms/CameraTransform.h"

namespace Crust {
    CameraTransform::CameraTransform() : Transform::Transform() {
    }

    void CameraTransform::setPosition(float p_x, float p_y, float p_z) {
        Transform::setPosition(p_x, p_y, p_z);
    }

    void CameraTransform::setSize(float p_x, float p_y, float p_z) {
        Transform::setSize(p_x, p_y, p_z);
    }

    void CameraTransform::setEulerRotation(float p_x, float p_y, float p_z) {
        Transform::setEulerRotation(p_x, p_y, p_z);
    }

    void CameraTransform::translate(float p_dx, float p_dy, float p_dz) {
        Transform::translate(p_dx, p_dy, p_dz);
    }

    void CameraTransform::scale(float p_dx, float p_dy, float p_dz) {
        Transform::scale(p_dx, p_dy, p_dz);
    }

    void CameraTransform::rotateEuler(float p_dx, float p_dy, float p_dz) {
        Transform::rotateEuler(p_dx, p_dy, p_dz);
    }

    Matrix4x4f& CameraTransform::transformMatrix() {
        m_transform_mat.makeIdentity() ;
        Vector3 look_dir = {0.0f, 0.0f, 1.0f};
        Vector3 v_target = m_position;
        v_target += look_dir;

        return m_transform_mat;
    }
}