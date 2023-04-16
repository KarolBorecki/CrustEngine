#ifndef _LIGHTSOURCE_HPP_
#define _LIGHTSOURCE_HPP_

#include <Rendering/Objects/Object.hpp>

/**
 * @brief Virtual class for light sources.
 */
class LightSource : public Object
{
public:
  /**
   * @param _intensivity Light's intensivity.
   */
  LightSource(double _intensivity);

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

protected:
  uint8_t intesivity{255}; //!< Light's intensivity. Value between 0 and 255, where 255 represent the brightest light.
};

inline LightSource::LightSource(double _intensivity) : intesivity(_intensivity), Object() {}

inline uint8_t LightSource::GetIntensivity() { return intesivity; }

inline double LightSource::GetNormalisedIntensivity() { return intesivity / 255; }

#endif /* _LIGHTSOURCE_HPP_ */
