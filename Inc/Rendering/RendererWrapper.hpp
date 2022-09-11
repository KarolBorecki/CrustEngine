#ifndef _RENDERERWRAPPER_HPP_
#define _RENDERERWRAPPER_HPP_

#include <string>

#include <SDL2/SDL.h>

#define LibRendererWindow SDL_Window
#define LibRenderer SDL_Renderer
#define LibRendererBool SDL_bool

#define LibRendererFalse SDL_FALSE
#define LibRendererTrue SDL_TRUE

class RendererWrapper {
public:
  enum RendererStatus {
    STATUS_OK = 0,
    STATUS_FAIL
  };

  enum RendererEvent {
    EVENT_QUIT = 0,
    EVENT_UNKNOWN
  };

  enum RendererColor {
    BLACK = 0x000000,
    WHITE = 0xFFFFFF,
    RED = 0xFF0000,
    GREEN = 0x00FF00,
    BLUE = 0x0000FF
  };

  RendererWrapper(int _width, int _height) : width(_width), height(_height) {
    window = NULL;
    renderer = NULL;
    isRunning = LibRendererFalse;
  }
  ~RendererWrapper() {}

  RendererStatus Init();
  RendererStatus CreateWindow();

  void SetWindowTitle(std::string title);

  void SetDrawColor(int r, int g, int b, int a);
  void SetDrawColor(int r, int g, int b);
  void SetDrawColor(int color, int a);
  void SetDrawColor(int color);

  void DrawLine(int startX, int startY, int endX, int endY);

  void Show();

  void Clean();

  LibRendererBool IsRunning();
  void StopRunning();
  void GetEvent();

  void Quit();

  LibRenderer* GetRenderer();

private:
  int width;
  int height;

  LibRendererWindow* window;
  LibRenderer* renderer;

  LibRendererBool isRunning;
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
    if(event.type == SDL_QUIT) isRunning = LibRendererFalse;
}

void RendererWrapper::Quit() {
  if (renderer) SDL_DestroyRenderer(renderer);
  if (window) SDL_DestroyWindow(window);

  SDL_Quit(); /* TODO should it be here? */
}

inline LibRenderer* RendererWrapper::GetRenderer() {
  return renderer;
}

#endif /* _RENDERERWRAPPER_HPP_ */
