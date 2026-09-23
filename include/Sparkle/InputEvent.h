#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
//
// Created by z3r0_ on 10/01/2024.
//

#ifndef SPARKLE_SOLUTION_INPUT_EVENT_H
#define SPARKLE_SOLUTION_INPUT_EVENT_H

#include "Sparkle/Util/EnumTypeTemplate.h"
#include <string>
#include <cassert>
#include <utility>
#include <variant>

namespace Sparkle
{
    // Input related ENUMS transformed into CLASSES for convenient methods like c_str() and implicit string conversion
    // They should be used (and enforced to be used) as ENUMS

#pragma region Enum Input Types

#define MOUSE_BUTTON_LIST(E) \
E(BUTTON_NONE) \
E(BUTTON_LEFT) \
E(BUTTON_MIDDLE) \
E(BUTTON_RIGHT) \
E(BUTTON_X1) \
E(BUTTON_X2) \
E(Count)
DEFINE_ENUM_TYPE(MouseButtonType, MOUSE_BUTTON_LIST)
#undef MOUSE_BUTTON_LIST

#define MOUSE_AXIS_LIST(E) \
E(AXIS_X) \
E(AXIS_Y) \
E(SCROLL_WHEEL_Y) \
E(SCROLL_WHEEL_X) \
E(Count) \
E(AXIS_NONE)
DEFINE_ENUM_TYPE(MouseAxisType, MOUSE_AXIS_LIST)
#undef MOUSE_AXIS_LIST

#define MOUSE_STICK_LIST(E) \
E(MOUSE_MOVEMENT) \
E(Count)
DEFINE_ENUM_TYPE(MouseStickType, MOUSE_STICK_LIST)
#undef MOUSE_STICK_LIST

#pragma region Keyboard

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
DEFINE_ENUM_TYPE(KeyboardButtonType, KEYBOARD_BUTTON_LIST)
#undef KEYBOARD_BUTTON_LIST

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

#pragma endregion

#define GAMEPAD_STICK_LIST(E) \
E(STICK_LEFT) \
E(STICK_RIGHT) \
E(Count) \
E(STICK_NONE)
DEFINE_ENUM_TYPE(GamepadStickType, GAMEPAD_STICK_LIST)
#undef GAMEPAD_STICK_LIST

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
DEFINE_ENUM_TYPE(GamepadButtonType, GAMEPAD_BUTTON_LIST)
#undef GAMEPAD_BUTTON_LIST

#define GAMEPAD_AXIS_LIST(E) \
E(AXIS_LEFT_X)  \
E(AXIS_LEFT_Y)  \
E(AXIS_RIGHT_X) \
E(AXIS_RIGHT_Y) \
E(TRIGGER_LEFT) \
E(TRIGGER_RIGHT)\
E(Count)        \
E(AXIS_NONE)
DEFINE_ENUM_TYPE(GamepadAxisType, GAMEPAD_AXIS_LIST)
#undef GAMEPAD_AXIS_LIST

#pragma endregion Enum Input Types

#pragma region Enum Event Trigger Types

#define INPUT_STICK_EVENT_TRIGGER_LIST(E) \
E(MOVEMENT) \
E(FULL_POSITIVE) \
E(FULL_NEGATIVE) \
E(CONTINUOUS)
DEFINE_ENUM_TYPE(InputAnalogEventTrigger, INPUT_STICK_EVENT_TRIGGER_LIST)
#undef INPUT_STICK_EVENT_TRIGGER_LIST

#define INPUT_BUTTON_EVENT_TRIGGER_LIST(E) \
E(JUST_PRESSED) \
E(JUST_RELEASED) \
E(HOLDING_DOWN) \
E(UP)
// HOLD, LONG_PRESS, etc.
DEFINE_ENUM_TYPE(InputDigitalEventTrigger, INPUT_BUTTON_EVENT_TRIGGER_LIST)

#pragma endregion Enum Event Trigger Types

#pragma region Struct Event Pair (Trigger/Input)

#define InputButtonEvent(ClassName, ButtonType)                                             \
struct ClassName                                                                            \
{                                                                                           \
    InputDigitalEventTrigger ButtonTrigger{};                                               \
    ButtonType Button{};                                                                    \
                                                                                            \
    bool operator<(const ClassName& rhs) const                                              \
    { return std::tie(ButtonTrigger, Button) < std::tie(rhs.ButtonTrigger, rhs.Button); }   \
    bool operator==(const ClassName& rhs) const = default;                                  \
};                                                                                          \
                                                                                            \

#define InputAxisEvent(ClassName, AxisType)                                                 \
struct ClassName                                                                            \
{                                                                                           \
    InputAnalogEventTrigger AxisTrigger{};                                                  \
    AxisType Axis{};                                                                        \
                                                                                            \
    bool operator<(const ClassName& rhs) const                                              \
    { return std::tie(AxisTrigger, Axis) < std::tie(rhs.AxisTrigger, rhs.Axis); }           \
    bool operator==(const ClassName& rhs) const = default;                                  \
};                                                                                          \
                                                                                            \

#define InputStickEvent(ClassName, StickType)                                                \
struct ClassName                                                                            \
{                                                                                           \
    InputAnalogEventTrigger StickTrigger{};                                                 \
    StickType Stick{};                                                                      \
                                                                                            \
    bool operator<(const ClassName& rhs) const                                              \
    { return std::tie(StickTrigger, Stick) < std::tie(rhs.StickTrigger, rhs.Stick); }       \
    bool operator==(const ClassName& rhs) const = default;                                  \
};                                                                                          \
                                                                                            \

    InputButtonEvent(InputMouseButtonEvent, MouseButtonType);
    InputButtonEvent(InputKeyboardButtonEvent, KeyboardButtonType);
    InputButtonEvent(InputGamepadButtonEvent, GamepadButtonType);

    InputAxisEvent(InputMouseAxisEvent, MouseAxisType);
    InputAxisEvent(InputKeyboardAxisEvent, KeyboardAxisType);
    InputAxisEvent(InputGamepadAxisEvent, GamepadAxisType);

    InputStickEvent(InputMouseStickEvent, MouseStickType);
    InputStickEvent(InputKeyboardStickEvent, KeyboardStickType);
    InputStickEvent(InputGamepadStickEvent, GamepadStickType);

#undef InputButtonEvent
#undef InputAxisEvent
#undef InputStickEvent

#pragma endregion Struct Event Pair (Trigger/Input)

    /// Active Event type used
    using SpecificInputEvent = std::variant<
        InputKeyboardButtonEvent,
        InputKeyboardStickEvent,
        InputKeyboardAxisEvent,
        InputGamepadButtonEvent,
        InputGamepadStickEvent,
        InputGamepadAxisEvent,
        InputMouseButtonEvent,
        InputMouseStickEvent,
        InputMouseAxisEvent
    >;

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

        bool operator <(const InputTrigger& rhs) const
        {
            return Event < rhs.Event;
        }
        bool operator ==(const InputTrigger& rhs) const
        {
            return Event == rhs.Event;
        }
    };
}

#pragma region Input Event Hash

// To compute HASH for InputTrigger, so it can be used in unordered_map (if needed).
// use the Action name as HASH
// using hash trick to emulate a fold expression (available in C++17) in C++11
// answer on https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x by Henri Mencke
namespace Sparkle
{
    template<typename T, typename... Rest>
    inline void HashCombine(std::size_t &seed, T const &v, Rest &&... rest)
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        int i[] = {0, (HashCombine(seed, std::forward<Rest>(rest)), 0)...};
        (void) (i);
    }
}

#define DefineButtonEventHashTemplate(ClassName) \
template<> \
struct std::hash<ClassName> \
{ \
    std::size_t operator()(const ClassName& e) const \
    { \
        std::size_t h = 0; \
        Sparkle::HashCombine(h, (int)e.Button, (int)e.ButtonTrigger); \
        return h; \
    } \
};

DefineButtonEventHashTemplate(Sparkle::InputGamepadButtonEvent)
DefineButtonEventHashTemplate(Sparkle::InputMouseButtonEvent)
DefineButtonEventHashTemplate(Sparkle::InputKeyboardButtonEvent)

#undef DefineButtonEventHashTemplate

#define DefineAxisEventHashTemplate(ClassName) \
template<> \
struct std::hash<ClassName> \
{ \
    std::size_t operator()(const ClassName& e) const \
    { \
        std::size_t h = 0; \
        Sparkle::HashCombine(h, (int)e.Axis, (int)e.AxisTrigger); \
        return h; \
    } \
};

DefineAxisEventHashTemplate(Sparkle::InputGamepadAxisEvent)
DefineAxisEventHashTemplate(Sparkle::InputMouseAxisEvent)

#undef DefineStickEventHashTemplate

#define DefineStickEventHashTemplate(ClassName) \
template<> \
struct std::hash<ClassName> \
{ \
    std::size_t operator()(const ClassName& e) const \
    { \
        std::size_t h = 0; \
        Sparkle::HashCombine(h, (int)e.Stick, (int)e.StickTrigger); \
        return h; \
    } \
};

DefineStickEventHashTemplate(Sparkle::InputGamepadStickEvent)
DefineStickEventHashTemplate(Sparkle::InputMouseStickEvent)

#undef DefineStickEventHashTemplate

template<>
struct std::hash<Sparkle::InputKeyboardAxisEvent>
{
    std::size_t operator()(const Sparkle::InputKeyboardAxisEvent& e) const
    {
        std::size_t h = 0;
        Sparkle::HashCombine(h,
                             (int)e.AxisTrigger,
                             (int)e.Axis.Motion1.Range, (int)e.Axis.Motion1.Button,
                             (int)e.Axis.Motion2.Range, (int)e.Axis.Motion2.Button);
        return h;
    }
};

template <> struct std::hash<Sparkle::InputKeyboardStickEvent>
{
    std::size_t operator()(const Sparkle::InputKeyboardStickEvent& e) const
    {
        std::size_t h = 0;
        Sparkle::HashCombine(h,
                             (int)e.StickTrigger,
                             (int)e.Stick.Vertical.Motion1.Range,   (int)e.Stick.Vertical.Motion1.Button,
                             (int)e.Stick.Vertical.Motion2.Range,   (int)e.Stick.Vertical.Motion2.Button,
                             (int)e.Stick.Horizontal.Motion1.Range, (int)e.Stick.Horizontal.Motion1.Button,
                             (int)e.Stick.Horizontal.Motion2.Range, (int)e.Stick.Horizontal.Motion2.Button);
        return h;
    }
};

template <>
struct std::hash<Sparkle::InputTrigger>
{
    std::size_t operator()(const Sparkle::InputTrigger& t) const
    {
        return std::visit([&t](auto&& event) {
            std::size_t h = std::hash<std::size_t>{}(t.Event.index());
            Sparkle::HashCombine(h, std::hash<std::decay_t<decltype(event)>>{}(event));
            return h;
        }, t.Event);
    }
};

#pragma endregion

#endif //SPARKLE_SOLUTION_INPUT_EVENT_H

#pragma clang diagnostic pop