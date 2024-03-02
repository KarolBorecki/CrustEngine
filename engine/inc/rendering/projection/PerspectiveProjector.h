#ifndef CRUSTENGINE_PERSPECTIVEPROJECTOR_H
#define CRUSTENGINE_PERSPECTIVEPROJECTOR_H

#include <cstdint>
#include "rendering/projection/AbstractProjector.h"

namespace Crust {

    /**
     * @brief A perspective projector class. It is responsible for projecting the scene based on the perspective projection model.
     */
    class PerspectiveProjector : public AbstractProjector {
    public:
        /**
         * @brief Construct a new Projector object with the specified width and height.
         *
         * @param p_width The width of the projector.
         * @param p_height The height of the projector.
         */
        PerspectiveProjector(uint16_t  p_width, uint16_t p_height) : AbstractProjector(p_width, p_height) { }
    };
}

#endif /* CRUSTENGINE_PERSPECTIVEPROJECTOR_H */
