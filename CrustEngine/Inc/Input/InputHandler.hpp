#ifndef _INPUTHANDLER_HPP_
#define _INPUTHANDLER_HPP_

#include <SDL2/SDL.h>

#include <Logging/Logger.hpp>
#include <Input/InputEvent.hpp>

/**
 * @brief A static class used to handle event from the user.
 */
class InputHandler
{
public:
  /**
   * @brief Method that has to be called once before any input monitoring will be done.
   */
  static void BeginInputMonitoring();

  /**
   * @brief Method that should be called once per frame. This function checks for any pending events.
   *
   * @details This method checks if any event occured and if so sets #lastEvent to this event. Then You are able to check last event using #GetLastEvent method.
   * Without this function called #lastEvent will be set to UNKNOWN state, but #IsPressed method shall work fine without it.
   */
  static void PollEvent();

  /**
   * @brief Get the last event that occured in the engine.
   *
   * @return InputEvent&
   */
  static InputEvent &GetLastEvent();
  /**
   * @brief Function that checks if given key is pressed. In order for this function to work You need to call #BeginInputMonitoring method first.
   *
   * @param key - key that will be check if it is pressed.
   * @return true - if key is pressed right now.
   * @return false  - if key is not pressed right now.
   */
  static bool IsPressed(Key::KeyCode key);

private:
  static inline bool isInitialized{false}; //!< Represents if handler was already initialized.
  static inline InputEvent lastEvent;      //!< Last event that occured in the engine.

  static const inline unsigned char *keyboardState; //!< Holds true/false value for each keyboard's key - tells if key is pressed right now.

  /**
   * @brief Reset's last event state to UNKNOW. Called on input monitoring start.
   */
  static void ResetEventState();
  /**
   * @brief Wrapper for SDL's keycodes - converts SDL's keycode to crustengine codes.
   *
   * @param keyCode - Keycode that will be converted.
   * @return Key::KeyCode - Converted keycode.
   */
  static Key::KeyCode ParseSDLKeyCodeEvent(int32_t keyCode);
};

inline void InputHandler::BeginInputMonitoring()
{
  if (isInitialized)
    return;
  ResetEventState();
  isInitialized = true;
  keyboardState = SDL_GetKeyboardState(NULL);
}

void InputHandler::PollEvent()
{
  if (!isInitialized)
    return;

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
    }
    else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.repeat == 0)
    {
      lastEvent.type = Event::EVENT_KEY_UP;
      lastEvent.keyCode = ParseSDLKeyCodeEvent(sdlEvent.key.keysym.sym);
    }
    else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)
    {
      lastEvent.type = Event::EVENT_MOUSE_DOWN;
    }
    else if (sdlEvent.type == SDL_MOUSEBUTTONUP)
    {
      lastEvent.type = Event::EVENT_MOUSE_UP;
    }
    else if (sdlEvent.type == SDL_MOUSEWHEEL)
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
  if (keyCode > Key::KEY_Z)
    return Key::KEY_NONE;
  return static_cast<Key::KeyCode>(keyCode);
}

#endif /* _INPUTHANDLER_HPP_ */