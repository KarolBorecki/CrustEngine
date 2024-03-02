#ifndef CRUSTENGINE_LIGHTSOURCE_H
#define CRUSTENGINE_LIGHTSOURCE_H

#include <cstdint>

#include "Object.h"
#include "static/Definitions.h"
#include "static/Config.h"

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
        LightSource(LightType p_type, LightIntensity p_intensity);

        /**
         * @brief Destroy the LightSource object.
         */
        virtual ~LightSource() = default;

        /**
         * @brief Set the type of the light source.
         *
         * @param p_type Type of the light source.
         */
        void setType(LightType p_type);

        /**
         * @brief Get the type of the light source.
         *
         * @return Type of the light source.
         */
        LightType getType() const;

        /**
         * @brief Set the intensity of the light source.
         *
         * @param p_intensity Intensity of the light source.
         */
        void setIntensity(LightIntensity p_intensity);

        /**
         * @brief Get the intensity of the light source.
         *
         * @return Intensity of the light source.
         */
        LightIntensity getIntensity() const;

    private:
        LightType m_type { Crust::DEFAULT_LIGHT_TYPE }; /**< Type of the light source. */
        LightIntensity m_intensity { Crust::DEFAULT_LIGHT_INTENSITY }; /**< Intensity of the light source. */
    };
}

#endif /* CRUSTENGINE_LIGHTSOURCE_H */
