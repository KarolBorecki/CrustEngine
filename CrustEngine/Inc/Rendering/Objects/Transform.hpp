#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include <Math/Vector3.hpp>

// TODO use float in position and rotation vectors
// TODO add docs
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
     * @return Vector3<>& Position of the object with this transform attached.
     */
    Vector3<> &GetPosition() const;

    /**
     * @brief Getter for #scale field;
     *
     * @return Vector3<>& Scale of the object with this transform attached.
     */
    Vector3<> &GetScale() const;

    /**
     * @brief Getter for #rot field, this returns handler to euler's vector for rotation.
     *
     * @return Vector3<>& Euler's rotation of the object with this transform attached.
     */
    Vector3<> &GetEulerRotation() const;

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
    Vector3<> *p_pos{nullptr};   //!< Object's position in 3D space.
    Vector3<> *p_scale{nullptr}; //!< Object's scale in 3D space.
    Vector3<> *p_rot{nullptr};   //!< Object's Euler roatation in 3D space. //TODO implement Quaternions, this value should be from 0 to 1
    //TODO trzymanie wartości nie jest głupie jeśli Vector3 = 3 * float = 24 bity < 64 bitowa referencja
    static inline Vector3<> _upVector{0, 1, 0}; //!< Object's up vector in 3D space. Represents the direction of the top of the object.
};

inline Transform::Transform()
{
    p_pos = new Vector3(0.0f);
    p_scale = new Vector3(1.0f);
    p_rot = new Vector3(0.0f); 
}

inline Transform::~Transform()
{
    delete p_pos;
    delete p_scale;
    delete p_rot;
}

inline Vector3<> &Transform::GetPosition() const { return *p_pos; }

inline Vector3<> &Transform::GetScale() const { return *p_scale; }

inline Vector3<> &Transform::GetEulerRotation() const { return *p_rot; }

inline void Transform::SetPosition(float x, float y, float z) { (*p_pos) = {x, y, z}; }

inline void Transform::SetScale(float x, float y, float z) { (*p_scale) = {x, y, z}; }

inline void Transform::SetEulerRotation(float x, float y, float z) { (*p_rot) = {x, y, z}; }

inline void Transform::Translate(float dX, float dY, float dZ) { (*p_pos) += {dX, dY, dZ}; }

inline void Transform::Scale(float dX, float dY, float dZ) { (*p_scale) += {dX, dY, dZ}; }

inline void Transform::RotateEuler(float dX, float dY, float dZ) { (*p_rot) += {dX, dY, dZ}; }

#endif /* _TRANSFORM_HPP_ */