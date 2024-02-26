#ifndef CRUSTENGINE_DEFINITIONS_H
#define CRUSTENGINE_DEFINITIONS_H


namespace Crust {
    enum Status {
        OK = 0,
        ERROR = 99,
    };

    enum LightType {
        DIRECTIONAL = 0,
        POINT = 1, // TODO not implemented
        SPOT = 2 // TODO not implemented
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
