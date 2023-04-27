#ifndef _DURECTIONALLIGHT_HPP_
#define _DURECTIONALLIGHT_HPP_

#include <Rendering/Objects/Lightining/LightSource.hpp>

#include <Math/Vector3.hpp>

/**
 * @brief Object on the scene representing basic directional light source. It represents parraller light rays.
 */
class DirectionalLight : public LightSource
{
public:
    /**
     * @param _intensivity Light's intensivity.
     * @param _dir Light's direction.
     */
    DirectionalLight(double _intensivity, Vector3<> &_direction);
};

inline DirectionalLight::DirectionalLight(double _intensivity, Vector3<> &_dir) : LightSource(_intensivity)
{
    p_transform->SetEulerRotation(_dir.X(), _dir.Y(), _dir.Z());
}

#endif /* _DURECTIONALLIGHT_HPP_ */
