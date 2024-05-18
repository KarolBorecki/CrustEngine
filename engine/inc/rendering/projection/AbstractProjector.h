#ifndef CRUSTENGINE_ABSTRACTPROJECTOR_H
#define CRUSTENGINE_ABSTRACTPROJECTOR_H

#include <cstdint>
#include "objects/Camera.h"
#include "objects/LightSource.h"
#include "objects/RenderObject.h"
#include "math/Matrix.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include <random>

namespace Crust {
    /**
     * @brief A projector base class. Defines basic operations that can be implemented based on different projection models.
     */
    class AbstractProjector {
    public:
        typedef struct ProjectionData {
            Vector3 v1;
            Vector3 v2;
            Vector3 v3;
            uint8_t r, g, b, a;
            uint8_t light = 0;
        } ProjectionData_t;

        /**
         * @brief Construct a new Projector object with the specified width and height.
         *
         * @param p_width The width of the projector.
         * @param p_height The height of the projector.
         */
        AbstractProjector(uint16_t p_width, uint16_t p_height) : m_width(p_width), m_height(p_height) {
            m_aspect_ratio = (float) p_height / (float) p_width;
        }

        /**
         * @brief Destroy the Projector object.
         */
        virtual ~AbstractProjector() = default;

        /**
         * @brief Gets the camera ready for the frame. Prepares projection and view matrixes.
         *
         * @param camera - main camera on the scene from which projection will be done.
         */
        virtual void setupCamera(Camera &camera) = 0;

        /**
         * @brief Setups the lightning on the scene. Saves the direction of the perpendicular rays (currently on this is supported).
         *
         * @param p_light - Light source which emits the light on the scene.
         */
        virtual void setupLightning(LightSource &p_light) = 0; // TODO handle multiple lights?

        /**
         * @brief Projects the Render object and saves projected faces to the #m_projection_data vector.
         *
         * @param p_object - object to project.
         */
        virtual void project(RenderObject &p_object) = 0;

        /**
         * @brief Retrieve the projection data, which is the data of the projections made in the current frame.
         *
         * @return std::vector<ProjectionData_t> The projection data.
         */
        inline virtual std::vector<ProjectionData_t> retrieveProjections() {
#ifndef CRUST_STOP_TRIANGLE_DIVISION_IN_PROJECTION_SORTING
            uint32_t size = m_projection_data.size();
            std::vector<ProjectionData_t> local_clips_stack;
            static Triangle out_tri_1;
            static Triangle out_tri_2;
            static Triangle out_tri_3;
            static Triangle clipped_tri;
            static Triangle edge_tri;
            static uint8_t max_iterations = 0;
            for (uint32_t i = 0; i < size; i++) {
                size = m_projection_data.size();
                Logger::log("-------------------------------iteration: %d, size = %d", i, m_projection_data.size());
                for (uint32_t j = i + 1; j < size; j++) {
//                    Logger::log("        tick: %d", j);
                    clipped_tri.setVertex(0, m_projection_data[j].v1);
                    clipped_tri.setVertex(1, m_projection_data[j].v2);
                    clipped_tri.setVertex(2, m_projection_data[j].v3);

                    uint8_t n_clipped_triangles = Math::triangle2DClipAgainstEdge(m_projection_data[i].v1,
                                                                                  m_projection_data[i].v2,
                                                                                  clipped_tri,
                                                                                  out_tri_1,
                                                                                  out_tri_2,
                                                                                  out_tri_3);
                    if (n_clipped_triangles > 0) {
                        local_clips_stack.push_back({out_tri_1.getVertex(0),
                                                     out_tri_1.getVertex(1),
                                                     out_tri_1.getVertex(2),
                                                     m_projection_data[j].r,
                                                     m_projection_data[j].g,
                                                     m_projection_data[j].b,
                                                     m_projection_data[j].a,
                                                     m_projection_data[j].light});
                    }
                    if (n_clipped_triangles > 1) {
                        local_clips_stack.push_back({out_tri_2.getVertex(0),
                                                     out_tri_2.getVertex(1),
                                                     out_tri_2.getVertex(2),
                                                     m_projection_data[j].r,
                                                     m_projection_data[j].g,
                                                     m_projection_data[j].b,
                                                     m_projection_data[j].a,
                                                     m_projection_data[j].light});
                    }

                    if (n_clipped_triangles > 2) {
                        local_clips_stack.push_back({out_tri_3.getVertex(0),
                                                     out_tri_3.getVertex(1),
                                                     out_tri_3.getVertex(2),
                                                     m_projection_data[j].r,
                                                     m_projection_data[j].g,
                                                     m_projection_data[j].b,
                                                     m_projection_data[j].a,
                                                     m_projection_data[j].light});
                    }
                    uint8_t stack_size = local_clips_stack.size();
                    for (uint32_t j = 0; j < stack_size; j++) {
                        clipped_tri.setVertex(0, local_clips_stack[j].v1);
                        clipped_tri.setVertex(1, local_clips_stack[j].v2);
                        clipped_tri.setVertex(2, local_clips_stack[j].v3);
                        n_clipped_triangles = Math::triangle2DClipAgainstEdge(m_projection_data[i].v1,
                                                                              m_projection_data[i].v3,
                                                                              clipped_tri,
                                                                              out_tri_1,
                                                                              out_tri_2,
                                                                              out_tri_3);
                        if (n_clipped_triangles > 0) {
                            local_clips_stack.push_back({out_tri_1.getVertex(0),
                                                         out_tri_1.getVertex(1),
                                                         out_tri_1.getVertex(2),
                                                         local_clips_stack[j].r,
                                                         local_clips_stack[j].g,
                                                         local_clips_stack[j].b,
                                                         local_clips_stack[j].a,
                                                         local_clips_stack[j].light});
                        }
                        if (n_clipped_triangles > 1) {
                            local_clips_stack.push_back({out_tri_2.getVertex(0),
                                                         out_tri_2.getVertex(1),
                                                         out_tri_2.getVertex(2),
                                                         local_clips_stack[j].r,
                                                         local_clips_stack[j].g,
                                                         local_clips_stack[j].b,
                                                         local_clips_stack[j].a,
                                                         local_clips_stack[j].light});
                        }
                        if (n_clipped_triangles > 2) {
                            local_clips_stack.push_back({out_tri_3.getVertex(0),
                                                         out_tri_3.getVertex(1),
                                                         out_tri_3.getVertex(2),
                                                         local_clips_stack[j].r,
                                                         local_clips_stack[j].g,
                                                         local_clips_stack[j].b,
                                                         local_clips_stack[j].a,
                                                         local_clips_stack[j].light});
                        }
                    }
                    stack_size = local_clips_stack.size();
                    for (uint32_t j = 0; j < stack_size; j++) {
                        clipped_tri.setVertex(0, local_clips_stack[j].v1);
                        clipped_tri.setVertex(1, local_clips_stack[j].v2);
                        clipped_tri.setVertex(2, local_clips_stack[j].v3);
                        n_clipped_triangles = Math::triangle2DClipAgainstEdge(m_projection_data[i].v2,
                                                                              m_projection_data[i].v3,
                                                                              clipped_tri,
                                                                              out_tri_1,
                                                                              out_tri_2,
                                                                              out_tri_3);

                        if (n_clipped_triangles > 0) {
                            local_clips_stack.push_back({out_tri_1.getVertex(0),
                                                         out_tri_1.getVertex(1),
                                                         out_tri_1.getVertex(2),
                                                         local_clips_stack[j].r,
                                                         local_clips_stack[j].g,
                                                         local_clips_stack[j].b,
                                                         local_clips_stack[j].a,
                                                         local_clips_stack[j].light});
                        }
                        if (n_clipped_triangles > 1) {
                            local_clips_stack.push_back({out_tri_2.getVertex(0),
                                                         out_tri_2.getVertex(1),
                                                         out_tri_2.getVertex(2),
                                                         local_clips_stack[j].r,
                                                         local_clips_stack[j].g,
                                                         local_clips_stack[j].b,
                                                         local_clips_stack[j].a,
                                                         local_clips_stack[j].light});
                        }
                        if (n_clipped_triangles > 2) {
                            local_clips_stack.push_back({out_tri_3.getVertex(0),
                                                         out_tri_3.getVertex(1),
                                                         out_tri_3.getVertex(2),
                                                         local_clips_stack[j].r,
                                                         local_clips_stack[j].g,
                                                         local_clips_stack[j].b,
                                                         local_clips_stack[j].a,
                                                         local_clips_stack[j].light});
                        }
                    }
                    if (!local_clips_stack.empty()) {
                        m_projection_data.insert(m_projection_data.end(), local_clips_stack.begin(),
                                                 local_clips_stack.end());
                        local_clips_stack.clear();
                        m_projection_data.erase(m_projection_data.begin() + j);
                    }
                }

            }
#endif

            sort(m_projection_data.begin(), m_projection_data.end(),
                 [](const AbstractProjector::ProjectionData &a, const AbstractProjector::ProjectionData &b) {
                     /* https://en.wikipedia.org/wiki/Painter%27s_algorithm */
                     float za = (a.v1.z() + a.v2.z() + a.v3.z()) / 3;
                     float zb = (b.v1.z() + b.v2.z() + b.v3.z()) / 3;
                     return za > zb;
                 });

            return m_projection_data;
        }

        /**
         * @brief Deletes projection performed during last frame. This is obligatory to run after frame end. Without it old projections stays in the memory and gets drawn each frame which results in overflowing the stack.
         */
        inline void clearProjections() {
            m_projection_data.clear();
        }

        /**
         * @brief Set according on what window size calculations will be made.
         *
         * @param p_width The width of the window.
         * @param p_height The height of the window.
         */
        inline void resize(uint16_t p_width, uint16_t p_height) {
            m_width = p_width;
            m_height = p_height;
            m_aspect_ratio = (float) p_height / (float) p_width;
        }

    protected:
        float m_aspect_ratio{0}; /** !< The aspect ratio of the projector. */
        uint16_t m_width{0}; /** !< The width of the projector. */
        uint16_t m_height{0}; /** !< The height of the projector. */

        std::vector<ProjectionData_t> m_projection_data; /** !< The data of the projection. Holds all projections made in current frame */

        Matrix4x4f m_projection_matrix; /** !< The projection matrix. */
        Matrix4x4f m_view_matrix; /** !< The view matrix. */
        Matrix4x4f m_translation_matrix; /** !< The translation matrix. */

        Vector3 m_light_direction; /** !< The direction of the light source. */
    };

}

#endif /* CRUSTENGINE_ABSTRACTPROJECTOR_H */
