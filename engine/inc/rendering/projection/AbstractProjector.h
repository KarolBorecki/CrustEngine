#ifndef CRUSTENGINE_ABSTRACTPROJECTOR_H
#define CRUSTENGINE_ABSTRACTPROJECTOR_H

#include <cstdint>

namespace Crust {
    /**
     * @brief A projector base class. Defines basic operations that can be implemented based on different projection models.
     */
    class AbstractProjector {
    public:
        /**
         * @brief Construct a new Projector object with the specified width and height.
         *
         * @param p_width The width of the projector.
         * @param p_height The height of the projector.
         */
        AbstractProjector(uint16_t p_width, uint16_t p_height) : m_width(p_width), m_height(p_height) {}

        /**
         * @brief Destroy the Projector object.
         */
        virtual ~AbstractProjector() = default;

    private:
        uint16_t m_width { 0 }; /** !< The width of the projector. */
        uint16_t m_height { 0 }; /** !< The height of the projector. */
    };

}

#endif /* CRUSTENGINE_ABSTRACTPROJECTOR_H */
