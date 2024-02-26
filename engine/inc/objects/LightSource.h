#ifndef CRUSTENGINE_LIGHTSOURCE_H
#define CRUSTENGINE_LIGHTSOURCE_H

#include <cstdint>

#include "Object.h"
#include "static/Definitions.h"

namespace Crust {
    /**
     * @brief A light source base class. Based on this class no calculation will be done. Please use derived classes.
     */
    class LightSource : public Object {
    public:
        /**
         * @brief Construct a new LightSource object with default type set to #DIRECTIONAL and intensity set to #INTENSIVITY_BRIGHT.
         */
        LightSource() : Object() {};

        /**
         * @brief Construct a new LightSource object with intensity set to #p_intensity.
         *
         * @param p_type Type of the light source.
         * @param p_intensity Intensity of the light source.
         */
        LightSource(uint8_t p_type, uint8_t p_intensity);

        /**
         * @brief Destroy the LightSource object.
         */
        virtual ~LightSource() = default;

        /**
         * @brief Set the type of the light source.
         *
         * @param p_type Type of the light source.
         */
        void setType(uint8_t p_type);

        /**
         * @brief Get the type of the light source.
         *
         * @return Type of the light source.
         */
        uint8_t getType() const;

        /**
         * @brief Set the intensity of the light source.
         *
         * @param p_intensity Intensity of the light source.
         */
        void setIntensity(uint8_t p_intensity);

        /**
         * @brief Get the intensity of the light source.
         *
         * @return Intensity of the light source.
         */
        uint8_t getIntensity() const;

    private:
        uint8_t m_type { LightType::DIRECTIONAL }; /**< Type of the light source. */
        uint8_t m_intensity { LightIntensity::INTENSIVITY_BRIGHT }; /**< Intensity of the light source. */
    };
}

#endif /* CRUSTENGINE_LIGHTSOURCE_H */
