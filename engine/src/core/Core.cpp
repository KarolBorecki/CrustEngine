#include "core/Core.h"

namespace Crust {
    Core::Core() {
        TimeProvider::onEngineStart();
    }

    Core::~Core() {
        for (auto window : m_windows) {
            if (window != nullptr) {
                delete window;
            }
        }
    }

    Window* Core::openWindow(uint16_t p_width, uint16_t p_height) {
        if (p_width == 0 || p_height == 0)
            ExceptionsHandler::throwError("Error while opening new window: Width or Height cannot be equal to 0!");

        auto* window = new Window(p_width, p_height);
        m_windows.push_back(window);
        window->open();

        return window;
    }

    Window& Core::getWindow(uint16_t p_index) {
        if (p_index >= m_windows.size()) {
            ExceptionsHandler::throwError("Error while getting window: Index out of range!");
        }
        return *m_windows[p_index];
    }

    std::vector<Window*> Core::getWindows() const {
        return m_windows;
    }
}