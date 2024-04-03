#include "rendering/projection/PerspectiveProjector.h"

#include <iostream> // TODO delete

namespace Crust {
    void PerspectiveProjector::setupCamera(Camera& camera) {
        // Calculate projection matrix
        static float q;
        m_projection_matrix(0, 0) = m_aspect_ratio * camera.getFFovRad();
        m_projection_matrix(1, 1) = camera.getFFovRad();
        m_projection_matrix(2, 2) = camera.getFFar() / (camera.getFFar() - camera.getFNear());
        m_projection_matrix(2, 3) = 1.0f;
        m_projection_matrix(3, 2) = -(camera.getFFar() * camera.getFNear()) / (camera.getFFar() - camera.getFNear());
        // Calculate view matrix
        // m_view_matrix = camera.getTransformationMatrix().inverse(); // is it tho?

    }

    void PerspectiveProjector::setupLightning(LightSource& p_light) {
        m_light_direction = p_light.direction();
    }

    void PerspectiveProjector::project(RenderObject& p_object) {
        Transform& transform = p_object.transform();
        static Matrix4x4f translation_mat;
        translation_mat = translation_mat.Identity();
        translation_mat(3, 0) = transform.position().x();
        translation_mat(3, 1) = transform.position().y();
        translation_mat(3, 2) = transform.position().z();

        static Matrix4x4f scale_mat;
        scale_mat(0, 0) = transform.size().x();
        scale_mat(1, 1) = transform.size().y();
        scale_mat(2, 2) = transform.size().z();
        scale_mat(3, 3) = 1.0f;

        static Matrix4x4f rotation_z_mat;
        rotation_z_mat(0, 0) = Math::cos(transform.eulerRotation().z());
        rotation_z_mat(1, 0) = -Math::sin(transform.eulerRotation().z());
        rotation_z_mat(0, 1) = Math::sin(transform.eulerRotation().z());
        rotation_z_mat(1, 1) = Math::cos(transform.eulerRotation().z());
        rotation_z_mat(2, 2) = 1.0f;
        rotation_z_mat(3, 3) = 1.0f;

        static Matrix4x4f rotation_x_mat;
        rotation_x_mat(0, 0) = 1.0f;
        rotation_x_mat(1, 1) = Math::cos(transform.eulerRotation().x());
        rotation_x_mat(2, 1) = -Math::sin(transform.eulerRotation().x());
        rotation_x_mat(1, 2) = Math::sin(transform.eulerRotation().x());
        rotation_x_mat(2, 2) = Math::cos(transform.eulerRotation().x());
        rotation_x_mat(3, 3) = 1.0f;

        static Matrix4x4f rotation_y_mat;
        rotation_y_mat(0, 0) = Math::cos(transform.eulerRotation().y());
        rotation_y_mat(2, 0) = -Math::sin(transform.eulerRotation().y());
        rotation_y_mat(0, 2) = Math::sin(transform.eulerRotation().y());
        rotation_y_mat(1, 1) = 1.0f;
        rotation_y_mat(2, 2) = Math::cos(transform.eulerRotation().y());
        rotation_y_mat(3, 3) = 1.0f;

        static Matrix4x4f rotation_mat;
        rotation_mat = rotation_z_mat * rotation_x_mat * rotation_y_mat;
        m_translation_matrix = scale_mat * rotation_mat * translation_mat;

        for (auto face : p_object.getMesh().getPolygons()) {
            // Translation
            static Matrix1x4f transformedP1;
            static Matrix1x4f transformedP2;
            static Matrix1x4f transformedP3;

            transformedP1 << face->getVertex(0).x(), face->getVertex(0).y(), face->getVertex(0).z(), 1.0f;
            transformedP2 << face->getVertex(1).x(), face->getVertex(1).y(), face->getVertex(1).z(), 1.0f;
            transformedP3 << face->getVertex(2).x(), face->getVertex(2).y(), face->getVertex(2).z(), 1.0f;

            transformedP1 *= m_translation_matrix;
            transformedP2 *= m_translation_matrix;
            transformedP3 *= m_translation_matrix;

            // Backface culling
            Vector3<> referencePoint = {transformedP1.x(), transformedP1.y(), transformedP1.z()};
            Vector3<> normal = Math::normal(referencePoint,
                                            {transformedP2.x(), transformedP2.y(), transformedP2.z()},
                                            {transformedP3.x(), transformedP3.y(), transformedP3.z()});
            if (normal.dot(referencePoint) < 0.0f) {
                static uint8_t light = 0;
                Vector3<> lightDirNormal;
                lightDirNormal = m_light_direction;
                lightDirNormal.normalize();
                if(lightDirNormal.dot(normal) < 0.0f)
                    lightDirNormal *= -1.0f;
                light = m_light_direction.normalized().dot(normal) * 255;

                // Projection
                transformedP1 *= m_projection_matrix;
                transformedP2 *= m_projection_matrix;
                transformedP3 *= m_projection_matrix;


                // Normalization
                static Vector3<> projectedP1;
                static Vector3<> projectedP2;
                static Vector3<> projectedP3;

                projectedP1 << transformedP1.x(), transformedP1.y(), transformedP1.z();
                projectedP2 << transformedP2.x(), transformedP2.y(), transformedP2.z();
                projectedP3 << transformedP3.x(), transformedP3.y(), transformedP3.z();

                projectedP1 /= transformedP1.w();
                projectedP2 /= transformedP2.w();
                projectedP3 /= transformedP3.w();

                static Vector3<> viewOffset(1.0f, 1.0f, 0.0f);
                projectedP1 += viewOffset;
                projectedP2 += viewOffset;
                projectedP3 += viewOffset;

                // Data mapping
                projectedP1 << (projectedP1.x()) * m_width * 0.5f, (projectedP1.y()) * m_height * 0.5f, projectedP1.z();
                projectedP2 << (projectedP2.x()) * m_width * 0.5f, (projectedP2.y()) * m_height * 0.5f, projectedP2.z();;
                projectedP3 << (projectedP3.x()) * m_width * 0.5f, (projectedP3.y()) * m_height * 0.5f, projectedP3.z();;

                m_projection_data.push_back({ projectedP1.x(), projectedP1.y(),projectedP1.z(),
                                              projectedP2.x(), projectedP2.y(), projectedP2.z(),
                                              projectedP3.x(), projectedP3.y(), projectedP3.z(),
                                              light });
            }
        }
    }

}