#ifndef CRUSTENGINE_TRANSFORM_H
#define CRUSTENGINE_TRANSFORM_H

#include "math/Math.h"
#include "math/Matrix.h"
#include "math/Vector3.h"

namespace Crust {
    /**
     * @brief The transform of an object. Handles position, rotation and scale.
     */
    class Transform {
    public:
        /**
         * @brief Construct a new Transform object with default values.
         */
        Transform();

        virtual ~Transform() = default;

        /**
         * @brief Getter for #pos field.
         *
         * @return Vector3& Position of the object with this transform attached.
         */
        virtual Crust::Vector3 &position();

        /**
         * @brief Getter for #scale field;
         *
         * @return Vector3& Scale of the object with this transform attached.
         */
        virtual Crust::Vector3 &size();

        /**
         * @brief Getter for #rot field, this returns handler to euler's vector for rotation.
         *
         * @return Vector3& Euler's rotation of the object with this transform attached.
         */
        virtual Crust::Vector3 &eulerRotation();

        /**
         * @brief Set the position of this object to given vector (x, y, z).
         */
        virtual void setPosition(double x, double y, double z);

        /**
         * @brief Set the scale of this object to given vector (x, y, z).
         */
        virtual void setSize(double x, double y, double z);

        /**
         * @brief Set the euler's rotation of this object to given vector (x, y, z) in degrees.
         */
        virtual void setEulerRotation(double x, double y, double z);

        /**
         * @brief Moves object by given values.
         *
         * @details Adds dX, dY and dZ to adequate values of #pos vector values.
         */
        virtual void translate(double dX, double dY, double dZ);

        /**
         * @brief Scales object by given values.
         *
         * @param dX delta X of which the scale of the object will be increased.
         * @param dY delta Y of which the scale of the object will be increased.
         * @param dZ delta Z of which the scale of the object will be increased.
         */
        virtual void scale(double dX, double dY, double dZ);

        /**
         * @brief Rotates object by given values.
         *
         * @details Adds dX, dY and dZ to adequate values of #rot vector values.
         */
        virtual void rotateEuler(double dX, double dY, double dZ);

        virtual Matrix4x4f &transformMatrix() = 0;

    protected:
        Vector3 m_position;
        Vector3 m_rotation;
        Vector3 m_scale;

        virtual void recalculateTransformMatrix() {};

        virtual void recalculateTranslationMatrix() {};

        virtual void recalculateScaleMatrix() {};

        virtual void recalculateRotationMatrix() {};
    };
}

#endif /* CRUSTENGINE_TRANSFORM_H */
