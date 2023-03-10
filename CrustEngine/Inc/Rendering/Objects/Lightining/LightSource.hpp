#ifndef _LIGHTSOURCE_HPP_
#define _LIGHTSOURCE_HPP_

#include <Rendering/Objects/Object.hpp>

/**
 * @brief Object on the scene representing basic directional light source. It represents parraller light rays.
 */
class LightSource : public Object
{
public:
  /**
   * @param _intensivity Light's intensivity.
   * @param _dir Light's direction.
   */
  LightSource(double _intensivity);

  virtual ~LightSource() = default;

  virtual std::string GetObjectTypeName() override;

  /**
   * @brief Getter for light's #intesivity field.
   */
  virtual uint8_t GetIntensivity();

  /**
   * @brief Getter for light's normalised #intesivity field.
   *
   * @return Value of #intesivity divided by 255 (Normalised to value from 0.0 to 1.0).
   */
  virtual double GetNormalisedIntensivity();

  /**
   * @brief Getter for light's #direction field.
   */
  Vector3 *GetDirection();

protected:
  LightSource(double _intensivity, Vector3 *_direction);

  uint8_t intesivity { 255 };     //!< Light's intensivity. Value between 0 and 255, where 255 represent brightest light.
  Vector3 *direction { nullptr }; //!< Lights direction in 3D space. // TODO move to directional ligth
};

inline LightSource::LightSource(double _intensivity) : intesivity(_intensivity) {}

inline LightSource::LightSource(double _intensivity, Vector3 *_direction) : intesivity(_intensivity), direction(_direction) {}

inline std::string LightSource::GetObjectTypeName() { return "Light Source"; }

inline uint8_t LightSource::GetIntensivity() { return intesivity; }

inline double LightSource::GetNormalisedIntensivity() { return intesivity / 255; }

inline Vector3 *LightSource::GetDirection() { return direction; }

#endif /* _LIGHTSOURCE_HPP_ */
