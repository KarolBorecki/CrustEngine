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
        typedef struct ProjectionData {
            Vector3<> v1;
            Vector3<> v2;
            Vector3<> v3;
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
            sort(m_projection_data.begin(), m_projection_data.end(),
                 [](const AbstractProjector::ProjectionData &a, const AbstractProjector::ProjectionData &b) {
                     /* https://en.wikipedia.org/wiki/Painter%27s_algorithm */
                     float za = (a.v1.z() + a.v2.z() + a.v3.z()) / 3;
                     float zb = (b.v1.z() + b.v2.z() + b.v3.z()) / 3;
                     return za < zb;
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

        Vector3<> m_light_direction; /** !< The direction of the light source. */
    };

}

#endif /* CRUSTENGINE_ABSTRACTPROJECTOR_H */
