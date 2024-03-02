#include "objects/LightSource.h"

namespace Crust {
    LightSource::LightSource(LightType p_type, LightIntensity p_intensity) : Object(), m_type(p_type), m_intensity(p_intensity) {

    }

    void LightSource::setType(LightType p_type) {
        m_type = p_type;
    }

    LightType LightSource::getType() const {
        return m_type;
    }

    void LightSource::setIntensity(LightIntensity p_intensity) {
        m_intensity = p_intensity;
    }

    LightIntensity LightSource::getIntensity() const {
        return m_intensity;
    }
}