#ifndef CRUSTENGINE_OBJECT_TRANSFORM_H
#define CRUSTENGINE_OBJECT_TRANSFORM_H

#include "objects/transforms/Transform.h"
#include "math/Vector3.h"
#include "math/Matrix.h"

namespace Crust {
    /**
     * @brief The transform of an object. Handles position, rotation and scale.
     */
    class ObjectTransform : public Transform {
    public:
        /**
         * @brief Construct a new Transform object with default values.
         */
        ObjectTransform();

        Matrix4x4f &transformMatrix() override;

    private:
        Matrix4x4f m_transform_mat;
        Matrix4x4f m_translation_mat;
        Matrix4x4f m_scale_mat;
        Matrix4x4f m_rotation_x_mat;
        Matrix4x4f m_rotation_y_mat;
        Matrix4x4f m_rotation_z_mat;

        void recalculateTransformMatrix() override;

        void recalculateTranslationMatrix() override;

        void recalculateScaleMatrix() override;

        void recalculateRotationMatrix() override;
    };
}

#endif /* CRUSTENGINE_OBJECT_TRANSFORM_H */
