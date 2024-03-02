#include "objects/Camera.h"

namespace Crust {
    Camera::Camera(int p_f_fov_deg, double p_f_near, double p_f_far) : m_f_fov_deg(p_f_fov_deg), m_fNear(p_f_near), m_f_far(p_f_far) {
        if (p_f_near <= 0 || p_f_far <= 0 || p_f_near >= p_f_far)
            Crust::ExceptionsHandler::throwError("Wrong input data for Camera!");

        double f_fov_converted = Crust::Math::degreesToRadians(p_f_fov_deg);
        if (Crust::Math::equal(f_fov_converted, 0))
            Crust::ExceptionsHandler::throwError("_fFovDeg cannot be equal to 0 in radians!");

        m_f_fov_rad = (1.0 / Math::tan(f_fov_converted * 0.5));
        Logger::info("Camera created with fFovDeg: %d, fNear: %f, fFar: %f", p_f_fov_deg, p_f_near, p_f_far);
    }

    int Camera::getFFovDeg() {
        return m_f_fov_deg;
    }

    double Camera::getFNear() {
        return m_fNear;
    }

    double Camera::getFFar() {
        return m_f_far;
    }

    double Camera::getFFovRad() {
        return m_f_fov_rad;
    }
}