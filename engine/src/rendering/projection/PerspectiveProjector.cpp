#include "rendering/projection/PerspectiveProjector.h"

#include <iostream> // TODO delete

namespace Crust {
    void PerspectiveProjector::setupCamera(Camera &camera) {
        // Calculate projection matrix
        static float q;
        m_projection_matrix(0, 0) = m_aspect_ratio * camera.getFFovRad();
        m_projection_matrix(1, 1) = camera.getFFovRad();
        m_projection_matrix(2, 2) = camera.getFFar() / (camera.getFFar() - camera.getFNear());
        m_projection_matrix(2, 3) = 1.0;
        m_projection_matrix(3, 2) = -(camera.getFFar() * camera.getFNear()) / (camera.getFFar() - camera.getFNear());
        // Calculate view matrix
        m_view_matrix = camera.transform().transformMatrix();
    }

    void PerspectiveProjector::setupLightning(LightSource &p_light) {
        m_light_direction = p_light.direction();
    }

    void PerspectiveProjector::project(
            RenderObject &p_object) {// TODO maybe keep in memory projected faces until something changes in certain object's translation?
        m_translation_matrix = p_object.transform().transformMatrix();
        m_light_direction.normalize();
        for (auto face: p_object.getMesh().getPolygons()) {
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

            transformedP1 *= m_view_matrix;
            transformedP2 *= m_view_matrix;
            transformedP3 *= m_view_matrix;

            // Clipping
            Triangle tri;
            tri.setVertex(0, transformedP1.x(), transformedP1.y(), transformedP1.z());
            tri.setVertex(1, transformedP2.x(), transformedP2.y(), transformedP2.z());
            tri.setVertex(2, transformedP3.x(), transformedP3.y(), transformedP3.z());

            Vector3 n(0.0, 0.0, 1.0);
            Vector3 p_n(0.0, 0.0, 0.3);

            Triangle out[2];

            uint8_t n_clipped_triangles = Math::triangleClipAgainstPlane(p_n, n, tri, out[0], out[1]);

            for (uint8_t n = 0; n < n_clipped_triangles; n++) {
                tri = out[n];
                transformedP1 << tri.getVertex(0).x(), tri.getVertex(0).y(), tri.getVertex(0).z(), transformedP1.w();
                transformedP2 << tri.getVertex(1).x(), tri.getVertex(1).y(), tri.getVertex(1).z(), transformedP2.w();
                transformedP3 << tri.getVertex(2).x(), tri.getVertex(2).y(), tri.getVertex(2).z(), transformedP3.w();

                Vector3 referencePoint = {transformedP1.x(), transformedP1.y(), transformedP1.z()};
                Vector3 normal = Math::normal(referencePoint,
                                              {transformedP2.x(), transformedP2.y(), transformedP2.z()},
                                              {transformedP3.x(), transformedP3.y(), transformedP3.z()});

#ifndef CRUST_RENDERER_STOP_CULLING
                if (normal.dot(referencePoint) > 0.0) {
                    continue;
                }

#endif
                static uint8_t light = 0;
                if (m_light_direction.dot(normal) > 0)
                    m_light_direction *= -1;
                light = m_light_direction.dot(normal) * 255;

                // Projection
                transformedP1 *= m_projection_matrix;
                transformedP2 *= m_projection_matrix;
                transformedP3 *= m_projection_matrix;

                // Normalization & Data mapping
                m_projection_data.push_back({Vector3((transformedP1.x() / transformedP1.w() + 1.0) * m_width * 0.5,
                                                     (transformedP1.y() / transformedP1.w() + 1.0) * m_height * 0.5,
                                                     transformedP1.z() / transformedP1.w()),
                                             Vector3((transformedP2.x() / transformedP2.w() + 1.0) * m_width * 0.5,
                                                     (transformedP2.y() / transformedP2.w() + 1.0) * m_height * 0.5,
                                                     transformedP2.z() / transformedP2.w()),
                                             Vector3((transformedP3.x() / transformedP3.w() + 1.0) * m_width * 0.5,
                                                     (transformedP3.y() / transformedP3.w() + 1.0) * m_height * 0.5,
                                                     transformedP3.z() / transformedP3.w()),
                                             light});
            }

        }
    }

}