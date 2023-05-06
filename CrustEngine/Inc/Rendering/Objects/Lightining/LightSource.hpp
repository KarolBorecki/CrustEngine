#ifndef _LIGHTSOURCE_HPP_
#define _LIGHTSOURCE_HPP_

#include <Rendering/Objects/Object.hpp>

/**
 * @brief Virtual class for light sources.
 */
class LightSource : public Object
{
public:
  enum LightIntensivity : uint8_t {
    INTENSIVITY_DARK = 0,
    INTENSIVITY_LOW = 64,
    INTENSIVITY_MEDIUM = 128,
    INTENSIVITY_BRIGHT = 192,
    INTENSIVITY_HIGH = 232,
    INTENSIVITY_MAX = 255
  };

public:
  /**
   * @param _intensivity Light's intensivity.
   */
  LightSource(uint8_t _intensivity);

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
  uint8_t _intesivity{INTENSIVITY_HIGH}; //!< Light's intensivity. Value between 0 and 255, where 255 represent the brightest light.
};

inline LightSource::LightSource(uint8_t _intensivity) : _intesivity(_intensivity), Object() {}

inline uint8_t LightSource::GetIntensivity() { return _intesivity; }

inline double LightSource::GetNormalisedIntensivity() { return _intesivity / INTENSIVITY_MAX; }

#endif /* _LIGHTSOURCE_HPP_ */
