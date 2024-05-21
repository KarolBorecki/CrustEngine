#ifndef CRUSTENGINE_PERSPECTIVEPROJECTOR_H
#define CRUSTENGINE_PERSPECTIVEPROJECTOR_H

#include <cstdint>

#include "rendering/projection/AbstractProjector.h"
#include "objects/Camera.h"
#include "objects/LightSource.h"
#include "objects/RenderObject.h"
#include "math/Vector3.h"
#include "math/Vector4.h"

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
        PerspectiveProjector(uint16_t p_width, uint16_t p_height) : AbstractProjector(p_width, p_height) {}

        /**
         * @brief Destroy the Projector object.
         */
        ~PerspectiveProjector() override = default;

        void setupCamera(Camera &camera) override;

        void setupLightning(LightSource &p_light, uint8_t p_ambient_light) override;

        void project(RenderObject &p_object) override;
    };
}

#endif /* CRUSTENGINE_PERSPECTIVEPROJECTOR_H */
