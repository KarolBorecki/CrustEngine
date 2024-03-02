#include "core/Core.h"

namespace Crust {
    Core::Core() {
        Logger::info("Crust core initialized.");
        TimeProvider::onEngineStart();
    }

    Core::~Core() {
        closeAllWindows();
    }

    Status Core::openWindow(uint16_t p_width, uint16_t p_height) {
        if (p_width == 0 || p_height == 0)
            ExceptionsHandler::throwError("Error while opening new window: Width or Height cannot be equal to 0!");

        Window* window = new Window(p_width, p_height);
        m_windows.push_back(window);
        window->open();

        return OK;
    }

    Window* Core::getWindow(uint16_t p_index) const {
        if (p_index >= m_windows.size()) {
            return nullptr;
        }
        return m_windows[p_index];
    }

    Status Core::closeAllWindows() {
        for (auto window : m_windows) {
            if (window == nullptr) {
                return ERROR;
            }
            window->close();
            delete window;
        }
        m_windows.clear();
        Logger::info("Windows cleared.");
        return OK;
    }

    Status Core::quit() {
        Logger::info("Quitting the crust engine.");
        return closeAllWindows();
    }

    std::vector<Window*> Core::getWindows() const {
        return m_windows;
    }
}