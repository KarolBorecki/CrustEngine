#ifndef CRUSTENGINE_CAMERA_TRANSFORM_H
#define CRUSTENGINE_CAMERA_TRANSFORM_H

#include "objects/transforms/Transform.h"
#include "math/Vector3.h"
#include "math/Matrix.h"

namespace Crust {
    /**
     * @brief The transform of a camera.
     */
    class CameraTransform : public Transform {
    public:
        /**
         * @brief Construct a new CameraTransform object with default values.
         */
        CameraTransform();

        Matrix4x4f &transformMatrix() override;

    protected:
        static inline Matrix1x4f WORLD_RIGHT = {1.0f, 0.0f, 0.0f, 1.0f};
        static inline Matrix1x4f WORLD_UP = {0.0f, 1.0f, 0.0f, 1.0f};
        static inline Matrix1x4f WORLD_FORWARD = {0.0f, 0.0f, 1.0f, 1.0f};

        Matrix4x4f m_transform_mat;

        void recalculateTransformMatrix() override;
    };
}

#endif /* CRUSTENGINE_CAMERA_TRANSFORM_H */
