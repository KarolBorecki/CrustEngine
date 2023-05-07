#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include <Math/Vector3.hpp>

/**
 * @brief This class represents transform of an object. Holds position, rotation and scale of an object. Default values are 0, 0, 0 for position and rotation and 1, 1, 1 for scale.
 */
class Transform
{
public:
    Transform() = default;
    ~Transform() = default;

    /**
     * @brief Getter for #pos field.
     *
     * @return Vector3<>& Position of the object with this transform attached.
     */
    Vector3<> &GetPosition();

    /**
     * @brief Getter for #scale field;
     *
     * @return Vector3<>& Scale of the object with this transform attached.
     */
    Vector3<> &GetScale();

    /**
     * @brief Getter for #rot field, this returns handler to euler's vector for rotation.
     *
     * @return Vector3<>& Euler's rotation of the object with this transform attached.
     */
    Vector3<> &GetEulerRotation();

    /**
     * @brief Set the position of this object to given vector (x, y, z).
     */
    void SetPosition(float x, float y, float z);

    /**
     * @brief Set the scale of this object to given vector (x, y, z).
     */
    void SetScale(float x, float y, float z);

    /**
     * @brief Set the euler's rotation of this object to given vector (x, y, z) in degrees.
     */
    void SetEulerRotation(float x, float y, float z);

    /**
     * @brief Moves object by given values.
     *
     * @details Adds dX, dY and dZ to adequate values of #pos vector values.
     */
    void Translate(float dX, float dY, float dZ);

    /**
     * @brief Scales object by given values.
     *
     * @param dX delta X of which the scale of the object will be increased.
     * @param dY delta Y of which the scale of the object will be increased.
     * @param dZ delta Z of which the scale of the object will be increased.
     */
    void Scale(float dX, float dY, float dZ);

    /**
     * @brief Rotates object by given values.
     *
     * @details Adds dX, dY and dZ to adequate values of #rot vector values.
     */
    void RotateEuler(float dX, float dY, float dZ);

    static Vector3<> &Up() { return _upVector; }

private:
    Vector3<> p_pos{0.0f};   //!< Object's position in 3D space.
    Vector3<> p_scale{1.0f}; //!< Object's scale in 3D space.
    Vector3<> p_rot{0.0f};   //!< Object's Euler roatation in 3D space. //TODO implement Quaternions, this value should be from 0 to 1
    //TODO trzymanie wartości nie jest głupie jeśli Vector3 = 3 * float = 24 bity < 64 bitowa referencja
    static inline Vector3<> _upVector{0, 1, 0}; //!< Object's up vector in 3D space. Represents the direction of the top of the object.
};

inline Vector3<> &Transform::GetPosition()  { return p_pos; }

inline Vector3<> &Transform::GetScale()  { return p_scale; }

inline Vector3<> &Transform::GetEulerRotation()  { return p_rot; }

inline void Transform::SetPosition(float x, float y, float z) { p_pos = {x, y, z}; }

inline void Transform::SetScale(float x, float y, float z) { p_scale = {x, y, z}; }

inline void Transform::SetEulerRotation(float x, float y, float z) { p_rot = {x, y, z}; }

inline void Transform::Translate(float dX, float dY, float dZ) { p_pos += {dX, dY, dZ}; }

inline void Transform::Scale(float dX, float dY, float dZ) { p_scale += {dX, dY, dZ}; }

inline void Transform::RotateEuler(float dX, float dY, float dZ) { p_rot += {dX, dY, dZ}; }

#endif /* _TRANSFORM_HPP_ */