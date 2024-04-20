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

        /**
         * @brief Set the position of this object to given vector (x, y, z).
         */
        void setPosition(float x, float y, float z) override;

        /**
         * @brief Set the scale of this object to given vector (x, y, z).
         */
        void setSize(float x, float y, float z) override;

        /**
         * @brief Set the euler's rotation of this object to given vector (x, y, z) in degrees.
         */
        void setEulerRotation(float x, float y, float z) override;

        /**
         * @brief Moves object by given values.
         *
         * @details Adds dX, dY and dZ to adequate values of #pos vector values.
         */
        void translate(float dX, float dY, float dZ) override;

        /**
         * @brief Scales object by given values.
         *
         * @param dX delta X of which the scale of the object will be increased.
         * @param dY delta Y of which the scale of the object will be increased.
         * @param dZ delta Z of which the scale of the object will be increased.
         */
        void scale(float dX, float dY, float dZ) override;

        /**
         * @brief Rotates object by given values.
         *
         * @details Adds dX, dY and dZ to adequate values of #rot vector values.
         */
        void rotateEuler(float dX, float dY, float dZ) override;

        Matrix4x4f &transformMatrix() override;

    private:
        Matrix4x4f m_transform_mat;
        Matrix4x4f m_translation_mat;
        Matrix4x4f m_scale_mat;
        Matrix4x4f m_rotation_x_mat;
        Matrix4x4f m_rotation_y_mat;
        Matrix4x4f m_rotation_z_mat;

        void recalculateTransformMatrix();

        void recalculateTranslationMatrix();

        void recalculateScaleMatrix();

        void recalculateRotationMatrix();
    };
}

#endif /* CRUSTENGINE_OBJECT_TRANSFORM_H */
