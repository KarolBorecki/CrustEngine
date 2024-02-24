#ifndef _RENDERERWRAPPER_HPP_
#define _RENDERERWRAPPER_HPP_

#include <string>

#include <raylib-cpp.hpp>

/**
 * @brief Wrapper for currently used graphic library.
 */
class RendererWrapper
{
public:
    /**
     * @brief Represents status of graphic interfaces.
     */
    enum RendererStatus
    {
        STATUS_OK = 0,
        STATUS_FAIL
    };

    /**
     * @brief Creates new renderer. Does not create window.
     * @details This class should not be used. It is ought to be used through #Renderer class. Please refer to that class for more information.
     *
     * @param _width Width of graphic window.
     * @param _height Height of graphic window.
     *
     * @sa Renderer.hpp
     */
    RendererWrapper(uint16_t width, uint16_t height) : _width(width), _height(height)
    {
        p_window = nullptr;
    }
    virtual ~RendererWrapper() = default;

    /**
     * @brief Initzializs graphic wrapper. Should be called on wrapper start.
     *
     * @details Runs SDL Init funciton. Must be called before any drawing will be done on new Renderer.
     * Also after this call the RendererWrapper::CreateWindow method must be called in order to create new window.
     *
     * @return STATUS_OK if everything is fine and STATUS_FAIL is something failed and graphic interface cannot start.
     */
    RendererStatus Init();
    /**
     * @brief Opens new window to draw on.
     *
     * @details Runs SDL create window and renderer function. Mus be called after RednererWrapper::Init method.
     *
     * @return STATUS_OK if everything is fine and STATUS_FAIL is something failed and graphic interface cannot open new window.
     */
    RendererStatus CreateWindow();

    /**
     * @brief Sets window caption to #title.
     *
     * @param title New window caption.
     */
    void SetWindowTitle(std::string title);

    /**
     * @brief Draws straight line on the window from start (x, y) to end (x, y). X and y values are given in pixels.
     */
    void DrawLine(int startX, int startY, int endX, int endY);

    /**
     * @brief Draws triangle with given coordinates on the screen.
     *
     * @param p1X Point 1 X.
     * @param p1Y Point 1 Y.
     * @param p2X Point 2 X.
     * @param p2Y Point 2 Y.
     * @param p3X Point 3 X.
     * @param p3Y Point 3 Y.
     */
    void DrawTri(float p1X, float p1Y, float p2X, float p2Y, float p3X, float p3Y);

    /**
     * @brief Draws given triangle on the screen.
     *
     * @param p1X Point 1 X.
     * @param p1Y Point 1 Y.
     * @param p2X Point 2 X.
     * @param p2Y Point 2 Y.
     * @param p3X Point 3 X.
     * @param p3Y Point 3 Y.
     *
     * @param r Red value (0-255).
     * @param g Green value (0-255).
     * @param b Blue value (0-255).
     *
     * @sa Triangle.hpp
     */
    void DrawFilledTri(float p1X, float p1Y, float p2X, float p2Y, float p3X, float p3Y, uint8_t r, uint8_t g, uint8_t b);

    /**
     * @brief Draws given triangle on the screen.
     *
     * @param p1X Point 1 X.
     * @param p1Y Point 1 Y.
     * @param p2X Point 2 X.
     * @param p2Y Point 2 Y.
     * @param p3X Point 3 X.
     * @param p3Y Point 3 Y.
     *
     * @param rgb Red, Green, Blue value (0-255).
     *
     * @sa Triangle.hpp
     */
    void DrawFilledTri(float p1X, float p1Y, float p2X, float p2Y, float p3X, float p3Y, uint8_t rgb);

    /**
     * @brief Function called to show everything that has been drawn on the screen after last RendererWrapper::Show call.
     */
    void OnDrawStart();

    /**
     * @brief Function called to clean everything that has been drawn on the screen after last RendererWrapper::Clean call.
     */
    void OnDrawEnd();

    /**
     *
     */
    bool ShouldClose();

    /**
     * @brief Quits the graphic library.
     *
     * @details destroys renderer and window if exist.
     */
    void Quit();

    /**
     * @brief Getter for renderer width.
     *
     * @return uint16_t Width in pixels.
     */
    uint16_t Width() const;

    /**
     * @brief Getter for renderer height.
     *
     * @return uint16_t Height in pixels.
     */
    uint16_t Height() const;

private:
    uint16_t _width {0};  //!< Drawing window width.
    uint16_t _height {0}; //!< Drawing window height.

    raylib::Window *p_window {nullptr}; //!< Drawing window handler.
};

inline RendererWrapper::RendererStatus RendererWrapper::Init()
{
    return RendererStatus::STATUS_OK;
}

inline RendererWrapper::RendererStatus RendererWrapper::CreateWindow()
{
    p_window = new raylib::Window(_width, _height);
    return RendererStatus::STATUS_OK;
}

inline void RendererWrapper::SetWindowTitle(std::string title)
{
    // TODO
}

inline void RendererWrapper::DrawLine(int startX, int startY, int endX, int endY)
{
    // TODO
}

void RendererWrapper::DrawTri(float p1X, float p1Y, float p2X, float p2Y, float p3X, float p3Y)
{
    p1X = _width - p1X; p1Y = _height - p1Y;
    p2X = _width - p2X; p2Y = _height - p2Y;
    p3X = _width - p3X; p3Y = _height - p3Y;

    DrawLine(p1X, p1Y, p2X, p2Y);
    DrawLine(p2X, p2Y, p3X, p3Y);
    DrawLine(p3X, p3Y, p1X, p1Y);
}

inline void RendererWrapper::DrawFilledTri(float p1X, float p1Y, float p2X, float p2Y, float p3X, float p3Y, uint8_t r, uint8_t g, uint8_t b)
{
    DrawTriangle(
            {p1X, p1Y},
            {p2X, p2Y},
            {p3X, p3Y},
            {r, g, b, 255}
    );
}

inline void RendererWrapper::DrawFilledTri(float p1X, float p1Y, float p2X, float p2Y, float p3X, float p3Y, uint8_t rgb)
{
    DrawFilledTri(p1X, p1Y, p2X, p2Y, p3X, p3Y, rgb, rgb, rgb);
}

inline void RendererWrapper::OnDrawStart()
{
    BeginDrawing();
    ClearBackground(CLITERAL(Color){ 0, 0, 0, 255 });
}

inline void RendererWrapper::OnDrawEnd()
{
    EndDrawing();
}

inline bool RendererWrapper::ShouldClose()
{
    return WindowShouldClose();
}

void RendererWrapper::Quit()
{
    CloseWindow();
}

inline uint16_t RendererWrapper::Width() const { return _width; }

inline uint16_t RendererWrapper::Height() const { return _height; }

#endif /* _RENDERERWRAPPER_HPP_ */