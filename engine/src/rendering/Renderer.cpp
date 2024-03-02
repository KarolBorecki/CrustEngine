#include "rendering/Renderer.h"

namespace Crust {
    Renderer::Renderer(uint16_t p_width, uint16_t p_height) : m_lib_2d(*(new Library2DWrapper(p_width, p_height))) {}

    void Renderer::renderScene(Scene &scene) {
        // TODO: Implement
    }
}
