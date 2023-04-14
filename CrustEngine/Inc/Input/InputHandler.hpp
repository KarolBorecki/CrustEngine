#ifndef _INPUTHANDLER_HPP_
#define _INPUTHANDLER_HPP_

#include <SDL2/SDL.h>

#include <Logging/Logger.hpp>
#include <Input/InputEvent.hpp>

class InputHandler
{
public:
  static void BeginInputMonitoring(); 
  static void PollEvent();

  static InputEvent &GetLastEvent();
  static bool IsPressed(Key::KeyCode key);

private:
  static inline bool isInitialized { false };
  static inline InputEvent lastEvent;

  static const inline unsigned char *keyboardState; 
  static void ResetEventState();
  static Key::KeyCode ParseSDLKeyCodeEvent(int32_t keyCode);
};

inline void InputHandler::BeginInputMonitoring()
{
  ResetEventState();
  isInitialized = true;
  keyboardState = SDL_GetKeyboardState(NULL);
}

void InputHandler::PollEvent()
{
  if(!isInitialized) return;

  static SDL_Event sdlEvent;
  if (SDL_PollEvent(&sdlEvent))
  {
    if (sdlEvent.type == SDL_QUIT)
    {
      lastEvent.type = Event::EVENT_WINDOW_QUIT;
    }
    else if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.repeat == 0)
    {
      lastEvent.type = Event::EVENT_KEY_DOWN;
      lastEvent.keyCode = ParseSDLKeyCodeEvent(sdlEvent.key.keysym.sym);
    }else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.repeat == 0)
    {
      lastEvent.type = Event::EVENT_KEY_UP;
      lastEvent.keyCode = ParseSDLKeyCodeEvent(sdlEvent.key.keysym.sym);
    } else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)
    {
      lastEvent.type = Event::EVENT_MOUSE_DOWN;
    }else if (sdlEvent.type == SDL_MOUSEBUTTONUP)
    {
      lastEvent.type = Event::EVENT_MOUSE_UP;
    } else if (sdlEvent.type == SDL_MOUSEWHEEL)
    {
      lastEvent.type = Event::EVENT_WHEEL;
    } 
  }
}

bool InputHandler::IsPressed(Key::KeyCode key)
{
  return keyboardState[key] == 1;
}

inline InputEvent &InputHandler::GetLastEvent() { return lastEvent; }

inline void InputHandler::ResetEventState()
{
  lastEvent.type = Event::EVENT_UNKNOWN;
  lastEvent.keyCode = Key::KEY_NONE;
}

inline Key::KeyCode InputHandler::ParseSDLKeyCodeEvent(int32_t keyCode)
{
  if (keyCode > Key::KEY_Z) return Key::KEY_NONE;
  return static_cast<Key::KeyCode>(keyCode);
}

#endif /* _INPUTHANDLER_HPP_ */