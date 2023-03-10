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
class RendererWrapper {
public:
  /**
  * @brief Represents status of graphic interfaces.
  */
  enum RendererStatus {
    STATUS_OK = 0,
    STATUS_FAIL
  };
  /**
  * @brief Represents type of event occured on the graphic window.
  */
  enum RendererEvent {
    EVENT_QUIT = 0,
    EVENT_UNKNOWN
  };
  /**
  * @brief Represents color in classic web hexadecimal values.
  */
  enum RendererColor {
    BLACK = 0x000000,
    WHITE = 0xFFFFFF,
    RED = 0xFF0000,
    GREEN = 0x00FF00,
    BLUE = 0x0000FF
  };

  /**
  * @param _width Width of graphic window.
  * @param _height Height of graphic window.
  */
  RendererWrapper(int _width, int _height) : width(_width), height(_height) {
    window = NULL;
    renderer = NULL;
    isRunning = LibRendererFalse;
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
  void SetDrawColor(int r, int g, int b, int a);
  /**
  * @brief Sets drawing color to given values.
  *
  * @param r Red value (0-255).
  * @param g Green value (0-255).
  * @param b Blue value (0-255).
  * @param a Alpha/transparency value (0-255).
  */
  void SetDrawColor(int r, int g, int b);
  /**
  * @brief Sets drawing color to given values.
  *
  * @param color hexadecimal value of the color.
  * @param a Alpha/transparency value (0-255).
  *
  * @sa RendererColor
  */
  void SetDrawColor(int color, int a);
  /**
  * @brief Sets drawing color to given value.
  *
  * @param color hexadecimal value of the color.
  *
  * @sa RendererColor
  */
  void SetDrawColor(int color);

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
  * @sa Triangle.hpp
  */
  void DrawFilledTri(double p1X, double p1Y, double p2X, double p2Y, double p3X, double p3Y, uint8_t r, uint8_t g, uint8_t b);

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
  LibRendererBool IsRunning();
  /**
  * @brief Stops the renderer.
  *
  * @details This function sets #isRunning field to LibRendererFalse in order to stop the main thread of this renderer.
  */
  void StopRunning();
  /**
  * @brief Checks for events from user and calls methods accordingly.
  */
  void GetEvent();

  /**
  * @brief Quits the graphic library.
  *
  * @details destroys renderer and window if exist.
  */
  void Quit();

  /**
  * @brief Getter for wrapped renderer.
  */
  LibRenderer* GetRenderer();

  /**
  * @brief Getter for renderer width.
  */
  int Width();
  /**
  * @brief Getter for renderer height.
  */
  int Height();

private:
  int width; //!< Drawing window width.
  int height; //!< Drawing window height.

  LibRendererWindow* window; //!< Drawing window handler.
  LibRenderer* renderer; //!< Drawing renderer handler.

  LibRendererBool isRunning; //!< Flag representing if the renderer thread is running.
};

inline RendererWrapper::RendererStatus RendererWrapper::Init() {
  return SDL_Init(SDL_INIT_VIDEO) == 0 ? STATUS_OK : STATUS_FAIL;
}

inline RendererWrapper::RendererStatus RendererWrapper::CreateWindow() {
  isRunning = LibRendererTrue;
  return SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) == 0 ? STATUS_OK : STATUS_FAIL;
}

inline void RendererWrapper::SetWindowTitle(std::string title) {
  SDL_SetWindowTitle(window, title.c_str());
}

inline void RendererWrapper::SetDrawColor(int r, int g, int b, int a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

inline void RendererWrapper::SetDrawColor(int r, int g, int b) {
  SetDrawColor(r, g, b, 255);
}

inline void RendererWrapper::SetDrawColor(int color, int a) {
  SetDrawColor((color & 0xFF0000)>> 16, (color & 0x00FF00) >> 8, (color & 0x0000FF), a);
}

inline void RendererWrapper::SetDrawColor(int color) {
  SetDrawColor(color, 255);
}

inline void RendererWrapper::DrawLine(int startX, int startY, int endX, int endY) {
  SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
}

void RendererWrapper::DrawTri(double p1X, double p1Y, double p2X, double p2Y, double p3X, double p3Y) {
  DrawLine(p1X, p1Y, p2X, p2Y);
  DrawLine(p2X, p2Y, p3X, p3Y);
  DrawLine(p3X, p3Y, p1X, p1Y);
}

inline void RendererWrapper::DrawFilledTri(double p1X, double p1Y, double p2X, double p2Y, double p3X, double p3Y, uint8_t r, uint8_t g, uint8_t b) {
  const std::vector< SDL_Vertex > verts =
  {
      { SDL_FPoint{ static_cast<float>(p1X), static_cast<float>(p1Y) }, SDL_Color{ r, g, b, 255 }, SDL_FPoint{ 0 }, },
      { SDL_FPoint{ static_cast<float>(p2X), static_cast<float>(p2Y) }, SDL_Color{ r, g, b, 255 }, SDL_FPoint{ 0 }, },
      { SDL_FPoint{ static_cast<float>(p3X), static_cast<float>(p3Y) }, SDL_Color{ r, g, b, 255 }, SDL_FPoint{ 0 }, },
  };
  SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
}

inline void RendererWrapper::Show() {
  SDL_RenderPresent(renderer);
}

inline void RendererWrapper::Clean() {
  SDL_RenderClear(renderer);
}

inline LibRendererBool RendererWrapper::IsRunning() {
  return isRunning;
}

inline void RendererWrapper::StopRunning() {
  isRunning = LibRendererFalse;
}

void RendererWrapper::GetEvent() {
  SDL_Event event;
  while(SDL_PollEvent(&event))
    if(event.type == SDL_QUIT) isRunning = LibRendererFalse; //TODO Create event system
}

void RendererWrapper::Quit() {
  if (renderer) SDL_DestroyRenderer(renderer);
  if (window) SDL_DestroyWindow(window);

  SDL_Quit(); /* TODO should it be here? */
}

inline LibRenderer* RendererWrapper::GetRenderer() {
  return renderer;
}

inline int RendererWrapper::Width() { return width; }

inline int RendererWrapper::Height() { return height; }

#endif /* _RENDERERWRAPPER_HPP_ */
