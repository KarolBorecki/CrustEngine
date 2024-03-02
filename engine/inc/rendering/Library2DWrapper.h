#ifndef CRUSTENGINE_LIBRARY2DWRAPPER_H
#define CRUSTENGINE_LIBRARY2DWRAPPER_H

#include <cstdint>
#include <string>

#include <raylib.h>

#include "static/Definitions.h"

namespace Crust {
    /**
     * @brief A wrapper class for the 2D library.
     */
    class Library2DWrapper {
    public:
        /**
         * @brief Construct a new Library2DWrapper object. Needs to be initialized and window must be open with specified width and height.
         */
        Library2DWrapper() = default;

        /**
         * @brief Destroy the Library2DWrapper object.
         */
        virtual ~Library2DWrapper() = default;

        /**
         * @brief Initialize the 2D library. Should be called on the start of the wrapper.
         *
         * @details Performs the initialization of the 2D library.
         *
         * @return The status of the initialization.
         */
        Crust::Status init();

        /**
         * @brief Create a window with the specified width and height.
         *
         * @details Performs the creation of the window by opening OS's new window to draw onto. It also sets the width and height of the window.
         *
         * @param p_width The width of the window.
         * @param p_height The height of the window.
         * @return The status of the window creation.
         */
        Crust::Status createWindow(uint16_t p_width, uint16_t p_height);

        /**
         * @brief Check if the window should close. Typicaly should return true when user clicks the close button on the window.
         *
         * @details Checks if the window should close. Should be called in the main loop of the application as the check for the loop.
         *
         * @return The status of the window closing.
         */
        bool shouldClose();

        /**
         * @brief Start the drawing.
         *
         * @details Starts the drawing. Should be called before each draw frame before any drawing is done and after the window is created.
         */
        void onDrawStart();

        /**
         * @brief End the drawing.
         *
         * @details Ends the drawing. Should be called after each draw frame after all drawing is done.
         */
        void onDrawEnd();

        /**
         * @brief Close the window.
         *
         * @details Closes the window. Should be called after the drawing loop ends and we want to cleanup leftovers of the library.
         */
        void quit();

        /**
         * @brief Resize the window.
         *
         * @details Resizes the window to the specified width and height.
         *
         * @param p_width The width of the window.
         * @param p_height The height of the window.
         */
        void resize(uint16_t p_width, uint16_t p_height);


        /**
         * @brief Set the window caption.
         *
         * @details Sets the caption of the window to the specified string that will be visible in the OS.
         *
         * @param p_caption The caption of the window.
         * @return The status of the caption setting.
         */
        Crust::Status setWindowCaption(const char* p_caption);

        /**
         * @brief Draw a triangle on the window in greyscale.
         *
         * @details Draws a pixel on the triangle at the specified position with the specified color.
         *
         * @param p_x The x position of the triangle's point.
         * @param p_y The y position of the triangle's point.
         * @param p_shade The color of the pixel in greyscale.
         */
        void drawTriangle(float p_x1, float p_y1, float p_x2, float p_y2, float p_x3, float p_y3, uint8_t p_shade);

    private:
        uint16_t m_width { 0 }; /**< Width of the window. */
        uint16_t m_height { 0 }; /**< Height of the window. */
    };
}

#endif /* CRUSTENGINE_LIBRARY2DWRAPPER_H */
