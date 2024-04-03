#ifndef CRUSTENGINE_ABSTRACTPROJECTOR_H
#define CRUSTENGINE_ABSTRACTPROJECTOR_H

#include <cstdint>
#include "objects/Camera.h"
#include "objects/LightSource.h"
#include "objects/RenderObject.h"
#include "math/Matrix.h"
#include "math/Vector3.h"
#include "math/Vector4.h"

namespace Crust {
    /**
     * @brief A projector base class. Defines basic operations that can be implemented based on different projection models.
     */
    class AbstractProjector {
    public:
        typedef struct ProjectionData
        {
            float x1 = 0, y1 = 0, z1 = 0;
            float x2 = 0, y2 = 0, z2 = 0;
            float x3 = 0, y3 = 0, z3 = 0;
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

        virtual void setupCamera(Camera& camera) = 0; // TODO add documentation
        virtual void setupLightning(LightSource& p_light) = 0; // TODO handle multiple lights

        virtual void project(RenderObject& p_object) = 0;

        /**
         * @brief Retrieve the projection data, which is the data of the projections made in the current frame.
         *
         * @return std::vector<ProjectionData_t> The projection data.
         */
        inline std::vector<ProjectionData_t> retrievProjections() {
            sort(m_projection_data.begin(), m_projection_data.end(), [](const AbstractProjector::ProjectionData &a, const AbstractProjector::ProjectionData &b)
            {
                /* https://en.wikipedia.org/wiki/Painter%27s_algorithm */
                float za = (a.z1 + a.z2 + a.z3) / 3;
                float zb = (b.z1 + b.z2 + b.z3) / 3;
                return za > zb;
            });

            return m_projection_data;
        }

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
            m_aspect_ratio = (float)p_height / (float)p_width;
        }

    protected:
        float m_aspect_ratio { 0 }; /** !< The aspect ratio of the projector. */
        uint16_t m_width { 0 }; /** !< The width of the projector. */
        uint16_t m_height { 0 }; /** !< The height of the projector. */

        std::vector<ProjectionData_t> m_projection_data; /** !< The data of the projection. Holds all projections made in current frame */

        Matrix4x4f m_projection_matrix; /** !< The projection matrix. */
        Matrix4x4f m_view_matrix; /** !< The view matrix. */
        Matrix4x4f m_translation_matrix; /** !< The translation matrix. */

        Vector3<> m_light_direction; /** !< The direction of the light source. */
    };

}

#endif /* CRUSTENGINE_ABSTRACTPROJECTOR_H */
