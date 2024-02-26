#ifndef CRUSTENGINE_PROJECTOR_H
#define CRUSTENGINE_PROJECTOR_H

#include <cstdint>

namespace Crust {

    /**
     * @brief A projector class. Based on this class projection calculation will be done.
     *        It wrapps mathematical model of the engine.
     */
    class Projector {
    public:
        /**
         * @brief Construct a new Projector object with the specified width and height.
         *
         * @param p_width The width of the projector.
         * @param p_height The height of the projector.
         */
        Projector(uint16_t  p_width, uint16_t p_height);

        /**
         * @brief Destroy the Projector object.
         */
        virtual ~Projector() = default;

    private:
        uint16_t m_width { 0 }; /** !< The width of the projector. */
        uint16_t m_height { 0 }; /** !< The height of the projector. */
    };
}

#endif /* CRUSTENGINE_PROJECTOR_H */
