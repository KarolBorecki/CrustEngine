#include <SDL2/SDL.h>

#define DrawerWindow SDL_Window
#define DrawerRenderer SDL_Renderer
#define DrawerBool SDL_bool

#define DrawerFalse SDL_FALSE
#define DrawerTrue SDL_TRUE

class Drawer {
public:
  enum DrawerStatus {
    STATUS_OK = 0,
    STATUS_FAIL
  };

  enum DrawerEvent {
    EVENT_QUIT = 0,
    EVENT_UNKNOWN
  };

  enum DrawerColor {
    BLACK = 0x000000,
    WHITE = 0xFFFFFF,
    RED = 0xFF0000,
    GREEN = 0x00FF00,
    BLUE = 0x0000FF
  };

  Drawer(int _width, int _height) : width(_width), height(_height) {
    window = NULL;
    renderer = NULL;
    isRunning = DrawerFalse;
  }
  ~Drawer() {}

  DrawerStatus Init();
  DrawerStatus CreateWindow();

  void SetDrawColor(int r, int g, int b, int a);
  void SetDrawColor(int r, int g, int b);
  void SetDrawColor(int color, int a);
  void SetDrawColor(int color);

  void DrawLine(int startX, int startY, int endX, int endY);

  void Show();

  void Clean();

  DrawerBool IsRunning();
  void GetEvent();

  void Quit();

  DrawerRenderer* GetRenderer();

private:
  int width;
  int height;

  DrawerWindow* window;
  DrawerRenderer* renderer;

  DrawerBool isRunning;
};

inline Drawer::DrawerStatus Drawer::Init() {
  return SDL_Init(SDL_INIT_VIDEO) == 0 ? STATUS_OK : STATUS_FAIL;
}

inline Drawer::DrawerStatus Drawer::CreateWindow() {
  isRunning = DrawerTrue;
  return SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) == 0 ? STATUS_OK : STATUS_FAIL;
}

inline void Drawer::SetDrawColor(int r, int g, int b, int a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

inline void Drawer::SetDrawColor(int r, int g, int b) {
  SetDrawColor(r, g, b, 255);
}

#include <bitset>

inline void Drawer::SetDrawColor(int color, int a) {
  SetDrawColor((color & 0xFF0000)>> 16, (color & 0x00FF00) >> 8, (color & 0x0000FF), a);
}

inline void Drawer::SetDrawColor(int color) {
  SetDrawColor(color, 255);
}

inline void Drawer::DrawLine(int startX, int startY, int endX, int endY) {
  SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
}

inline void Drawer::Show() {
  SDL_RenderPresent(renderer);
}

inline void Drawer::Clean() {
  SDL_RenderClear(renderer);
}

inline DrawerBool Drawer::IsRunning() {
  return isRunning;
}

inline void Drawer::GetEvent() {
  SDL_Event event;
  while(SDL_PollEvent(&event))
    if(event.type == SDL_QUIT) isRunning = DrawerFalse;
}

inline void Drawer::Quit() {
  if (renderer) {
      SDL_DestroyRenderer(renderer);
  }
  if (window) {
      SDL_DestroyWindow(window);
  }
  SDL_Quit();
}

inline DrawerRenderer* Drawer::GetRenderer() {
  return renderer;
}
