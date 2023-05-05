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
    Vector3<> &GetPosition() const;

    /**
     * @brief Getter for #rot field, this returns handler to euler's vector for rotation.
     *
     * @return #rot field.
     */
    Vector3<> &GetEulerRotation() const;

    /**
     * @brief Set the position of this object to given vector (x, y, z).
     */
    void SetPosition(float x, float y, float z);

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
     * @brief Rotates object by given values.
     *
     * @details Adds dX, dY and dZ to adequate values of #rot vector values.
     */
    void RotateEuler(float dX, float dY, float dZ);

    static Vector3<>& Up() { return _upVector; }

private:
    Vector3<> *p_pos{nullptr}; //!< Object's position in 3D space.
    Vector3<> *p_rot{nullptr}; //!< Object's Euler roatation in 3D space. //TODO implement Quaternions, this value should be from 0 to 1
    
    static inline Vector3<> _upVector{0,1,0}; //!< Object's up vector in 3D space. Represents the direction of the top of the object.
};

inline Transform::Transform()
{
    p_pos = new Vector3();
    p_rot = new Vector3();
}

inline Transform::~Transform()
{
    delete p_pos;
    delete p_rot;
}

inline Vector3<> &Transform::GetPosition() const { return *p_pos; }

inline Vector3<> &Transform::GetEulerRotation() const { return *p_rot; }

inline void Transform::SetPosition(float x, float y, float z) { (*p_pos) = {x, y, z}; }

inline void Transform::SetEulerRotation(float x, float y, float z) { (*p_rot) = {x, y, z}; }

inline void Transform::Translate(float dX, float dY, float dZ) { (*p_pos) += {dX, dY, dZ}; }

inline void Transform::RotateEuler(float dX, float dY, float dZ) { (*p_rot) += {dX, dY, dZ}; } 

#endif /* _TRANSFORM_HPP_ */