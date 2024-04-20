#include "objects/transforms/CameraTransform.h"

#include <iostream>

namespace Crust {
    CameraTransform::CameraTransform() : Transform::Transform() {
    }

//    void CameraTransform::setPosition(float p_x, float p_y, float p_z) {
//        Transform::setPosition(p_x, p_y, p_z);
//    }
//
//    void CameraTransform::setSize(float p_x, float p_y, float p_z) {
//        Transform::setSize(p_x, p_y, p_z);
//    }
//
//    void CameraTransform::setEulerRotation(float p_x, float p_y, float p_z) {
//        Transform::setEulerRotation(p_x, p_y, p_z);
//    }
//
//    void CameraTransform::translate(float p_dx, float p_dy, float p_dz) {
//        Transform::translate(p_dx, p_dy, p_dz);
//    }
//
//    void CameraTransform::scale(float p_dx, float p_dy, float p_dz) {
//        Transform::scale(p_dx, p_dy, p_dz);
//    }
//
//    void CameraTransform::rotateEuler(float p_dx, float p_dy, float p_dz) {
//        Transform::rotateEuler(p_dx, p_dy, p_dz);
//    }

    // TODO optimize
    Matrix4x4f &CameraTransform::transformMatrix() {
//        Matrix1x4f target;
//        target << 0.0f, 0.0f, 1.0f, 1.0f;
//
//        Matrix4x4f m_rotation_z_mat;
//        m_rotation_z_mat(0, 0) = Math::cos(m_rotation.z());
//        m_rotation_z_mat(1, 0) = -Math::sin(m_rotation.z());
//        m_rotation_z_mat(0, 1) = Math::sin(m_rotation.z());
//        m_rotation_z_mat(1, 1) = Math::cos(m_rotation.z());
//        m_rotation_z_mat(2, 2) = 1.0f;
//        m_rotation_z_mat(3, 3) = 1.0f;
//
//        Matrix4x4f m_rotation_x_mat;
//        m_rotation_x_mat(0, 0) = 1.0f;
//        m_rotation_x_mat(1, 1) = Math::cos(m_rotation.x());
//        m_rotation_x_mat(2, 1) = -Math::sin(m_rotation.x());
//        m_rotation_x_mat(1, 2) = Math::sin(m_rotation.x());
//        m_rotation_x_mat(2, 2) = Math::cos(m_rotation.x());
//        m_rotation_x_mat(3, 3) = 1.0f;
//
//        Matrix4x4f m_rotation_y_mat;
//        m_rotation_y_mat(0, 0) = Math::cos(m_rotation.y());
//        m_rotation_y_mat(2, 0) = -Math::sin(m_rotation.y());
//        m_rotation_y_mat(0, 2) = Math::sin(m_rotation.y());
//        m_rotation_y_mat(1, 1) = 1.0f;
//        m_rotation_y_mat(2, 2) = Math::cos(m_rotation.y());
//        m_rotation_y_mat(3, 3) = 1.0f;
//
//        target *= m_rotation_y_mat;
//        Vector3 v_target;
//        v_target << target.x(), target.y(), target.z();
//        v_target -= m_position.normalized();
        Vector3 v_target = {0.4f, 0.0f, 1.0f};
        std::cout << "v_target: " << std::endl << v_target << std::endl;
        // DO NOT TOUCH THIS CODE
        Vector3 Q = m_position;
        Vector3 T = v_target;
        v_target -= m_position;

        Vector3 W = T;
        W -= Q;
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

        m_transform_mat(0, 1) = -V(0);
        m_transform_mat(1, 1) = -V(1);
        m_transform_mat(2, 1) = -V(2);
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