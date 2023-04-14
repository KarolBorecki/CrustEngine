#ifndef _INPUTHANDLER_HPP_
#define _INPUTHANDLER_HPP_

#include <SDL2/SDL.h>

#include <Logging/Logger.hpp>
#include <Input/InputEvent.hpp>

KeyCode ParseSDLKeyCodeEvent(int32_t keyCode)
{
  switch (keyCode)
  {
  case SDLK_0:
    return KEY_0;
    break;
  case SDLK_1:
    return KEY_1;
    break;
  case SDLK_2:
    return KEY_2;
    break;
  case SDLK_3:
    return KEY_3;
    break;
  case SDLK_4:
    return KEY_4;
    break;
  case SDLK_5:
    return KEY_5;
    break;
  case SDLK_6:
    return KEY_6;
    break;
  case SDLK_7:
    return KEY_7;
    break;
  case SDLK_8:
    return KEY_8;
    break;
  case SDLK_9:
    return KEY_9;
    break;

  case SDLK_a:
    return KEY_A;
    break;
  case SDLK_w:
    return KEY_W;
    break;
  case SDLK_s:
    return KEY_S;
    break;
  case SDLK_d:
    return KEY_D;
    break;

  default:
    return KEY_NONE;
    break;
  }
}

class InputHandler
{
public:
  static void BeginInputMonitoring(); 
  static void PollEvent();

  static InputEvent &GetEvent();

private:
  static inline bool isInitialized { false };
  static inline InputEvent event;

  static void ResetEventState();
};

void InputHandler::BeginInputMonitoring()
{
  ResetEventState();
  isInitialized = true;
}

void InputHandler::PollEvent()
{
  if(!isInitialized) return;
  static SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent))
  {
    if (sdlEvent.type == SDL_QUIT)
    {
      event.type = EVENT_WINDOW_QUIT;
    }
    else if (sdlEvent.type == SDL_KEYDOWN)
    {
      event.type = EVENT_KEY_DOWN;
      event.keyCode = ParseSDLKeyCodeEvent(sdlEvent.key.keysym.sym);
    }else if (sdlEvent.type == SDL_KEYUP)
    {
      event.type = EVENT_KEY_UP;
      event.keyCode = ParseSDLKeyCodeEvent(sdlEvent.key.keysym.sym);
    } else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)
    {
      event.type = EVENT_MOUSE_DOWN;
    }else if (sdlEvent.type == SDL_MOUSEBUTTONUP)
    {
      event.type = EVENT_MOUSE_UP;
    } else if (sdlEvent.type == SDL_MOUSEWHEEL)
    {
      event.type = EVENT_WHEEL;
    } else { ResetEventState(); }
 
  }
}

InputEvent &InputHandler::GetEvent() { return event; }

void InputHandler::ResetEventState()
{
  event.type = EVENT_UNKNOWN;
  event.keyCode = KEY_NONE;
}

#endif /* _INPUTHANDLER_HPP_ */