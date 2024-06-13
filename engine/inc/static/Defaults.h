#ifndef CRUSTENGINE_DEFAULTS_H
#define CRUSTENGINE_DEFAULTS_H

#include "static/Config.h"
#include "static/Definitions.h"

namespace Crust {
    static const char *DEFAULT_MESH_NAME = "NO NAME";
    static const char *DEFAULT_SCENE_NAME = "Scene";

    static const uint8_t DEFAULT_PROJECTOR = Projection::PERSPECTIVE;

    static const uint8_t DEFAULT_LIGHT_TYPE = LightType::DIRECTIONAL;
    static const float DEFAULT_LIGHT_INTENSITY = 0.85f;

    static const float DEFAULT_SCENE_AMBIENT_LIGHT = 0.1f;
}

#endif /* CRUSTENGINE_DEFAULTS_H */
