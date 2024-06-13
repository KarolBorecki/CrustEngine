#include "rendering/projection/PerspectiveProjector.h"

#include <iostream> // TODO delete

namespace Crust {
    void PerspectiveProjector::setupCamera(Camera &camera) {
        m_camera = &camera;

        // Calculate projection matrix
        double q = camera.getFFar() / (camera.getFFar() - camera.getFNear());
        m_projection_matrix(0, 0) = m_aspect_ratio * camera.getFFovRad();
        m_projection_matrix(1, 1) = camera.getFFovRad();
        m_projection_matrix(2, 2) = q;
        m_projection_matrix(2, 3) = 1.0;
        m_projection_matrix(3, 2) = -(camera.getFFar() * camera.getFNear()) / (camera.getFFar() - camera.getFNear());

        // Calculate view matrix
        m_view_matrix = camera.transform().transformMatrix();
    }

    void PerspectiveProjector::setupLightning(LightSource &p_light, uint8_t p_ambient_light) {
        m_light = p_light;
        m_ambient_light = p_ambient_light;
    }

    void PerspectiveProjector::project(RenderObject &p_object) {
        m_translation_matrix = p_object.transform().transformMatrix();

        Color diffuse = {p_object.getMaterial().getDiffuse().r, p_object.getMaterial().getDiffuse().g,
                         p_object.getMaterial().getDiffuse().b, 1.0f};
        Color material_specular = p_object.getMaterial().getSpecular();
        float light_intensity = m_light.getIntensity();

        std::cout << "light intensity: " << light_intensity << std::endl;
        std::cout << "material specular: " << material_specular.r << " " << material_specular.g << " "
                  << material_specular.b << std::endl;
        std::cout << "material diffuse: " << diffuse.r << " " << diffuse.g << " " << diffuse.b << std::endl;

        for (auto face: p_object.getMesh().getPolygons()) {
            Matrix1x4f transformedP1, transformedP2, transformedP3;

            transformedP1 << face->getVertex(0).x(), face->getVertex(0).y(), face->getVertex(0).z(), 1.0f;
            transformedP2 << face->getVertex(1).x(), face->getVertex(1).y(), face->getVertex(1).z(), 1.0f;
            transformedP3 << face->getVertex(2).x(), face->getVertex(2).y(), face->getVertex(2).z(), 1.0f;

            transformedP1 *= m_translation_matrix;
            transformedP2 *= m_translation_matrix;
            transformedP3 *= m_translation_matrix;

            Vector3 v1_v3 = {transformedP1.x(), transformedP1.y(), transformedP1.z()};
            Vector3 normal = Math::normal(v1_v3, {transformedP2.x(), transformedP2.y(), transformedP2.z()},
                                          {transformedP3.x(), transformedP3.y(), transformedP3.z()});
            Vector3 light_normal = normal;

            Color ambient_color = {m_ambient_light * diffuse.r, m_ambient_light * diffuse.g,
                                   m_ambient_light * diffuse.b, 1.0f};

            Vector3 light_dir = m_light.transform().position() - v1_v3;
            light_dir.normalize();

            float diff = Math::max(light_dir.dot(normal), 0.0f);
            Color diffuse_color = {light_intensity * diff * diffuse.r, light_intensity * diff * diffuse.g,
                                   light_intensity * diff * diffuse.b, 1.0f};

            Vector3 view_dir = m_camera->transform().position() - v1_v3;
            view_dir.normalize();

            Vector3 reflect_dir = 2 * light_dir.dot(normal) * normal - light_dir;
            reflect_dir.normalize();

            float spec = (float) Math::power(Math::max(view_dir.dot(reflect_dir), 0.0f),
                                             p_object.getMaterial().getShininess());
            Color specular_color = {light_intensity * spec * material_specular.r,
                                    light_intensity * spec * material_specular.g,
                                    light_intensity * spec * material_specular.b};

            Color final_color = {ambient_color.r + diffuse_color.r + specular_color.r,
                                 ambient_color.g + diffuse_color.g + specular_color.g,
                                 ambient_color.b + diffuse_color.b + specular_color.b, 1.0f};

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
            uint8_t n_clipped_triangles = Math::triangle3DClipAgainstPlane(p_n, n, tri, out[0], out[1]);

            for (uint8_t n = 0; n < n_clipped_triangles; n++) {
                tri = out[n];
                transformedP1 << tri.getVertex(0).x(), tri.getVertex(0).y(), tri.getVertex(0).z(), transformedP1.w();
                transformedP2 << tri.getVertex(1).x(), tri.getVertex(1).y(), tri.getVertex(1).z(), transformedP2.w();
                transformedP3 << tri.getVertex(2).x(), tri.getVertex(2).y(), tri.getVertex(2).z(), transformedP3.w();

                v1_v3 = {transformedP1.x(), transformedP1.y(), transformedP1.z()};
                normal = Math::normal(v1_v3, {transformedP2.x(), transformedP2.y(), transformedP2.z()},
                                      {transformedP3.x(), transformedP3.y(), transformedP3.z()});

#ifndef CRUST_RENDERER_STOP_CULLING
                if (normal.dot(v1_v3) >= 0.0) {
                    continue;
                }
#endif
                // Projection
                transformedP1 *= m_projection_matrix;
                transformedP2 *= m_projection_matrix;
                transformedP3 *= m_projection_matrix;

                // Normalization & Data mapping
                m_projection_data.push_back({
                                                    Vector3((transformedP1.x() / transformedP1.w() + 1.0) * m_width *
                                                            0.5,
                                                            (transformedP1.y() / transformedP1.w() + 1.0) * m_height *
                                                            0.5, transformedP1.z() / transformedP1.w()),
                                                    Vector3((transformedP2.x() / transformedP2.w() + 1.0) * m_width *
                                                            0.5,
                                                            (transformedP2.y() / transformedP2.w() + 1.0) * m_height *
                                                            0.5, transformedP2.z() / transformedP2.w()),
                                                    Vector3((transformedP3.x() / transformedP3.w() + 1.0) * m_width *
                                                            0.5,
                                                            (transformedP3.y() / transformedP3.w() + 1.0) * m_height *
                                                            0.5, transformedP3.z() / transformedP3.w()),
                                                    final_color, final_color, final_color
                                            });
            }
        }
    }
}
