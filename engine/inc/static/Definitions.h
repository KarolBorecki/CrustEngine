#ifndef CRUSTENGINE_DEFINITIONS_H
#define CRUSTENGINE_DEFINITIONS_H

#include <cstdint>

namespace Crust {
    enum Status : uint8_t {
        OK = 0,
        NOT_SUPPORTED = 1,
        FILE_NOT_FOUND = 98,
        ERROR = 99,
    };

    enum Projection : uint8_t{
        PERSPECTIVE = 0,
//        ORTHOGRAPHIC = 1 // not implemented
    };

    enum LightType : uint8_t {
        DIRECTIONAL = 0,
//        POINT = 1, // not implemented
//        SPOT = 2 // not implemented
    };

    enum LightIntensity : uint8_t {
        INTENSIVITY_DARK = 0,
        INTENSIVITY_LOW = 64,
        INTENSIVITY_MEDIUM = 128,
        INTENSIVITY_BRIGHT = 192,
        INTENSIVITY_HIGH = 232,
        INTENSIVITY_MAX = 255
    };
}


#endif /* CRUSTENGINE_DEFINITIONS_H */
