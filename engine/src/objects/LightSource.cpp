#include "objects/LightSource.h"

namespace Crust {
    LightSource::LightSource(uint8_t p_type, uint8_t p_intensity) : Object(), m_type(p_type), m_intensity(p_intensity) {

    }

    void LightSource::setType(uint8_t p_type) {
        m_type = p_type;
    }

    uint8_t LightSource::getType() const {
        return m_type;
    }

    void LightSource::setIntensity(uint8_t p_intensity) {
        m_intensity = p_intensity;
    }

    uint8_t LightSource::getIntensity() const {
        return m_intensity;
    }
}