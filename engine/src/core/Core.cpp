#include "core/Core.h"

#include "core/Window.h"

namespace Crust {
    Core::~Core() {
        closeAllWindows();
    }

    Status Core::openWindow(uint16_t p_width, uint16_t p_height) {
        return ERROR;
    }

    Status Core::closeAllWindows() {
        return ERROR;
    }

    Status Core::quit() {
        return ERROR;
    }
}