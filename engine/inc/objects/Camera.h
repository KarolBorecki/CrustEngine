#ifndef CRUSTENGINE_CAMERA_H
#define CRUSTENGINE_CAMERA_H

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
        Camera(int p_f_fov_deg, double p_f_near, double p_f_far);

        virtual ~Camera() = default;

        /**
         * @brief Getter for #fieldOfViewDeg field.
         *
         * @return Value of #fieldOfViewDeg.
         */
        int getFFovDeg();

        /**
         * @brief Getter for #fNear field.
         *
         * @return Value of #fNear.
         */
        double getFNear();

        /**
         * @brief Getter for #fFar field.
         *
         * @return Value of #fFar.
         */
        double getFFar();

        /**
         * @brief Getter for #fFovRad field.
         *
         * @return Value of #fFovRad.
         */
        double getFFovRad();

    private:
        int m_f_fov_deg { 0 };      //!< Represents the field of view of the camera as the angle value in degrees.
        double m_fNear { 0.0 };   //!< Represents the distance between the virtual eye and the rendered plane.
        double m_f_far { 0.0 };    //!< Represents the maximum depth of the viewed image.
        double m_f_fov_rad { 0.0 }; //!< Represents the field of view in radians.
    };

}

#endif /* CRUSTENGINE_CAMERA_H */
