#ifndef CRUSTENGINE_MATERIAL_H
#define CRUSTENGINE_MATERIAL_H

#include <cstdint>

namespace Crust {
    /**
     * @brief Color struct represents a color in RGBA format.
     */
    typedef struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    } Color;

    /**
     * @brief Material class represents a material that can be applied to an object.
     */
    class Material {
    public:
        /**
         * @brief Construct a new Material object. Default color is black.
         */
        Material() = default;

        /**
         * @brief Construct a new Material object with specified diffuse color.
         *
         * @param p_diffuse
         */
        Material(Color p_diffuse) : m_diffuse(p_diffuse) {}

        /**
         * @brief Destroy the Material object.
         */
        ~Material() = default;

        /**
         * @brief Get the diffuse color of the material.
         *
         * @return Color
         */
        [[nodiscard]] Color getDiffuse() const {
            return m_diffuse;
        }

        /**
         * @brief Set the diffuse color of the material.
         *
         * @param p_diffuse
         */
        void setDiffuse(Color p_diffuse) {
            m_diffuse = p_diffuse;
        }

    private:
        Color m_diffuse;

    };
}

#endif /*CRUSTENGINE_MATERIAL_H */
