#ifndef CRUSTENGINE_CAMERA_H
#define CRUSTENGINE_CAMERA_H

#include <cstdint>

#include "logging/Logger.h"
#include "logging/ExceptionsHandler.h"
#include "math/Math.h"
#include "Object.h"

namespace Crust {
    /**
     * @brief Class representing the camera on a scene from which's perespective the renderer can render Mesh.
     */
    class Camera : public Object {
    public:
        /**
         * @details Also calculates the fFovRad for given input.
         *
         * @param _fFovDeg Field of view in degress.
         * @param _fNear fNear.
         * @param _fFar fFar.
         */
        Camera(uint16_t p_f_fov_deg, float p_f_near, float p_f_far);

        virtual ~Camera() = default;

        /**
         * @brief Getter for #fieldOfViewDeg field.
         *
         * @return Value of #fieldOfViewDeg.
         */
        uint16_t getFFovDeg() const;

        /**
         * @brief Getter for #fNear field.
         *
         * @return Value of #fNear.
         */
        float getFNear() const;

        /**
         * @brief Getter for #fFar field.
         *
         * @return Value of #fFar.
         */
        float getFFar() const;

        /**
         * @brief Getter for #fFovRad field.
         *
         * @return Value of #fFovRad.
         */
        float getFFovRad() const;

    private:
        uint16_t m_f_fov_deg { 0 }; //!< Represents the field of view of the camera as the angle value in degrees.
        float m_fNear { 0.0 }; //!< Represents the distance between the virtual eye and the rendered plane.
        float m_f_far { 0.0 }; //!< Represents the maximum depth of the viewed image.
        float m_f_fov_rad { 0.0 }; //!< Represents the field of view in radians.
    };

}

#endif /* CRUSTENGINE_CAMERA_H */
