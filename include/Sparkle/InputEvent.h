#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
//
// Created by z3r0_ on 10/01/2024.
//

#ifndef SPARKLE_SOLUTION_INPUT_EVENT_H
#define SPARKLE_SOLUTION_INPUT_EVENT_H

#include <string>
#include <cassert>

namespace Sparkle
{
    // Input related ENUMS transformed into CLASSES for convenient methods like c_str() and implicit string conversion
    // They should be used (and enforced to be used) as ENUMS

#pragma region Enum Input Types

    /// MouseButton
    class MouseButtonType
    {
#define MOUSE_BUTTON_LIST(E) \
E(BUTTON_NONE) \
E(BUTTON_LEFT) \
E(BUTTON_MIDDLE) \
E(BUTTON_RIGHT) \
E(BUTTON_X1) \
E(BUTTON_X2) \
E(Count)
    public:
        enum MouseButtonEnum
        {
#define MOUSE_BUTTON_DEF(name) name,
            MOUSE_BUTTON_LIST(MOUSE_BUTTON_DEF)
#undef MOUSE_BUTTON_DEF
        };

        MouseButtonType() = default;

        constexpr MouseButtonType(MouseButtonEnum enumValue) : value(enumValue)
        {}

        // prevent using as a pointer or boolean operator
        void *operator new(std::size_t) = delete;

        void *operator new[](std::size_t) = delete;

        void operator delete(void *p) = delete;

        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator MouseButtonEnum() const
        { return value; }

#define MOUSE_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char *c_str()
        {
            switch (value)
            {
                MOUSE_BUTTON_LIST(MOUSE_STRING_DEF)
                default:
                    return "MouseButton Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                MOUSE_BUTTON_LIST(MOUSE_STRING_DEF)
                default:
                    return "MouseButton Unknown";
            }
        }

#undef GAMEPAD_STRING_DEF

    private:
        MouseButtonEnum value;
#undef GAMEPAD_BUTTON_LIST
    };

    /// MouseAxis
    class MouseAxisType
    {
#define MOUSE_AXIS_LIST(E) \
E(AXIS_X) \
E(AXIS_Y) \
E(SCROLL_WHEEL_Y) \
E(SCROLL_WHEEL_X) \
E(Count) \
E(AXIS_NONE)
    public:
        enum MouseAxisEnum
        {
#define MOUSE_AXIS_DEF(name) name,
            MOUSE_AXIS_LIST(MOUSE_AXIS_DEF)
#undef MOUSE_AXIS_DEF
        };

        MouseAxisType() = default;

        constexpr MouseAxisType(MouseAxisEnum enumValue) : value(enumValue)
        {}

        // prevent using as a pointer or boolean operator
        void *operator new(std::size_t) = delete;

        void *operator new[](std::size_t) = delete;

        void operator delete(void *p) = delete;

        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator MouseAxisEnum() const
        { return value; }

#define MOUSE_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char *c_str()
        {
            switch (value)
            {
                MOUSE_AXIS_LIST(MOUSE_STRING_DEF)
                default:
                    return "MouseAxis Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                MOUSE_AXIS_LIST(MOUSE_STRING_DEF)
                default:
                    return "GamepadAxis Unknown";
            }
        }

#undef MOUSE_STRING_DEF

    private:
        MouseAxisEnum value;
#undef MOUSE_AXIS_LIST
    };

    /// MouseStick
    class MouseStickType
    {
#define MOUSE_STICK_LIST(E) \
E(MOUSE_MOVEMENT) \
E(Count)
    public:
        enum MouseStickEnum
        {
#define MOUSE_STICK_DEF(name) name,
            MOUSE_STICK_LIST(MOUSE_STICK_DEF)
#undef MOUSE_STICK_DEF
        };

        MouseStickType() = default;

        constexpr MouseStickType(MouseStickEnum enumValue) : value(enumValue)
        {}

        // prevent using as a pointer or boolean operator
        void *operator new(std::size_t) = delete;

        void *operator new[](std::size_t) = delete;

        void operator delete(void *p) = delete;

        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator MouseStickEnum() const
        { return value; }

#define MOUSE_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char *c_str()
        {
            switch (value)
            {
                MOUSE_STICK_LIST(MOUSE_STRING_DEF)
                default:
                    return "MouseStick Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                MOUSE_STICK_LIST(MOUSE_STRING_DEF)
                default:
                    return "MouseStick Unknown";
            }
        }

#undef MOUSE_STRING_DEF

    private:
        MouseStickEnum value;
#undef GAMEPAD_STICK_LIST
    };

    /// KeyboardButton
    class KeyboardButtonType
    {
#pragma region Key List
/// This key enum is based on SDL_SCANCODE
#define KEYBOARD_BUTTON_LIST(E) \
E(UNKNOWN)                      \
E(KEY_RESERVED_1)               \
E(KEY_RESERVED_2)               \
E(KEY_RESERVED_3)               \
E(KEY_A)                        \
E(KEY_B)                        \
E(KEY_C)                        \
E(KEY_D)                        \
E(KEY_E)                        \
E(KEY_F)                        \
E(KEY_G)                        \
E(KEY_H)                        \
E(KEY_I)                        \
E(KEY_J)                        \
E(KEY_K)                        \
E(KEY_L)                        \
E(KEY_M)                        \
E(KEY_N)                        \
E(KEY_O)                        \
E(KEY_P)                        \
E(KEY_Q)                        \
E(KEY_R)                        \
E(KEY_S)                        \
E(KEY_T)                        \
E(KEY_U)                        \
E(KEY_V)                        \
E(KEY_W)                        \
E(KEY_X)                        \
E(KEY_Y)                        \
E(KEY_Z)                        \
E(KEY_1)                        \
E(KEY_2)                        \
E(KEY_3)                        \
E(KEY_4)                        \
E(KEY_5)                        \
E(KEY_6)                        \
E(KEY_7)                        \
E(KEY_8)                        \
E(KEY_9)                        \
E(KEY_0)                        \
E(KEY_RETURN)                   \
E(KEY_ESCAPE)                   \
E(KEY_BACKSPACE)                \
E(KEY_TAB)                      \
E(KEY_SPACE)                    \
E(KEY_MINUS)                    \
E(KEY_EQUALS)                   \
E(KEY_LEFTBRACKET)              \
E(KEY_RIGHTBRACKET)             \
E(KEY_BACKSLASH)                \
E(KEY_NONUSHASH)                \
E(KEY_SEMICOLON)                \
E(KEY_APOSTROPHE)               \
E(KEY_GRAVE)                    \
E(KEY_COMMA)                    \
E(KEY_PERIOD)                   \
E(KEY_SLASH)                    \
E(KEY_CAPSLOCK)                 \
E(KEY_F1)                       \
E(KEY_F2)                       \
E(KEY_F3)                       \
E(KEY_F4)                       \
E(KEY_F5)                       \
E(KEY_F6)                       \
E(KEY_F7)                       \
E(KEY_F8)                       \
E(KEY_F9)                       \
E(KEY_F10)                      \
E(KEY_F11)                      \
E(KEY_F12)                      \
E(KEY_PRINTSCREEN)              \
E(KEY_SCROLLLOCK)               \
E(KEY_PAUSE)                    \
E(KEY_INSERT)                   \
E(KEY_HOME)                     \
E(KEY_PAGEUP)                   \
E(KEY_DELETE)                   \
E(KEY_END)                      \
E(KEY_PAGEDOWN)                 \
E(KEY_RIGHT)                    \
E(KEY_LEFT)                     \
E(KEY_DOWN)                     \
E(KEY_UP)                       \
E(KEY_NUMLOCKCLEAR)             \
E(KEY_KP_DIVIDE)                \
E(KEY_KP_MULTIPLY)              \
E(KEY_KP_MINUS)                 \
E(KEY_KP_PLUS)                  \
E(KEY_KP_ENTER)                 \
E(KEY_KP_1)                     \
E(KEY_KP_2)                     \
E(KEY_KP_3)                     \
E(KEY_KP_4)                     \
E(KEY_KP_5)                     \
E(KEY_KP_6)                     \
E(KEY_KP_7)                     \
E(KEY_KP_8)                     \
E(KEY_KP_9)                     \
E(KEY_KP_0)                     \
E(KEY_KP_PERIOD)                \
E(KEY_NONUSBACKSLASH)           \
E(KEY_APPLICATION)              \
E(KEY_POWER)                    \
E(KEY_KP_EQUALS)                \
E(KEY_F13)                      \
E(KEY_F14)                      \
E(KEY_F15)                      \
E(KEY_F16)                      \
E(KEY_F17)                      \
E(KEY_F18)                      \
E(KEY_F19)                      \
E(KEY_F20)                      \
E(KEY_F21)                      \
E(KEY_F22)                      \
E(KEY_F23)                      \
E(KEY_F24)                      \
E(KEY_EXECUTE)                  \
E(KEY_HELP)                     \
E(KEY_MENU)                     \
E(KEY_SELECT)                   \
E(KEY_STOP)                     \
E(KEY_AGAIN)                    \
E(KEY_UNDO)                     \
E(KEY_CUT)                      \
E(KEY_COPY)                     \
E(KEY_PASTE)                    \
E(KEY_FIND)                     \
E(KEY_MUTE)                     \
E(KEY_VOLUMEUP)                 \
E(KEY_VOLUMEDOWN)               \
E(KEY_LOCKINGCAPSLOCK)          \
E(KEY_LOCKINGNUMLOCK)           \
E(KEY_LOCKINGSCROLLLOCK)        \
E(KEY_KP_COMMA)                 \
E(KEY_KP_EQUALSAS400)           \
E(KEY_INTERNATIONAL1)           \
E(KEY_INTERNATIONAL2)           \
E(KEY_INTERNATIONAL3)           \
E(KEY_INTERNATIONAL4)           \
E(KEY_INTERNATIONAL5)           \
E(KEY_INTERNATIONAL6)           \
E(KEY_INTERNATIONAL7)           \
E(KEY_INTERNATIONAL8)           \
E(KEY_INTERNATIONAL9)           \
E(KEY_LANG1)                    \
E(KEY_LANG2)                    \
E(KEY_LANG3)                    \
E(KEY_LANG4)                    \
E(KEY_LANG5)                    \
E(KEY_LANG6)                    \
E(KEY_LANG7)                    \
E(KEY_LANG8)                    \
E(KEY_LANG9)                    \
E(KEY_ALTERASE)                 \
E(KEY_SYSREQ)                   \
E(KEY_CANCEL)                   \
E(KEY_CLEAR)                    \
E(KEY_PRIOR)                    \
E(KEY_RETURN2)                  \
E(KEY_SEPARATOR)                \
E(KEY_OUT)                      \
E(KEY_OPER)                     \
E(KEY_CLEARAGAIN)               \
E(KEY_CRSEL)                    \
E(KEY_EXSEL)                    \
E(KEY_RESERVED_4)               \
E(KEY_RESERVED_5)               \
E(KEY_RESERVED_6)               \
E(KEY_RESERVED_7)               \
E(KEY_RESERVED_8)               \
E(KEY_RESERVED_9)               \
E(KEY_RESERVED_10)              \
E(KEY_RESERVED_11)              \
E(KEY_RESERVED_12)              \
E(KEY_RESERVED_13)              \
E(KEY_RESERVED_14)              \
E(KEY_KP_00)                    \
E(KEY_KP_000)                   \
E(KEY_THOUSANDSSEPARATOR)       \
E(KEY_DECIMALSEPARATOR)         \
E(KEY_CURRENCYUNIT)             \
E(KEY_CURRENCYSUBUNIT)          \
E(KEY_KP_LEFTPAREN)             \
E(KEY_KP_RIGHTPAREN)            \
E(KEY_KP_LEFTBRACE)             \
E(KEY_KP_RIGHTBRACE)            \
E(KEY_KP_TAB)                   \
E(KEY_KP_BACKSPACE)             \
E(KEY_KP_A)                     \
E(KEY_KP_B)                     \
E(KEY_KP_C)                     \
E(KEY_KP_D)                     \
E(KEY_KP_E)                     \
E(KEY_KP_F)                     \
E(KEY_KP_XOR)                   \
E(KEY_KP_POWER)                 \
E(KEY_KP_PERCENT)               \
E(KEY_KP_LESS)                  \
E(KEY_KP_GREATER)               \
E(KEY_KP_AMPERSAND)             \
E(KEY_KP_DBLAMPERSAND)          \
E(KEY_KP_VERTICALBAR)           \
E(KEY_KP_DBLVERTICALBAR)        \
E(KEY_KP_COLON)                 \
E(KEY_KP_HASH)                  \
E(KEY_KP_SPACE)                 \
E(KEY_KP_AT)                    \
E(KEY_KP_EXCLAM)                \
E(KEY_KP_MEMSTORE)              \
E(KEY_KP_MEMRECALL)             \
E(KEY_KP_MEMCLEAR)              \
E(KEY_KP_MEMADD)                \
E(KEY_KP_MEMSUBTRACT)           \
E(KEY_KP_MEMMULTIPLY)           \
E(KEY_KP_MEMDIVIDE)             \
E(KEY_KP_PLUSMINUS)             \
E(KEY_KP_CLEAR)                 \
E(KEY_KP_CLEARENTRY)            \
E(KEY_KP_BINARY)                \
E(KEY_KP_OCTAL)                 \
E(KEY_KP_DECIMAL)               \
E(KEY_KP_HEXADECIMAL)           \
E(KEY_RESERVED_15)              \
E(KEY_RESERVED_16)              \
E(KEY_LCTRL)                    \
E(KEY_LSHIFT)                   \
E(KEY_LALT)                     \
E(KEY_LGUI)                     \
E(KEY_RCTRL)                    \
E(KEY_RSHIFT)                   \
E(KEY_RALT)                     \
E(KEY_RGUI)                     \
E(KEY_RESERVED_17)              \
E(KEY_RESERVED_18)              \
E(KEY_RESERVED_19)              \
E(KEY_RESERVED_20)              \
E(KEY_RESERVED_21)              \
E(KEY_RESERVED_22)              \
E(KEY_RESERVED_23)              \
E(KEY_RESERVED_24)              \
E(KEY_RESERVED_25)              \
E(KEY_RESERVED_26)              \
E(KEY_RESERVED_27)              \
E(KEY_RESERVED_28)              \
E(KEY_RESERVED_29)              \
E(KEY_RESERVED_30)              \
E(KEY_RESERVED_31)              \
E(KEY_RESERVED_32)              \
E(KEY_RESERVED_33)              \
E(KEY_RESERVED_34)              \
E(KEY_RESERVED_35)              \
E(KEY_RESERVED_36)              \
E(KEY_RESERVED_37)              \
E(KEY_RESERVED_38)              \
E(KEY_RESERVED_39)              \
E(KEY_RESERVED_40)              \
E(KEY_RESERVED_41)              \
E(KEY_MODE)                     \
E(KEY_AUDIONEXT)                \
E(KEY_AUDIOPREV)                \
E(KEY_AUDIOSTOP)                \
E(KEY_AUDIOPLAY)                \
E(KEY_AUDIOMUTE)                \
E(KEY_MEDIASELECT)              \
E(KEY_WWW)                      \
E(KEY_MAIL)                     \
E(KEY_CALCULATOR)               \
E(KEY_COMPUTER)                 \
E(KEY_AC_SEARCH)                \
E(KEY_AC_HOME)                  \
E(KEY_AC_BACK)                  \
E(KEY_AC_FORWARD)               \
E(KEY_AC_STOP)                  \
E(KEY_AC_REFRESH)               \
E(KEY_AC_BOOKMARKS)             \
E(KEY_BRIGHTNESSDOWN)           \
E(KEY_BRIGHTNESSUP)             \
E(KEY_DISPLAYSWITCH)            \
E(KEY_KBDILLUMTOGGLE)           \
E(KEY_KBDILLUMDOWN)             \
E(KEY_KBDILLUMUP)               \
E(KEY_EJECT)                    \
E(KEY_SLEEP)                    \
E(KEY_APP1)                     \
E(KEY_APP2)                     \
E(KEY_AUDIOREWIND)              \
E(KEY_AUDIOFASTFORWARD)         \
E(KEY_SOFTLEFT)                 \
E(KEY_SOFTRIGHT)                \
E(KEY_CALL)                     \
E(KEY_ENDCALL)                  \
E(Count)                        \
E(KEY_NONE)
#pragma endregion Key List
    public:
        enum KeyboardButtonEnum
        {
#define KEYBOARD_BUTTON_DEF(name) name,
            KEYBOARD_BUTTON_LIST(KEYBOARD_BUTTON_DEF)
#undef KEYBOARD_BUTTON_DEF
        };

        KeyboardButtonType() = default;

        constexpr KeyboardButtonType(KeyboardButtonEnum enumValue) : value(enumValue)
        {}

        // prevent using as a pointer or boolean operator
        void *operator new(std::size_t) = delete;

        void *operator new[](std::size_t) = delete;

        void operator delete(void *p) = delete;

        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator KeyboardButtonEnum() const
        { return value; }

#define KEYBOARD_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char *c_str()
        {
            switch (value)
            {
                KEYBOARD_BUTTON_LIST(KEYBOARD_STRING_DEF)
                default:
                    return "KeyboardButton Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                KEYBOARD_BUTTON_LIST(KEYBOARD_STRING_DEF)
                default:
                    return "KeyboardButton Unknown";
            }
        }

#undef KEYBOARD_STRING_DEF

    private:
        KeyboardButtonEnum value;
#undef KEYBOARD_BUTTON_LIST
    };

    /// KeyboardAxis
    class KeyboardAxisType
    {
    public:
        bool operator<(const KeyboardAxisType &rhs) const
        {
            return std::tie(Motion1, Motion2) < std::tie(rhs.Motion1, rhs.Motion2);
        }

        bool operator==(const KeyboardAxisType &rhs) const
        {
            return Motion1 == rhs.Motion1 && Motion2 == rhs.Motion2;
        }

        enum KeyboardAxisRange
        {
            POSITIVE,
            NEGATIVE,
            FULL
        };

        struct KeyboardPartAxis
        {
            bool operator<(const KeyboardPartAxis &rhs) const
            {
                return std::tie(Button, Range) < std::tie(rhs.Button, rhs.Range);
            }

            bool operator==(const KeyboardPartAxis &rhs) const
            {
                return Button == rhs.Button && Range == rhs.Range;
            }

            KeyboardButtonType Button;
            KeyboardAxisRange Range;
        } Motion1{}, Motion2{};
    };

    /// KeyboardStick
    class KeyboardStickType
    {
    public:
        bool operator<(const KeyboardStickType &rhs) const
        {
            return std::tie(Horizontal, Vertical) < std::tie(rhs.Horizontal, rhs.Vertical);
        }

        bool operator==(const KeyboardStickType &rhs) const
        {
            return Horizontal == rhs.Horizontal && Vertical == rhs.Vertical;
        }

        KeyboardAxisType Horizontal;
        KeyboardAxisType Vertical;
    };

    /// GamepadStick
    class GamepadStickType
    {
#define GAMEPAD_STICK_LIST(E) \
E(STICK_LEFT) \
E(STICK_RIGHT) \
E(Count) \
E(STICK_NONE)

public:
        enum GamepadStickEnum
        {
#define GAMEPAD_STICK_DEF(name) name,
            GAMEPAD_STICK_LIST(GAMEPAD_STICK_DEF)
#undef GAMEPAD_STICK_DEF
        };

        GamepadStickType() = default;

        constexpr GamepadStickType(GamepadStickEnum enumValue) : value(enumValue)
        {}

        // prevent using as a pointer or boolean operator
        void *operator new(std::size_t) = delete;

        void *operator new[](std::size_t) = delete;

        void operator delete(void *p) = delete;

        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator GamepadStickEnum() const
        { return value; }

#define GAMEPAD_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char *c_str()
        {
            switch (value)
            {
                GAMEPAD_STICK_LIST(GAMEPAD_STRING_DEF)
                default:
                    return "GamepadStick Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                GAMEPAD_STICK_LIST(GAMEPAD_STRING_DEF)
                default:
                    return "GamepadStick Unknown";
            }
        }

#undef GAMEPAD_STRING_DEF

    private:
        GamepadStickEnum value;
#undef GAMEPAD_STICK_LIST
    };

    /// GamepadButton
    class GamepadButtonType
    {
#define GAMEPAD_BUTTON_LIST(E) \
E(BUTTON_A) \
E(BUTTON_B) \
E(BUTTON_X) \
E(BUTTON_Y) \
E(BUTTON_BACK) \
E(BUTTON_GUIDE) \
E(BUTTON_START) \
E(BUTTON_LEFT_STICK) \
E(BUTTON_RIGHT_STICK) \
E(BUTTON_LEFT_SHOULDER) \
E(BUTTON_RIGHT_SHOULDER) \
E(BUTTON_DPAD_UP) \
E(BUTTON_DPAD_DOWN) \
E(BUTTON_DPAD_LEFT) \
E(BUTTON_DPAD_RIGHT) \
E(Count) \
E(BUTTON_NONE)
    public:
        enum GamepadButtonEnum
        {
#define GAMEPAD_BUTTON_DEF(name) name,
            GAMEPAD_BUTTON_LIST(GAMEPAD_BUTTON_DEF)
#undef GAMEPAD_BUTTON_DEF
        };

        GamepadButtonType() = default;

        constexpr GamepadButtonType(GamepadButtonEnum enumValue) : value(enumValue)
        {}

        // prevent using as a pointer or boolean operator
        void *operator new(std::size_t) = delete;

        void *operator new[](std::size_t) = delete;

        void operator delete(void *p) = delete;

        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator GamepadButtonEnum() const
        { return value; }

#define GAMEPAD_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char *c_str()
        {
            switch (value)
            {
                GAMEPAD_BUTTON_LIST(GAMEPAD_STRING_DEF)
                default:
                    return "GamepadButton Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                GAMEPAD_BUTTON_LIST(GAMEPAD_STRING_DEF)
                default:
                    return "GamepadButton Unknown";
            }
        }

#undef GAMEPAD_STRING_DEF

    private:
        GamepadButtonEnum value;
#undef GAMEPAD_BUTTON_LIST
    };

    /// GamepadAxis
    class GamepadAxisType
    {
#define GAMEPAD_AXIS_LIST(E) \
E(AXIS_LEFT_X)  \
E(AXIS_LEFT_Y)  \
E(AXIS_RIGHT_X) \
E(AXIS_RIGHT_Y) \
E(TRIGGER_LEFT) \
E(TRIGGER_RIGHT)\
E(Count)        \
E(AXIS_NONE)
    public:
        enum GamepadAxisEnum
        {
#define GAMEPAD_AXIS_DEF(name) name,
            GAMEPAD_AXIS_LIST(GAMEPAD_AXIS_DEF)
#undef GAMEPAD_AXIS_DEF
        };

        GamepadAxisType() = default;

        constexpr GamepadAxisType(GamepadAxisEnum enumValue) : value(enumValue)
        {}

        // prevent using as a pointer or boolean operator
        void *operator new(std::size_t) = delete;

        void *operator new[](std::size_t) = delete;

        void operator delete(void *p) = delete;

        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator GamepadAxisEnum() const
        { return value; }

#define GAMEPAD_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char *c_str()
        {
            switch (value)
            {
                GAMEPAD_AXIS_LIST(GAMEPAD_STRING_DEF)
                default:
                    return "GamepadAxis Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                GAMEPAD_AXIS_LIST(GAMEPAD_STRING_DEF)
                default:
                    return "GamepadAxis Unknown";
            }
        }

#undef GAMEPAD_STRING_DEF

    private:
        GamepadAxisEnum value;
#undef GAMEPAD_AXIS_LIST
    };

#pragma endregion Enum Input Types

#pragma region Enum Event Trigger Types

    /// InputAnalogEventTrigger. Used for triggers on analog range value [-1, 1]
    class InputAnalogEventTrigger
    {
#define INPUT_STICK_EVENT_TRIGGER_LIST(E) \
E(MOVEMENT) \
E(FULL_POSITIVE) \
E(FULL_NEGATIVE) \
E(CONTINUOUS)

    public:
        enum InputAnalogEventTriggerEnum
        {
#define INPUT_STICK_EVENT_TRIGGER_DEF(name) name,
            INPUT_STICK_EVENT_TRIGGER_LIST(INPUT_STICK_EVENT_TRIGGER_DEF)
#undef INPUT_STICK_EVENT_TRIGGER_DEF
        };

        InputAnalogEventTrigger() = default;

        [[maybe_unused]] constexpr InputAnalogEventTrigger(InputAnalogEventTriggerEnum enumValue) : value(enumValue)
        {}

        // prevent using as a pointer or boolean operator
        void *operator new(std::size_t) = delete;

        void *operator new[](std::size_t) = delete;

        void operator delete(void *p) = delete;

        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator InputAnalogEventTriggerEnum() const
        { return value; }

#define GAMEPAD_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char *c_str()
        {
            switch (value)
            {
                INPUT_STICK_EVENT_TRIGGER_LIST(GAMEPAD_STRING_DEF)
                default:
                    return "InputAxisEventTrigger Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                INPUT_STICK_EVENT_TRIGGER_LIST(GAMEPAD_STRING_DEF)
                default:
                    return "InputAxisEventTrigger Unknown";
            }
        }

#undef GAMEPAD_STRING_DEF

    private:
        InputAnalogEventTriggerEnum value;

#undef INPUT_STICK_EVENT_TRIGGER_LIST
    };

    /// InputButtonEventTrigger. Used for triggers on digital value (true, false)
    class InputDigitalEventTrigger
    {
#define INPUT_BUTTON_EVENT_TRIGGER_LIST(E) \
E(JUST_PRESSED) \
E(JUST_RELEASED) \
E(HOLDING_DOWN) \
E(UP)
// HOLD, LONG_PRESS, etc.

    public:
        enum InputButtonEventTriggerEnum
        {
#define INPUT_BUTTON_EVENT_TRIGGER_DEF(name) name,
            INPUT_BUTTON_EVENT_TRIGGER_LIST(INPUT_BUTTON_EVENT_TRIGGER_DEF)
#undef INPUT_BUTTON_EVENT_TRIGGER_DEF
        };

        InputDigitalEventTrigger() = default;

        [[maybe_unused]] constexpr InputDigitalEventTrigger(InputButtonEventTriggerEnum enumValue) : value(enumValue)
        {}

        // prevent using as a pointer or boolean operator
        void *operator new(std::size_t) = delete;

        void *operator new[](std::size_t) = delete;

        void operator delete(void *p) = delete;

        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator InputButtonEventTriggerEnum() const
        { return value; }

#define GAMEPAD_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char *c_str()
        {
            switch (value)
            {
                INPUT_BUTTON_EVENT_TRIGGER_LIST(GAMEPAD_STRING_DEF)
                default:
                    return "InputButtonEventTrigger Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                INPUT_BUTTON_EVENT_TRIGGER_LIST(GAMEPAD_STRING_DEF)
                default:
                    return "InputButtonEventTrigger Unknown";
            }
        }

#undef GAMEPAD_STRING_DEF

    private:
        InputButtonEventTriggerEnum value;

#undef INPUT_BUTTON_EVENT_TRIGGER_LIST
    };

#pragma endregion Enum Event Trigger Types

#pragma region Struct Event Pair (Trigger/Input)

    struct InputMouseButtonEvent
    {
        InputDigitalEventTrigger ButtonTrigger{};
        MouseButtonType Button{};
    };

    struct InputMouseAxisEvent
    {
        InputAnalogEventTrigger AxisTrigger{};
        MouseAxisType Axis{};
    };

    struct InputMouseStickEvent
    {
        InputAnalogEventTrigger StickTrigger{};
        MouseStickType Stick{};
    };

    struct InputKeyboardButtonEvent
    {
        InputDigitalEventTrigger ButtonTrigger{};
        KeyboardButtonType Button{};
    };

    struct InputKeyboardAxisEvent
    {
        InputAnalogEventTrigger AxisTrigger{};
        KeyboardAxisType Axis{};
    };

    struct InputKeyboardStickEvent
    {
        InputAnalogEventTrigger StickTrigger{};
        KeyboardStickType Stick{};
    };

    struct InputGamepadButtonEvent
    {
        InputDigitalEventTrigger ButtonTrigger{};
        GamepadButtonType Button{};
    };

    struct InputGamepadAxisEvent
    {
        InputAnalogEventTrigger AxisTrigger{};
        GamepadAxisType Axis{};
    };

    struct InputGamepadStickEvent
    {
        InputAnalogEventTrigger StickTrigger{};
        GamepadStickType Stick{};
    };

#pragma endregion Struct Event Pair (Trigger/Input)

    /// Possible event types supported
    /// Current support is Gamepad, Keyboard, and Mouse
    enum class InputEventType
    {
        GamepadButtonEventType,
        GamepadAxisEventType,
        GamepadStickEventType,
        KeyboardButtonEventType,
        KeyboardAxisEventType,
        KeyboardStickEventType,
        MouseButtonEventType,
        MouseAxisEventType,
        MouseStickEventType,
    };

    /// Active Event type used
    union SpecificInputEvent
    {
        InputKeyboardButtonEvent KeyboardButtonEvent;
        InputKeyboardStickEvent KeyboardStickEvent;
        InputKeyboardAxisEvent KeyboardAxisEvent;
        InputGamepadButtonEvent GamepadButtonEvent;
        InputGamepadStickEvent GamepadStickEvent;
        InputGamepadAxisEvent GamepadAxisEvent;
        InputMouseButtonEvent MouseButtonEvent;
        InputMouseStickEvent MouseStickEvent;
        InputMouseAxisEvent MouseAxisEvent;
    };

    /// Axis Type
    /// Represents an axis on a controller (Gamepad, Mouse, Keyboard)
    union AxisType
    {
        GamepadAxisType GamepadAxis;
        KeyboardAxisType KeyboardAxis;
        MouseAxisType MouseAxis;

        operator GamepadAxisType() const { return GamepadAxis; }
        operator KeyboardAxisType() const { return KeyboardAxis; }
        operator MouseAxisType() const { return MouseAxis; }
    };

    /// Stick Type
    /// Represents a stick on a controller (Gamepad, Mouse, Keyboard)
    union StickType
    {
        class MouseStickType MouseStick;
        class KeyboardStickType KeyboardStick;
        class GamepadStickType GamepadStick;

        operator MouseStickType() const { return MouseStick; }
        operator KeyboardStickType() const { return KeyboardStick; }
        operator GamepadStickType() const { return GamepadStick; }
    };

    /// Button Type
    /// Represents a button on a controller (Gamepad, Mouse, Keyboard)
    union ButtonType
    {
        class MouseButtonType MouseButton;
        class GamepadButtonType GamepadButton;
        class KeyboardButtonType KeyboardButton;

        operator MouseButtonType() const { return MouseButton; }
        operator GamepadButtonType() const { return GamepadButton; }
        operator KeyboardButtonType() const { return KeyboardButton; }
    };

    /// Input Vector
    /// Represents a pair of Axis.
    /// It is a pair of floats representing the horizontal and vertical movement.
    struct InputVector
    {
        float Horizontal;
        float Vertical;
    };

    /// Input Event
    /// Describes the Axis with the current state and the Type of the Axis (Gamepad::LEFT_TRIGGER, Mouse::WHEEL, etc)
    /// You must know the Controller type to consult the AxisType
    struct Axis
    {
        AxisType AxisType;
        float Value;

        operator float() const
        { return Value; }
    };

    /// Input Stick
    /// Describes the Stick with the current state and the Type of the Stick (Gamepad::LEFT_STICK, Mouse::MOVEMENT, etc)
    /// You must know the Controller type to consult the StickType
    struct Stick
    {
        StickType StickType;
        InputVector Value;

        operator InputVector() const
        { return Value; }
    };

    /// Input Button
    /// Describes the Button with the current state and the Type of the Button (Gamepad::X, Keyboard::A, Mouse::Left, etc)
    /// You must know the Controller type to consult the ButtonType
    struct Button
    {
        ButtonType ButtonType;
        bool Pressed;

        operator bool() const
        { return Pressed; }
    };

    /// Input Type
    /// Input Type can be three:
    /// 1. Button - This is a digital input, it can be pressed or released.
    /// 2. Axis - This is an analog input. Represents one axis [-1, 1]. Some axis might have a constraint to [0, 1] - Can be one direction of a gamepad stick, a gamepad trigger, or a mouse wheel, etc.
    /// 3. Stick - This is an Axis pair. It represents a Stick on a controller. It can be used to represent a mouse cursor movement, or a gamepad stick.
    enum struct InputType
    {
        BUTTON,
        AXIS,
        STICK
    };

    /// Controller Type
    /// Input controller describes the physical device that is being interacted with.
    enum struct InputControllerType
    {
        KEYBOARD,
        MOUSE,
        GAMEPAD
    };

    /// Input State Value
    /// This represents the current value for an Input. It can be a Button, Axis or Stick (the three possible supported inputs).
    union InputStateValue
    {
        Button Button {};
        Stick Stick;
        Axis Axis;

        operator struct Button() const { return Button; }
        operator struct Stick() const { return Stick; }
        operator struct Axis() const { return Axis; }
    };

    /// The input state for the action performed (Button, Stick or Axis)
    /// This is the result of an EventTrigger process
    /// To proper use it, check the InputType and get the appropriate InputStateValue (If Type is Button, read the Input Value for Button, and so on)
    struct InputState
    {
        InputType Type {};
        InputStateValue Input {};
        InputControllerType ControllerType {};
    };

    /// The result of an Event Trigger processed
    /// The Result is only valid if "IsActive" is true. It will be false if the controller is inactive.
    /// This is the result of an EventTrigger process
    struct InputResult
    {
        bool IsActive {};
        InputState InputState {};
    };

    /// The Input Trigger description
    /// This is used to map what the Input Event should look like to trigger a specific action
    struct InputTrigger
    {
        SpecificInputEvent Event{};
        InputEventType EventType{};

        bool operator <(const InputTrigger& rhs) const
        {
            switch (EventType) {
                case InputEventType::GamepadButtonEventType:
                    return std::tie(EventType,
                             Event.GamepadButtonEvent.Button,
                             Event.GamepadButtonEvent.ButtonTrigger) <
                           std::tie(rhs.EventType,
                             rhs.Event.GamepadButtonEvent.Button,
                             rhs.Event.GamepadButtonEvent.ButtonTrigger);
                case InputEventType::GamepadAxisEventType:
                    return std::tie(EventType,
                                    Event.GamepadAxisEvent.AxisTrigger,
                                    Event.GamepadAxisEvent.Axis) <
                           std::tie(rhs.EventType,
                                    rhs.Event.GamepadAxisEvent.AxisTrigger,
                                    rhs.Event.GamepadAxisEvent.Axis);
                case InputEventType::GamepadStickEventType:
                    return std::tie(EventType,
                                    Event.GamepadStickEvent.StickTrigger,
                                    Event.GamepadStickEvent.Stick) <
                           std::tie(rhs.EventType,
                                    rhs.Event.GamepadStickEvent.StickTrigger,
                                    rhs.Event.GamepadStickEvent.Stick);
                case InputEventType::KeyboardButtonEventType:
                    return std::tie(EventType,
                                    Event.KeyboardButtonEvent.ButtonTrigger,
                                    Event.KeyboardButtonEvent.Button) <
                           std::tie(rhs.EventType,
                                    rhs.Event.KeyboardButtonEvent.ButtonTrigger,
                                    rhs.Event.KeyboardButtonEvent.Button);
                case InputEventType::KeyboardAxisEventType:
                    return std::tie(EventType,
                                    Event.KeyboardAxisEvent.AxisTrigger,
                                    Event.KeyboardAxisEvent.Axis) <
                           std::tie(rhs.EventType,
                                    rhs.Event.KeyboardAxisEvent.AxisTrigger,
                                    rhs.Event.KeyboardAxisEvent.Axis);
                case InputEventType::KeyboardStickEventType:
                    return std::tie(EventType,
                                    Event.KeyboardStickEvent.StickTrigger,
                                    Event.KeyboardStickEvent.Stick) <
                           std::tie(rhs.EventType,
                                    rhs.Event.KeyboardStickEvent.StickTrigger,
                                    rhs.Event.KeyboardStickEvent.Stick);
                case InputEventType::MouseButtonEventType:
                    return std::tie(EventType,
                                    Event.MouseButtonEvent.ButtonTrigger,
                                    Event.MouseButtonEvent.Button) <
                           std::tie(rhs.EventType,
                                    rhs.Event.MouseButtonEvent.ButtonTrigger,
                                    rhs.Event.MouseButtonEvent.Button);
                case InputEventType::MouseAxisEventType:
                    return std::tie(EventType,
                                    Event.MouseAxisEvent.AxisTrigger,
                                    Event.MouseAxisEvent.Axis) <
                           std::tie(rhs.EventType,
                                    rhs.Event.MouseAxisEvent.AxisTrigger,
                                    rhs.Event.MouseAxisEvent.Axis);
                case InputEventType::MouseStickEventType:
                    return std::tie(EventType,
                                    Event.MouseStickEvent.StickTrigger,
                                    Event.MouseStickEvent.Stick) <
                           std::tie(rhs.EventType,
                                    rhs.Event.MouseStickEvent.StickTrigger,
                                    rhs.Event.MouseStickEvent.Stick);
            }
            assert(false && "No input event type verified");
        }
        bool operator ==(const InputTrigger& rhs) const
        {
            switch (EventType) {
                case InputEventType::GamepadButtonEventType:
                    return std::tie(EventType,
                                    Event.GamepadButtonEvent.Button,
                                    Event.GamepadButtonEvent.ButtonTrigger) ==
                           std::tie(rhs.EventType,
                                    rhs.Event.GamepadButtonEvent.Button,
                                    rhs.Event.GamepadButtonEvent.ButtonTrigger);
                case InputEventType::GamepadAxisEventType:
                    return std::tie(EventType,
                                    Event.GamepadAxisEvent.AxisTrigger,
                                    Event.GamepadAxisEvent.Axis) ==
                           std::tie(rhs.EventType,
                                    rhs.Event.GamepadAxisEvent.AxisTrigger,
                                    rhs.Event.GamepadAxisEvent.Axis);
                case InputEventType::GamepadStickEventType:
                    return std::tie(EventType,
                                    Event.GamepadStickEvent.StickTrigger,
                                    Event.GamepadStickEvent.Stick) ==
                           std::tie(rhs.EventType,
                                    rhs.Event.GamepadStickEvent.StickTrigger,
                                    rhs.Event.GamepadStickEvent.Stick);
                case InputEventType::KeyboardButtonEventType:
                    return std::tie(EventType,
                                    Event.KeyboardButtonEvent.ButtonTrigger,
                                    Event.KeyboardButtonEvent.Button) ==
                           std::tie(rhs.EventType,
                                    rhs.Event.KeyboardButtonEvent.ButtonTrigger,
                                    rhs.Event.KeyboardButtonEvent.Button);
                case InputEventType::KeyboardAxisEventType:
                    return std::tie(EventType,
                                    Event.KeyboardAxisEvent.AxisTrigger,
                                    Event.KeyboardAxisEvent.Axis) ==
                           std::tie(rhs.EventType,
                                    rhs.Event.KeyboardAxisEvent.AxisTrigger,
                                    rhs.Event.KeyboardAxisEvent.Axis);
                case InputEventType::KeyboardStickEventType:
                    return std::tie(EventType,
                                    Event.KeyboardStickEvent.StickTrigger,
                                    Event.KeyboardStickEvent.Stick) ==
                           std::tie(rhs.EventType,
                                    rhs.Event.KeyboardStickEvent.StickTrigger,
                                    rhs.Event.KeyboardStickEvent.Stick);
                case InputEventType::MouseButtonEventType:
                    return std::tie(EventType,
                                    Event.MouseButtonEvent.ButtonTrigger,
                                    Event.MouseButtonEvent.Button) ==
                           std::tie(rhs.EventType,
                                    rhs.Event.MouseButtonEvent.ButtonTrigger,
                                    rhs.Event.MouseButtonEvent.Button);
                case InputEventType::MouseAxisEventType:
                    return std::tie(EventType,
                                    Event.MouseAxisEvent.AxisTrigger,
                                    Event.MouseAxisEvent.Axis) ==
                           std::tie(rhs.EventType,
                                    rhs.Event.MouseAxisEvent.AxisTrigger,
                                    rhs.Event.MouseAxisEvent.Axis);
                case InputEventType::MouseStickEventType:
                    return std::tie(EventType,
                                    Event.MouseStickEvent.StickTrigger,
                                    Event.MouseStickEvent.Stick) ==
                           std::tie(rhs.EventType,
                                    rhs.Event.MouseStickEvent.StickTrigger,
                                    rhs.Event.MouseStickEvent.Stick);
            }
            assert(false && "No input event type verified");
        }
    };
}

// To compute HASH for InputTrigger, so it can be used in unordered_map (if needed).
// use the Action name as HASH
template <>
struct std::hash<Sparkle::InputTrigger>
{
    template <typename T, typename... Rest>
    inline void HashCombine(std::size_t &seed, T const &v, Rest &&... rest) const
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        // trick to emulate a fold expression (available in C++17) in C++11
        // answer on https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x by Henri Mencke
        int i[] = {0, (HashCombine(seed, std::forward<Rest>(rest)), 0)...};
        (void)(i);
    }

    std::size_t operator()(const Sparkle::InputTrigger& k) const
    {
        using std::size_t;
        using std::hash;
        using std::string;
        std::size_t h = 0;
        switch (k.EventType) {
            case Sparkle::InputEventType::GamepadButtonEventType:
                HashCombine(h,
                            (int)k.EventType,
                            (int)k.Event.GamepadButtonEvent.Button,
                            (int)k.Event.GamepadButtonEvent.ButtonTrigger);
                return h;
            case Sparkle::InputEventType::GamepadAxisEventType:
                HashCombine(h,
                            (int)k.EventType,
                            (int)k.Event.GamepadAxisEvent.Axis,
                            (int)k.Event.GamepadAxisEvent.AxisTrigger);
                return h;
            case Sparkle::InputEventType::GamepadStickEventType:
                HashCombine(h,
                            (int)k.EventType,
                            (int)k.Event.GamepadStickEvent.Stick,
                            (int)k.Event.GamepadStickEvent.StickTrigger);
                return h;
            case Sparkle::InputEventType::KeyboardButtonEventType:
                HashCombine(h,
                            (int)k.EventType,
                            (int)k.Event.KeyboardButtonEvent.Button,
                            (int)k.Event.KeyboardButtonEvent.ButtonTrigger);
                return h;
            case Sparkle::InputEventType::KeyboardAxisEventType:
                HashCombine(h,
                            (int)k.EventType,
                            (int)k.Event.KeyboardAxisEvent.AxisTrigger,
                            (int)k.Event.KeyboardAxisEvent.Axis.Motion1.Range,
                            (int)k.Event.KeyboardAxisEvent.Axis.Motion1.Button,
                            (int)k.Event.KeyboardAxisEvent.Axis.Motion2.Range,
                            (int)k.Event.KeyboardAxisEvent.Axis.Motion2.Button);
                return h;
            case Sparkle::InputEventType::KeyboardStickEventType:
                HashCombine(h,
                            (int)k.EventType,
                            (int)k.Event.KeyboardStickEvent.StickTrigger,
                            (int)k.Event.KeyboardStickEvent.Stick.Vertical.Motion1.Range,
                            (int)k.Event.KeyboardStickEvent.Stick.Vertical.Motion1.Button,
                            (int)k.Event.KeyboardStickEvent.Stick.Vertical.Motion2.Range,
                            (int)k.Event.KeyboardStickEvent.Stick.Vertical.Motion2.Button,
                            (int)k.Event.KeyboardStickEvent.Stick.Horizontal.Motion1.Range,
                            (int)k.Event.KeyboardStickEvent.Stick.Horizontal.Motion1.Button,
                            (int)k.Event.KeyboardStickEvent.Stick.Horizontal.Motion2.Range,
                            (int)k.Event.KeyboardStickEvent.Stick.Horizontal.Motion2.Button);
                return h;
            case Sparkle::InputEventType::MouseButtonEventType:
                HashCombine(h,
                            (int)k.EventType,
                            (int)k.Event.MouseButtonEvent.Button,
                            (int)k.Event.MouseButtonEvent.ButtonTrigger);
                return h;
            case Sparkle::InputEventType::MouseAxisEventType:
                HashCombine(h,
                            (int)k.EventType,
                            (int)k.Event.GamepadAxisEvent.AxisTrigger,
                            (int)k.Event.GamepadAxisEvent.Axis);
                return h;
            case Sparkle::InputEventType::MouseStickEventType:
                HashCombine(h,
                            (int)k.EventType,
                            (int)k.Event.GamepadStickEvent.StickTrigger,
                            (int)k.Event.GamepadStickEvent.Stick);
                return h;
        }
    }
};

#endif //SPARKLE_SOLUTION_INPUT_EVENT_H

#pragma clang diagnostic pop