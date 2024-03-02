#ifndef _INPUTEVENT_HPP_
#define _INPUTEVENT_HPP_

#include <cstdint>

namespace Key
{
  constexpr uint8_t KEYS_COUNT = 70; // Remember to update this value when updating KeyCode enum
  constexpr uint8_t KEYS_STATE_ARRAY_SIZE = 127;

  /**
   * @brief Types of keys. Each represents key on a keyboard that can be pressed and called with EVENT_KEY_DOWN or EVENT_KEY_UP.
   *
   * @sa InputHandler.hpp
   */
  enum KeyCode : int32_t
  {
    KEY_NONE = 0,

    KEY_A = 4,
    KEY_B = 5,
    KEY_C = 6,
    KEY_D = 7,
    KEY_E = 8,
    KEY_F = 9,
    KEY_G = 10,
    KEY_H = 11,
    KEY_I = 12,
    KEY_J = 13,
    KEY_K = 14,
    KEY_L = 15,
    KEY_M = 16,
    KEY_N = 17,
    KEY_O = 18,
    KEY_P = 19,
    KEY_Q = 20,
    KEY_R = 21,
    KEY_S = 22,
    KEY_T = 23,
    KEY_U = 24,
    KEY_V = 25,
    KEY_W = 26,
    KEY_X = 27,
    KEY_Y = 28,
    KEY_Z = 29,

    KEY_1 = 30,
    KEY_2 = 31,
    KEY_3 = 32,
    KEY_4 = 33,
    KEY_5 = 34,
    KEY_6 = 35,
    KEY_7 = 36,
    KEY_8 = 37,
    KEY_9 = 38,
    KEY_0 = 39,

    KEY_RETURN = 40,
    KEY_ESCAPE = 41,
    KEY_BACKSPACE = 42,
    KEY_TAB = 43,
    KEY_SPACE = 44,

    KEY_MINUS = 45,
    KEY_EQUALS = 46,
    KEY_LEFTBRACKET = 47,
    KEY_RIGHTBRACKET = 48,
    KEY_BACKSLASH = 49,
    KEY_NONUSHASH = 50,
    KEY_SEMICOLON = 51,
    KEY_APOSTROPHE = 52,
    KEY_GRAVE = 53,
    KEY_COMMA = 54,
    KEY_PERIOD = 55,
    KEY_SLASH = 56,
  };
}
namespace Event
{
  constexpr uint8_t EVENTS_COUNT = 7; // Remember to update this value when updating EventType enum

  /**
   * @brief Types of an event. Each represents single event that can occur during engine work time.
   *
   * @sa InputHandler.hpp
   */
  enum EventType : uint8_t
  {
    EVENT_UNKNOWN = 0,
    EVENT_WINDOW_QUIT,
    EVENT_KEY_DOWN,
    EVENT_KEY_UP,
    EVENT_MOUSE_DOWN,
    EVENT_MOUSE_UP,
    EVENT_WHEEL,
  };
}

/**
 * @brief Struct of an event. Engine at each event checks what type of an event occured and what key was pressed (If EVENT_KEY_DOWN or EVENT_KEY_UP occured).
 *
 */
typedef struct InputEvent
{
  Key::KeyCode keyCode;
  Event::EventType type;
} InputEvent;

#endif /* _INPUTEVENT_HPP_ */