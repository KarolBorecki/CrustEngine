#include "objects/transforms/CameraTransform.h"

#include <iostream>

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

    // TODO optimize
    Matrix4x4f &CameraTransform::transformMatrix() {
        Vector3 look_dir = {0.0f, 0.0f, 1.0f};

        Vector3 Q = m_position;
        Vector3 T = m_position;
        T += look_dir;

        Vector3 W = T;
        W -= Q; // it really is just W = look_dir
        W.normalize();

        Vector3 U = WORLD_UP;
        U = U.cross(W);
        U.normalize();

        Vector3 V = U;
        V = V.cross(W);

        m_transform_mat(0, 0) = U(0);
        m_transform_mat(1, 0) = U(1);
        m_transform_mat(2, 0) = U(2);
        m_transform_mat(3, 0) = -Q.dot(U);

        m_transform_mat(0, 1) = V(0);
        m_transform_mat(1, 1) = -V(1);
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