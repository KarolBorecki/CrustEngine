#ifndef CRUSTENGINE_CORE_H
#define CRUSTENGINE_CORE_H

#include <vector>

#include "core/Window.h"
#include "logging/ExceptionsHandler.h"

namespace Crust {
    /**
     * @brief Core of the engine. It manages all of the windows and their events.
     */
    class Core {
    public:
        /**
         * @brief Construct a new Core object.
         */
        Core();

        /**
         * @brief Destroy the Core object. It also closes all of the windows and manages the cleanup of the leftovers.
         */
        ~Core();

        /**
         * @brief Opens a new window with specified width and height.
         *
         * @details It also adds the window to the list of managed windows. Also remember that when window is opened it runs it's own event loop
         *
         * @param p_width The width of the window.
         * @param p_height The height of the window.
         * @return Status::OK if window was opened successfully, Status::ERROR otherwise.
         */
        Status openWindow(uint16_t p_width, uint16_t p_height);

        /**
         * @brief Get the window with the specified index.
         *
         * @param p_index The index of the window.
         * @return The window with the specified index.
         */
        Window* getWindow(uint16_t p_index) const;

        /**
         * @brief Closes all of the windows and manages the cleanup of the leftovers.
         *
         * @return Status::OK if all of the windows were closed successfully, Status::ERROR otherwise.
         */
        Status closeAllWindows();

        /**
         * @brief Quits the engine.
         *
         * @details Remember that this method should be called at the end of the main function otherwise leaks might occur.
         *
         * @return Status::OK if engine was quit successfully, Status::ERROR otherwise.
         */
        Status quit();

        /**
         * @brief Get the list of managed windows.
         *
         * @return The list of managed windows.
         */
        std::vector<Window*> getWindows() const;

    private:
        std::vector<Window*> m_windows; /**< List of managed windows. */
    };
}

#endif /* CRUSTENGINE_CORE_H */
