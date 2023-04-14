#ifndef _INPUTEVENT_HPP_
#define _INPUTEVENT_HPP_

enum KeyCode : int32_t // TODO Make this enum same mapping as SDL's Keycode!
{
  KEY_0 = 0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,

  KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, 
  KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

  KEY_SPACEBA,
  KEY_ARROW_UP, KEY_ARROW_DOWN,
  KEY_ARROW_LEFT, KEY_ARROW_RIGHT,

  KET_LCTRL, KEY_LSHIFT, 
  KEY_RCTRL, KEY_RSHIFT,  
  KEY_CAPSLOCK, KEY_TAB, KEY_RETURN,

  MOUSE_L,
  MOUSE_R,
  MOUSE_SCROLL,

  KEY_LSQB, // [
  KEY_BACKSLASH,
  KEY_RSQB, // ]
  KEY_CIRC, // ^
  KEY_LOWBAR, // _
  KEY_GRAVE, // '

  KEY_COLON, // :
  KEY_EQUALS, // =
  KEY_LOWER_THAN, // <
  KEY_GREATER_THAN, // >
  KEY_QUESTIONMARK, // =
  KEY_AT, // @

  KEY_NONE,
};

enum EventType : int8_t
{
  EVENT_WINDOW_QUIT = 0,
  EVENT_KEY_DOWN,
  EVENT_KEY_UP,
  EVENT_MOUSE_DOWN,
  EVENT_MOUSE_UP,
  EVENT_WHEEL,
  EVENT_UNKNOWN,
};

typedef union InputEvent
{
  KeyCode keyCode;
  EventType type;
} InputEvent;

#endif /* _INPUTEVENT_HPP_ */