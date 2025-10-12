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

    /// KeyboardButton
    class KeyboardButton
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
E(Count)
#pragma endregion Key List
    public:
        enum KeyboardButtonEnum
        {
#define KEYBOARD_BUTTON_DEF(name) name,
            KEYBOARD_BUTTON_LIST(KEYBOARD_BUTTON_DEF)
#undef KEYBOARD_BUTTON_DEF
        };

        KeyboardButton() = default;
        constexpr KeyboardButton(KeyboardButtonEnum enumValue) : value(enumValue) { }
        // prevent using as a pointer or boolean operator
        void * operator new (std::size_t) = delete;
        void * operator new[] (std::size_t) = delete;
        void operator delete (void *p) = delete;
        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator KeyboardButtonEnum() const { return value; }

#define KEYBOARD_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char* c_str() {
            switch (value)
            {
                KEYBOARD_BUTTON_LIST(KEYBOARD_STRING_DEF)
                default: return "KeyboardButton Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                KEYBOARD_BUTTON_LIST(KEYBOARD_STRING_DEF)
                default: return "KeyboardButton Unknown";
            }
        }
#undef KEYBOARD_STRING_DEF

    private:
        KeyboardButtonEnum value;
#undef KEYBOARD_BUTTON_LIST
    };

    /// KeyboardAxis
    class KeyboardAxis
    {
    public:
        bool operator <(const KeyboardAxis& rhs) const
        {
            return std::tie(Motion1, Motion2) < std::tie(rhs.Motion1, rhs.Motion2);
        }

        bool operator ==(const KeyboardAxis& rhs) const
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
            bool operator <(const KeyboardPartAxis& rhs) const
            {
                return std::tie(Button, Range) < std::tie(rhs.Button, rhs.Range);
            }
            bool operator ==(const KeyboardPartAxis& rhs) const
            {
                return Button == rhs.Button && Range == rhs.Range;
            }
            KeyboardButton Button;
            KeyboardAxisRange Range;
        } Motion1{}, Motion2{};
    };

    /// KeyboardStick
    class KeyboardStick
    {
    public:
        bool operator <(const KeyboardStick& rhs) const
        {
            return std::tie(Horizontal, Vertical) < std::tie(rhs.Horizontal, rhs.Vertical);
        }
        bool operator ==(const KeyboardStick& rhs) const
        {
            return Horizontal == rhs.Horizontal && Vertical == rhs.Vertical;
        }
        KeyboardAxis Horizontal;
        KeyboardAxis Vertical;
    };

    /// GamepadStick
    class GamepadStick
    {
#define GAMEPAD_STICK_LIST(E) \
E(STICK_LEFT) \
E(STICK_RIGHT) \
E(COUNT)
    public:
        enum GamepadStickEnum
        {
            #define GAMEPAD_STICK_DEF(name) name,
            GAMEPAD_STICK_LIST(GAMEPAD_STICK_DEF)
            #undef GAMEPAD_STICK_DEF
        };

        GamepadStick() = default;
        constexpr GamepadStick(GamepadStickEnum enumValue) : value(enumValue) { }
        // prevent using as a pointer or boolean operator
        void * operator new (std::size_t) = delete;
        void * operator new[] (std::size_t) = delete;
        void operator delete (void *p) = delete;
        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator GamepadStickEnum() const { return value; }

#define GAMEPAD_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char* c_str() {
            switch (value)
            {
                GAMEPAD_STICK_LIST(GAMEPAD_STRING_DEF)
                default: return "GamepadStick Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                GAMEPAD_STICK_LIST(GAMEPAD_STRING_DEF)
                default: return "GamepadStick Unknown";
            }
        }
#undef GAMEPAD_STRING_DEF

    private:
        GamepadStickEnum value;
#undef GAMEPAD_STICK_LIST
    };

    /// GamepadButton
    class GamepadButton
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
E(Count)
    public:
        enum GamepadButtonEnum
        {
            #define GAMEPAD_BUTTON_DEF(name) name,
            GAMEPAD_BUTTON_LIST(GAMEPAD_BUTTON_DEF)
            #undef GAMEPAD_BUTTON_DEF
        };

        GamepadButton() = default;
        constexpr GamepadButton(GamepadButtonEnum enumValue) : value(enumValue) { }
        // prevent using as a pointer or boolean operator
        void * operator new (std::size_t) = delete;
        void * operator new[] (std::size_t) = delete;
        void operator delete (void *p) = delete;
        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator GamepadButtonEnum() const { return value; }

#define GAMEPAD_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char* c_str() {
            switch (value)
            {
                GAMEPAD_BUTTON_LIST(GAMEPAD_STRING_DEF)
                default: return "GamepadButton Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                GAMEPAD_BUTTON_LIST(GAMEPAD_STRING_DEF)
                default: return "GamepadButton Unknown";
            }
        }
#undef GAMEPAD_STRING_DEF

    private:
        GamepadButtonEnum value;
#undef GAMEPAD_BUTTON_LIST
    };

    /// GamepadAxis
    class GamepadAxis
    {
#define GAMEPAD_AXIS_LIST(E) \
E(AXIS_LEFT_X) \
E(AXIS_LEFT_Y) \
E(AXIS_RIGHT_X) \
E(AXIS_RIGHT_Y) \
E(TRIGGER_LEFT) \
E(TRIGGER_RIGHT) \
E(Count)
    public:
        enum GamepadAxisEnum
        {
            #define GAMEPAD_AXIS_DEF(name) name,
            GAMEPAD_AXIS_LIST(GAMEPAD_AXIS_DEF)
            #undef GAMEPAD_AXIS_DEF
        };

        GamepadAxis() = default;
        constexpr GamepadAxis(GamepadAxisEnum enumValue) : value(enumValue) { }
        // prevent using as a pointer or boolean operator
        void * operator new (std::size_t) = delete;
        void * operator new[] (std::size_t) = delete;
        void operator delete (void *p) = delete;
        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator GamepadAxisEnum() const { return value; }

#define GAMEPAD_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char* c_str() {
            switch (value)
            {
                GAMEPAD_AXIS_LIST(GAMEPAD_STRING_DEF)
                default: return "GamepadAxis Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                GAMEPAD_AXIS_LIST(GAMEPAD_STRING_DEF)
                default: return "GamepadAxis Unknown";
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
E(FULL_NEGATIVE)
    public:
        enum InputAnalogEventTriggerEnum
        {
            #define INPUT_STICK_EVENT_TRIGGER_DEF(name) name,
            INPUT_STICK_EVENT_TRIGGER_LIST(INPUT_STICK_EVENT_TRIGGER_DEF)
            #undef INPUT_STICK_EVENT_TRIGGER_DEF
        };

        InputAnalogEventTrigger() = default;
        [[maybe_unused]] constexpr InputAnalogEventTrigger(InputAnalogEventTriggerEnum enumValue) : value(enumValue) { }
        // prevent using as a pointer or boolean operator
        void * operator new (std::size_t) = delete;
        void * operator new[] (std::size_t) = delete;
        void operator delete (void *p) = delete;
        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator InputAnalogEventTriggerEnum() const { return value; }

#define GAMEPAD_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char* c_str() {
            switch (value)
            {
                INPUT_STICK_EVENT_TRIGGER_LIST(GAMEPAD_STRING_DEF)
                default: return "InputAxisEventTrigger Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                INPUT_STICK_EVENT_TRIGGER_LIST(GAMEPAD_STRING_DEF)
                default: return "InputAxisEventTrigger Unknown";
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
        [[maybe_unused]] constexpr InputDigitalEventTrigger(InputButtonEventTriggerEnum enumValue) : value(enumValue) { }
        // prevent using as a pointer or boolean operator
        void * operator new (std::size_t) = delete;
        void * operator new[] (std::size_t) = delete;
        void operator delete (void *p) = delete;
        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator InputButtonEventTriggerEnum() const { return value; }

#define GAMEPAD_STRING_DEF(name) \
        case name: return #name;

        [[maybe_unused]] const char* c_str() {
            switch (value)
            {
                INPUT_BUTTON_EVENT_TRIGGER_LIST(GAMEPAD_STRING_DEF)
                default: return "InputButtonEventTrigger Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                INPUT_BUTTON_EVENT_TRIGGER_LIST(GAMEPAD_STRING_DEF)
                default: return "InputButtonEventTrigger Unknown";
            }
        }
#undef GAMEPAD_STRING_DEF

    private:
        InputButtonEventTriggerEnum value;

#undef INPUT_BUTTON_EVENT_TRIGGER_LIST
    };

#pragma endregion Enum Event Trigger Types

#pragma region Struct Event Pair (Trigger/Input)

    struct InputKeyboardButtonEvent
    {
        InputDigitalEventTrigger ButtonTrigger{};
        KeyboardButton Button{};
    };

    struct InputKeyboardAxisEvent
    {
        InputAnalogEventTrigger AxisTrigger{};
        KeyboardAxis Axis{};
    };

    struct InputKeyboardStickEvent
    {
        InputAnalogEventTrigger StickTrigger{};
        KeyboardStick Stick{};
    };

    struct InputGamepadButtonEvent
    {
        InputDigitalEventTrigger ButtonTrigger{};
        GamepadButton Button{};
    };

    struct InputGamepadAxisEvent
    {
        InputAnalogEventTrigger AxisTrigger{};
        GamepadAxis Axis{};
    };

    struct InputGamepadStickEvent
    {
        InputAnalogEventTrigger StickTrigger{};
        GamepadStick Stick{};
    };

#pragma endregion Struct Event Pair (Trigger/Input)

    /// Possible event types supported
    /// Current support is Gamepad and Keyboard
    enum class InputEventType
    {
        GamePadButtonEventType,
        GamePadAxisEventType,
        GamePadStickEventType,
        KeyboardButtonEventType,
        KeyboardAxisEventType,
        KeyboardStickEventType,
    };

    /// Active Event type used
    union SpecificInputEvent
    {
        InputKeyboardButtonEvent KeyboardButtonEvent;
        InputKeyboardStickEvent KeyboardStickEvent;
        InputKeyboardAxisEvent KeyboardAxisEvent;
        InputGamepadButtonEvent ButtonEvent;
        InputGamepadStickEvent StickEvent;
        InputGamepadAxisEvent AxisEvent;
    };

    /// 2D Stick value
    struct Stick
    {
        float Horizontal;
        float Vertical;
    };

    enum struct InputType
    {
        Button,
        Axis,
        Stick
    };

    union InputStateValue
    {
        bool ButtonPressed;
        Stick Stick;
        float Axis;
    };

    /// The input state for the action performed (Button, Stick or Axis)
    /// This is the result of an EventTrigger process
    struct InputState
    {
        InputType Type;
        InputStateValue Value;
    };

    /// The result of an Event Trigger processed
    struct InputResult
    {
        bool IsActive;
        InputState InputState;
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
                case InputEventType::GamePadButtonEventType:
                    return std::tie(EventType,
                             Event.ButtonEvent.Button,
                             Event.ButtonEvent.ButtonTrigger) <
                           std::tie(rhs.EventType,
                             rhs.Event.ButtonEvent.Button,
                             rhs.Event.ButtonEvent.ButtonTrigger);
                case InputEventType::GamePadAxisEventType:
                    return std::tie(EventType,
                                    Event.AxisEvent.AxisTrigger,
                                    Event.AxisEvent.Axis) <
                           std::tie(rhs.EventType,
                                    rhs.Event.AxisEvent.AxisTrigger,
                                    rhs.Event.AxisEvent.Axis);
                case InputEventType::GamePadStickEventType:
                    return std::tie(EventType,
                                    Event.StickEvent.StickTrigger,
                                    Event.StickEvent.Stick) <
                           std::tie(rhs.EventType,
                                    rhs.Event.StickEvent.StickTrigger,
                                    rhs.Event.StickEvent.Stick);
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
            }
            assert(false && "No input event type verified");
        }
        bool operator ==(const InputTrigger& rhs) const
        {
            switch (EventType) {
                case InputEventType::GamePadButtonEventType:
                    return std::tie(EventType,
                                    Event.ButtonEvent.Button,
                                    Event.ButtonEvent.ButtonTrigger) ==
                           std::tie(rhs.EventType,
                                    rhs.Event.ButtonEvent.Button,
                                    rhs.Event.ButtonEvent.ButtonTrigger);
                case InputEventType::GamePadAxisEventType:
                    return std::tie(EventType,
                                    Event.AxisEvent.AxisTrigger,
                                    Event.AxisEvent.Axis) ==
                           std::tie(rhs.EventType,
                                    rhs.Event.AxisEvent.AxisTrigger,
                                    rhs.Event.AxisEvent.Axis);
                case InputEventType::GamePadStickEventType:
                    return std::tie(EventType,
                                    Event.StickEvent.StickTrigger,
                                    Event.StickEvent.Stick) ==
                           std::tie(rhs.EventType,
                                    rhs.Event.StickEvent.StickTrigger,
                                    rhs.Event.StickEvent.Stick);
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
            case Sparkle::InputEventType::GamePadButtonEventType:
                HashCombine(h,
                            (int)k.EventType,
                            (int)k.Event.ButtonEvent.Button,
                            (int)k.Event.ButtonEvent.ButtonTrigger);
                return h;
            case Sparkle::InputEventType::GamePadAxisEventType:
                HashCombine(h,
                            (int)k.EventType,
                            (int)k.Event.AxisEvent.Axis,
                            (int)k.Event.AxisEvent.AxisTrigger);
                return h;
            case Sparkle::InputEventType::GamePadStickEventType:
                HashCombine(h,
                            (int)k.EventType,
                            (int)k.Event.StickEvent.Stick,
                            (int)k.Event.StickEvent.StickTrigger);
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
        }
    }
};

#endif //SPARKLE_SOLUTION_INPUT_EVENT_H

#pragma clang diagnostic pop