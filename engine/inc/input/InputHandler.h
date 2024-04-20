#ifndef CRUSTENGINE_INPUTHANDLER_H
#define CRUSTENGINE_INPUTHANDLER_H


#include <SDL2/SDL.h>

#include "input/InputEvent.h"

namespace Crust {
    /**
 * @brief A static class used to handle event from the user.
 */
    class InputHandler {
    public:
        /**
         * @brief Method that has to be called once before any input monitoring will be done.
         */
        static void beginInputMonitoring();

        /**
         * @brief Method that should be called once per frame. This function checks for any pending events.
         *
         * @details This method checks if any event occured and if so sets #lastEvent to this event. Then You are able to check last event using #GetLastEvent method.
         * Without this function called #lastEvent will be set to UNKNOWN state, but #IsPressed method shall work fine without it.
         */
        static void pollEvent();

        /**
         * @brief Get the last event that occured in the engine.
         *
         * @return InputEvent&
         */
        static InputEvent &getLastEvent();

        /**
         * @brief Function that checks if given key is pressed. In order for this function to work You need to call #BeginInputMonitoring method first.
         *
         * @param key - key that will be check if it is pressed.
         * @return true - if key is pressed right now.
         * @return false  - if key is not pressed right now.
         */
        static bool isPressed(Key::KeyCode key);

    private:
        static inline bool m_is_initialized{false}; //!< Represents if handler was already initialized.
        static inline InputEvent m_last_event;      //!< Last event that occured in the engine.

        static const inline unsigned char *m_keyboard_state; //!< Holds true/false value for each keyboard's key - tells if key is pressed right now.

    private:
        /**
         * @brief Reset's last event state to UNKNOW. Called on input monitoring start.
         */
        static void resetEventState();

        /**
         * @brief Wrapper for SDL's keycodes - converts SDL's keycode to crustengine codes.
         *
         * @param p_key_code - Keycode that will be converted.
         * @return Key::KeyCode - Converted keycode.
         */
        static Key::KeyCode parseSDLKeyCodeEvent(uint32_t p_key_code);
    };

    inline void InputHandler::beginInputMonitoring() {
        if (m_is_initialized)
            return;
        resetEventState();
        m_is_initialized = true;
        m_keyboard_state = SDL_GetKeyboardState(NULL);
    }

    inline void InputHandler::pollEvent() {
        if (!m_is_initialized)
            return;

        static SDL_Event sdlEvent;
        if (SDL_PollEvent(&sdlEvent)) {
            if (sdlEvent.type == SDL_QUIT) {
                m_last_event.type = Event::EVENT_WINDOW_QUIT;
            } else if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.repeat == 0) {
                m_last_event.type = Event::EVENT_KEY_DOWN;
                m_last_event.key_code = parseSDLKeyCodeEvent(sdlEvent.key.keysym.sym);
            } else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.repeat == 0) {
                m_last_event.type = Event::EVENT_KEY_UP;
                m_last_event.key_code = parseSDLKeyCodeEvent(sdlEvent.key.keysym.sym);
            } else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
                m_last_event.type = Event::EVENT_MOUSE_DOWN;
            } else if (sdlEvent.type == SDL_MOUSEBUTTONUP) {
                m_last_event.type = Event::EVENT_MOUSE_UP;
            } else if (sdlEvent.type == SDL_MOUSEWHEEL) {
                m_last_event.type = Event::EVENT_WHEEL;
            }
        }
    }

    inline bool InputHandler::isPressed(Key::KeyCode key) {
        return m_keyboard_state[key] == 1;
    }

    inline InputEvent &InputHandler::getLastEvent() { return m_last_event; }

    inline void InputHandler::resetEventState() {
        m_last_event.type = Event::EVENT_UNKNOWN;
        m_last_event.key_code = Key::KEY_NONE;
    }

    inline Key::KeyCode InputHandler::parseSDLKeyCodeEvent(uint32_t p_key_code) {
        if (p_key_code > Key::KEY_Z)
            return Key::KEY_NONE;
        return static_cast<Key::KeyCode>(p_key_code);
    }
}

#endif /* CRUSTENGINE_INPUTHANDLER_H */
