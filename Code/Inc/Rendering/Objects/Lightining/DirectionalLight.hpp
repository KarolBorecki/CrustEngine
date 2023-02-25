#ifndef _DURECTIONALLIGHT_HPP_
#define _DURECTIONALLIGHT_HPP_

#include <Rendering/Objects/Lightining/LightSource.hpp>

#include <Physics/Vector3.hpp>

/**
 * @brief Object on the scene representing basic directional light source. It represents parraller light rays.
 */
class DirectionalLight : public LightSource
{
public:
    DirectionalLight(double _intensivity, Vector3 *_direction);

    std::string GetObjectTypeName() override;

private:
};

inline DirectionalLight::DirectionalLight(double _intensivity, Vector3 *_dir) : LightSource(_intensivity, _dir) {}

inline std::string DirectionalLight::GetObjectTypeName() { return "Directional Light Source"; }

#endif /* _DURECTIONALLIGHT_HPP_ */
