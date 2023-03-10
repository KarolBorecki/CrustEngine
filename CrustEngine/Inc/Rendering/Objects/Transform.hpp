#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include <Math/Vector3.hpp>

class Transform {
public:
    Transform();

    ~Transform();

    /**
     * @brief Getter for #pos field.
     *
     * @return #pos field.
     */
    Vector3 &GetPosition() const;

    /**
     * @brief Getter for #rot field, this returns handler to euler's vector for rotation.
     *
     * @return #rot field.
     */
    Vector3 &GetRotation() const;

    void SetPosition(double x, double y, double z);

    /**
     * @brief Moves object by given values.
     *
     * @details Adds dX, dY and dZ to adequate values of #pos vector values.
     */
    void Translate(double dX, double dY, double dZ);

    /**
     * @brief Rotates object by given values.
     *
     * @details Adds dX, dY and dZ to adequate values of #rot vector values.
     */
    void Rotate(double dX, double dY, double dZ);

private:
    Vector3 *pos { nullptr }; //!< Object's position in 3D space.
    Vector3 *rot { nullptr }; //!< Object's Euler roatation in 3D space. //TODO implement Quaternions
};

inline Transform::Transform() {
    pos = new Vector3();
    rot = new Vector3(); 
}

inline Transform::~Transform() {
    delete pos;
    delete rot;
}

inline Vector3& Transform::GetPosition() const { return *pos; }

inline Vector3 & Transform::GetRotation() const { return *rot; }

inline void Transform::SetPosition(double x, double y, double z) { (*pos) = {x, y, z}; }

inline void Transform::Translate(double dX, double dY, double dZ) { (*pos) += {dX, dY, dZ}; }

inline void Transform::Rotate(double dX, double dY, double dZ) { (*rot) += {dX, dY, dZ}; }

#endif /* _TRANSFORM_HPP_ */