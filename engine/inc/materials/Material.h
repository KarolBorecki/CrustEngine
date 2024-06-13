#ifndef CRUSTENGINE_MATERIAL_H
#define CRUSTENGINE_MATERIAL_H

#include <cstdint>

namespace Crust {
    /**
     * @brief Color struct represents a color in RGBA format.
     */
    typedef struct Color {
        float r;
        float g;
        float b;
        float a;
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
         * @brief Construct a new Material object with specified diffuse color, specular and shinees.
         *
         * @param p_diffuse
         * @param p_specular
         * @param p_shininess
         */
        Material(Color p_diffuse, Color p_specular, uint8_t p_shininess) : m_diffuse(p_diffuse),
                                                                           m_specular(p_specular),
                                                                           m_shininess(p_shininess) {}

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

        /**
         * @brief Get the shininess of the material.
         *
         * @return uint8_t
         */
        [[nodiscard]] uint8_t getShininess() const {
            return m_shininess;
        }

        /**
         * @brief Set the shininess of the material.
         *
         * @param p_shininess
         */
        void setShininess(uint8_t p_shininess) {
            m_shininess = p_shininess;
        }

        /**
         * @brief Get the specular color of the material.
         *
         * @return Color
         */
        [[nodiscard]] Color getSpecular() const {
            return m_specular;
        }

        /**
         * @brief Set the specular color of the material.
         *
         * @param p_specular
         */
        void setSpecular(Color p_specular) {
            m_specular = p_specular;
        }

    private:
        Color m_diffuse;
        Color m_specular;
        uint8_t m_shininess; /** !< 0 - 255, Wood: 10-20, Wall: 5-15, Metal: 60-100, Plastic: 10-30/40-80 */
    };
}

#endif /*CRUSTENGINE_MATERIAL_H */
