#include "objects/Camera.h"

namespace Crust {
    Camera::Camera(uint16_t p_f_fov_deg, float p_f_near, float p_f_far) : m_f_fov_deg(p_f_fov_deg), m_fNear(p_f_near), m_f_far(p_f_far) {
        if (p_f_near <= 0 || p_f_far <= 0 || p_f_near >= p_f_far)
            Crust::ExceptionsHandler::throwError("Wrong input data for Camera!");

        double f_fov_converted = Crust::Math::degreesToRadians(p_f_fov_deg);
        if (Crust::Math::equal(f_fov_converted, 0))
            Crust::ExceptionsHandler::throwError("_fFovDeg cannot be equal to 0 in radians!");

        m_f_fov_rad = (1.0 / Math::tan(f_fov_converted * 0.5));
        Logger::info("Camera created with fFovDeg: %d, fNear: %f, fFar: %f", p_f_fov_deg, p_f_near, p_f_far);
    }

    uint16_t Camera::getFFovDeg() const {
        return m_f_fov_deg;
    }

    float Camera::getFNear() const {
        return m_fNear;
    }

    float Camera::getFFar() const {
        return m_f_far;
    }

    float Camera::getFFovRad() const{
        return m_f_fov_rad;
    }
}