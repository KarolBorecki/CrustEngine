#include "core/Core.h"

namespace Crust {
    Core::Core() {
        Logger::info("Crust core initialized.");
    }

    Core::~Core() {
        closeAllWindows();
    }

    Window& Core::openWindow(uint16_t p_width, uint16_t p_height) {
        auto* w = new Window(p_width, p_height);
        m_windows.push_back(w);
        w->open();

        return *w;
    }

    Status Core::closeAllWindows() {
        for (auto w : m_windows) {
            if (w == nullptr) {
                return ERROR;
            }

            w->close();
            delete w;
        }
        m_windows.clear();
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