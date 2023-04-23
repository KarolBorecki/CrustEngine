#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include <Math/Vector3.hpp>

//TODO use float in position and rotation vectors
//TODO add docs
class Transform
{
public:
    /**
     * @brief Construct a new transform object with position at (0,0,0) and rotation at (0,0,0). Allocates space for position and rotation vectors.
     */
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
    Vector3 &GetEulerRotation() const;

    /**
     * @brief Set the position of this object to given vector (x, y, z).
     */
    void SetPosition(double x, double y, double z);

    /**
     * @brief Set the euler's rotation of this object to given vector (x, y, z) in degrees.
     */
    void SetEulerRotation(double x, double y, double z);

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
    void RotateEuler(double dX, double dY, double dZ);

private:
    Vector3 *pos{nullptr}; //!< Object's position in 3D space.
    Vector3 *rot{nullptr}; //!< Object's Euler roatation in 3D space. //TODO implement Quaternions
};

inline Transform::Transform()
{
    pos = new Vector3();
    rot = new Vector3();
}

inline Transform::~Transform()
{
    delete pos;
    delete rot;
}

inline Vector3 &Transform::GetPosition() const { return *pos; }

inline Vector3 &Transform::GetEulerRotation() const { return *rot; }

inline void Transform::SetPosition(double x, double y, double z) { (*pos) = {x, y, z}; }

inline void Transform::SetEulerRotation(double x, double y, double z) { (*rot) = {x, y, z}; }

inline void Transform::Translate(double dX, double dY, double dZ) { (*pos) += {dX, dY, dZ}; }

inline void Transform::RotateEuler(double dX, double dY, double dZ) { (*rot) += {dX, dY, dZ}; }

#endif /* _TRANSFORM_HPP_ */