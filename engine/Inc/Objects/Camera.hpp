#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <Objects/Object.hpp>

#include <Math/Math.hpp>

namespace crust {
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
        Camera(int _fFovDeg, double _fNear, double _fFar);

        virtual ~Camera() = default;

        /**
         * @brief Getter for #fieldOfViewDeg field.
         *
         * @return Value of #fieldOfViewDeg.
         */
        int GetFFovDeg();

        /**
         * @brief Getter for #fNear field.
         *
         * @return Value of #fNear.
         */
        double GetFNear();

        /**
         * @brief Getter for #fFar field.
         *
         * @return Value of #fFar.
         */
        double GetFFar();

        /**
         * @brief Getter for #fFovRad field.
         *
         * @return Value of #fFovRad.
         */
        double GetFFovRad();

    private:
        int _fFovDeg{0};      //!< Represents the field of view of the camera as the angle value in degrees.
        double _fNear{0.0};   //!< Represents the distance between the virtual eye and the rendered plane.
        double _fFar{0.0};    //!< Represents the maximum depth of the viewed image.
        double _fFovRad{0.0}; //!< Represents the field of view in radians.
    };

    inline Camera::Camera(int fFovDeg, double fNear, double fFar) : _fFovDeg(fFovDeg), _fNear(fNear), _fFar(fFar) {
        if (_fNear <= 0 || _fFar <= 0 || _fNear >= _fFar)
            ExceptionsHandler::ThrowError("Wrong input data for Camera!");

        double fFovConverted = Math::DegreesToRadians(fFovDeg);
        if (Math::Equals(fFovConverted, 0))
            ExceptionsHandler::ThrowError("_fFovDeg cannot be equal to 0 in radians!");

        _fFovRad = (1.0 / Math::Tan(fFovConverted * 0.5));
    }

    inline int Camera::GetFFovDeg() { return _fFovDeg; }

    inline double Camera::GetFNear() { return _fNear; }

    inline double Camera::GetFFar() { return _fFar; }

    inline double Camera::GetFFovRad() { return _fFovRad; }
}

#endif /* _CAMERA_HPP_ */
