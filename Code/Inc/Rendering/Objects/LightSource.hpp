#ifndef _LIGHTSOURCE_HPP_
#define _LIGHTSOURCE_HPP_

#include <Rendering/Objects/Object.hpp>
#include <Physics/Vector3.hpp>

/**
* @brief Object on the scene representing basic directional light source. It represents parraller light rays.
*/
class LightSource : public Object {
public:
  /**
  * @param _intensivity Light's intensivity.
  * @param _dir Light's direction.
  */
  LightSource(double _intensivity, Vector3* _dir);

  ~LightSource();

  std::string GetObjectTypeName() override;

  /**
  * @brief Getter for light's #intesivity field.
  */
  uint8_t GetIntensivity();
  /**
  * @brief Getter for light's normalised #intesivity field.
  *
  * @return Value of #intesivity divided by 255 (Normalised to value from 0.0 to 1.0).
  */
  double GetNormalisedIntensivity();

  /**
  * @brief Getter for light's #direction field.
  */
  Vector3* GetDirection();

private:
  Vector3* direction { nullptr }; //!< Lights direction in 3D space.
  uint8_t intesivity { 255 }; //!< Light's intensivity. Value between 0 and 255, where 255 represent brightest light.
};

inline LightSource::LightSource(double _intensivity, Vector3* _dir) : intesivity(_intensivity), direction(_dir) {}

inline LightSource::~LightSource() {}

inline std::string LightSource::GetObjectTypeName() { return "Directional Light Source"; }

inline uint8_t LightSource::GetIntensivity() { return intesivity; }

inline double LightSource::GetNormalisedIntensivity() { return intesivity / 255; }

inline Vector3* LightSource::GetDirection() { return direction; }

#endif /* _LIGHTSOURCE_HPP_ */
