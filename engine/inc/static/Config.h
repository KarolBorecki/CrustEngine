#ifndef CRUSTENGINE_CONFIG_H
#define CRUSTENGINE_CONFIG_H

#include "static/Definitions.h"

namespace Crust {
    static const char* DEFAULT_MESH_NAME = "NO NAME";
    static const char* DEFAULT_SCENE_NAME = "Scene";

    static const uint8_t DEFAULT_PROJECTOR = Projection::PERSPECTIVE;

    static const uint8_t DEFAULT_LIGHT_TYPE = LightType::DIRECTIONAL;
    static const uint8_t DEFAULT_LIGHT_INTENSITY = LightIntensity::INTENSIVITY_BRIGHT;
}

#endif /* CRUSTENGINE_CONFIG_H */
