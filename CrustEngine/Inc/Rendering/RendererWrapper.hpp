#ifndef _RENDERERWRAPPER_HPP_
#define _RENDERERWRAPPER_HPP_

#include <string>

#include <SDL2/SDL.h>

#define LibRendererWindow SDL_Window
#define LibRenderer SDL_Renderer
#define LibRendererBool SDL_bool

#define LibRendererFalse SDL_FALSE
#define LibRendererTrue SDL_TRUE

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
   * @brief Represents type of event occured on the graphic window.
   */
  enum RendererEvent
  {
    EVENT_QUIT = 0,
    EVENT_UNKNOWN
  };

  /**
   * @brief Represents color in classic web hexadecimal values.
   */
  enum RendererColor
  {
    BLACK = 0x000000,
    WHITE = 0xFFFFFF,
    RED = 0xFF0000,
    GREEN = 0x00FF00,
    BLUE = 0x0000FF
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
  RendererWrapper(uint32_t _width, uint32_t _height) : _width(_width), _height(_height)
  {
    p_window = NULL;
    p_renderer = NULL;
    _isRunning = LibRendererFalse;
  }
  virtual ~RendererWrapper() = default;

  /**
   * @brief Initzializs graphic wrapper. Should be called on wrapper start.
   *
   * @details Runs SDL Init funciton. Must be called before any drawing will be done on new Renderer.
   * Also after this call the RendererWrapper::CreateWindow method must be called in order to create new window.
   *
   * @return STATUS_OK if everyting is fine and STATUS_FAIL is something failed and graphic interface cannot start.
   */
  RendererStatus Init();
  /**
   * @brief Opens new window to draw on.
   *
   * @details Runs SDL create window and renderer function. Mus be called after RednererWrapper::Init method.
   *
   * @return STATUS_OK if everyting is fine and STATUS_FAIL is something failed and graphic interface cannot open new window.
   */
  RendererStatus CreateWindow();

  /**
   * @brief Sets window caption to #title.
   *
   * @param title New window caption.
   */
  void SetWindowTitle(std::string title);

  /**
   * @brief Sets drawing color to given values.
   *
   * @param r Red value (0-255).
   * @param g Green value (0-255).
   * @param b Blue value (0-255).
   * @param a Alpha/transparency value (0-255).
   */
  void SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  /**
   * @brief Sets drawing color to given values.
   *
   * @param r Red value (0-255).
   * @param g Green value (0-255).
   * @param b Blue value (0-255).
   * @param a Alpha/transparency value (0-255).
   */
  void SetDrawColor(uint8_t r, uint8_t g, uint8_t b);

  /**
   * @brief Sets drawing color to given values.
   *
   * @param color hexadecimal value of the color.
   * @param a Alpha/transparency value (0-255).
   *
   * @sa RendererColor
   */
  void SetDrawColor(uint32_t color, uint8_t a);

  /**
   * @brief Sets drawing color to given value.
   *
   * @param color hexadecimal value of the color.
   *
   * @sa RendererColor
   */
  void SetDrawColor(uint32_t color);

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
  void DrawTri(double p1X, double p1Y, double p2X, double p2Y, double p3X, double p3Y);

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
  void DrawFilledTri(double p1X, double p1Y, double p2X, double p2Y, double p3X, double p3Y, uint8_t r, uint8_t g, uint8_t b);

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
  void DrawFilledTri(double p1X, double p1Y, double p2X, double p2Y, double p3X, double p3Y, uint8_t rgb);

  /**
   * @brief Function called to show everything that has been drawn on the screen after last RendererWrapper::Show call.
   */
  void Show();
  /**
   * @brief Function called to clean everything that has been drawn on the screen after last RendererWrapper::Clean call.
   */
  void Clean();

  /**
   * @brief Getter for #isRunning field.
   *
   * @return LibRendererTrue if renderer is running and LibRendererFalse if rendedrer is not running.
   */
  LibRendererBool IsRunning() const;
  /**
   * @brief Stops the renderer.
   *
   * @details This function sets #isRunning field to LibRendererFalse in order to stop the main thread of this renderer.
   */
  void StopRunning();

  /**
   * @brief Quits the graphic library.
   *
   * @details destroys renderer and window if exist.
   */
  void Quit();

  /**
   * @brief Getter for wrapped renderer.
   */
  LibRenderer &GetRenderer() const;

  /**
   * @brief Getter for renderer width.
   *
   * @return uint32_t Width in pixels.
   */
  uint32_t Width() const;

  /**
   * @brief Getter for renderer height.
   *
   * @return uint32_t Height in pixels.
   */
  uint32_t Height() const;

private:
  uint32_t _width{0};  //!< Drawing window width.
  uint32_t _height{0}; //!< Drawing window height.

  LibRendererWindow *p_window{nullptr}; //!< Drawing window handler.
  LibRenderer *p_renderer{nullptr};     //!< Drawing renderer handler.

  LibRendererBool _isRunning{LibRendererFalse}; //!< Flag representing if the renderer thread is running.
};

inline RendererWrapper::RendererStatus RendererWrapper::Init()
{
  return SDL_Init(SDL_INIT_VIDEO) == 0 ? STATUS_OK : STATUS_FAIL;
}

inline RendererWrapper::RendererStatus RendererWrapper::CreateWindow()
{
  _isRunning = LibRendererTrue;
  return SDL_CreateWindowAndRenderer(_width, _height, 0, &p_window, &p_renderer) == 0 ? STATUS_OK : STATUS_FAIL;
}

inline void RendererWrapper::SetWindowTitle(std::string title)
{
  SDL_SetWindowTitle(p_window, title.c_str());
}

inline void RendererWrapper::SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  SDL_SetRenderDrawColor(p_renderer, r, g, b, a);
}

inline void RendererWrapper::SetDrawColor(uint8_t r, uint8_t g, uint8_t b)
{
  SetDrawColor(r, g, b, 255);
}

inline void RendererWrapper::SetDrawColor(uint32_t color, uint8_t a)
{
  SetDrawColor((color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, (color & 0x0000FF), a);
}

inline void RendererWrapper::SetDrawColor(uint32_t color)
{
  SetDrawColor(color, 255);
}

inline void RendererWrapper::DrawLine(int startX, int startY, int endX, int endY)
{
  SDL_RenderDrawLine(p_renderer, startX, startY, endX, endY);
}

void RendererWrapper::DrawTri(double p1X, double p1Y, double p2X, double p2Y, double p3X, double p3Y)
{
  DrawLine(p1X, p1Y, p2X, p2Y);
  DrawLine(p2X, p2Y, p3X, p3Y);
  DrawLine(p3X, p3Y, p1X, p1Y);
}

inline void RendererWrapper::DrawFilledTri(double p1X, double p1Y, double p2X, double p2Y, double p3X, double p3Y, uint8_t r, uint8_t g, uint8_t b)
{
  const std::vector<SDL_Vertex> verts =
      {
          {
              SDL_FPoint{static_cast<float>(p1X), static_cast<float>(p1Y)},
              SDL_Color{r, g, b, 255},
              SDL_FPoint{0},
          },
          {
              SDL_FPoint{static_cast<float>(p2X), static_cast<float>(p2Y)},
              SDL_Color{r, g, b, 255},
              SDL_FPoint{0},
          },
          {
              SDL_FPoint{static_cast<float>(p3X), static_cast<float>(p3Y)},
              SDL_Color{r, g, b, 255},
              SDL_FPoint{0},
          },
      };
  SDL_RenderGeometry(p_renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
}

inline void RendererWrapper::DrawFilledTri(double p1X, double p1Y, double p2X, double p2Y, double p3X, double p3Y, uint8_t rgb)
{
  DrawFilledTri(p1X, p1Y, p2X, p2Y, p3X, p3Y, rgb, rgb, rgb);
}

inline void RendererWrapper::Show()
{
  SDL_RenderPresent(p_renderer);
}

inline void RendererWrapper::Clean()
{
  SDL_RenderClear(p_renderer);
}

inline LibRendererBool RendererWrapper::IsRunning() const
{
  return _isRunning;
}

inline void RendererWrapper::StopRunning()
{
  _isRunning = LibRendererFalse;
}

void RendererWrapper::Quit()
{
  if (p_renderer)
    SDL_DestroyRenderer(p_renderer);
  if (p_window)
    SDL_DestroyWindow(p_window);

  SDL_Quit();
}

inline LibRenderer &RendererWrapper::GetRenderer() const { return *p_renderer; }

inline uint32_t RendererWrapper::Width() const { return _width; }

inline uint32_t RendererWrapper::Height() const { return _height; }

#endif /* _RENDERERWRAPPER_HPP_ */
