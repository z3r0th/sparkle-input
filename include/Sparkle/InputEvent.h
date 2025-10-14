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
//TODO: Add more keyboard button
#define KEYBOARD_BUTTON_LIST(E) \
E(UNKNOWN)                      \
E(KEY_RESERVED_1)               \
E(KEY_RESERVED_2)               \
E(KEY_RESERVED_3)               \
E(KEY_A)                        \
E(Count)

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

        const char* c_str() {
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

        const char* c_str() {
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

        const char* c_str() {
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

        const char* c_str() {
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

    /// InputStickEventTrigger
    class InputStickEventTrigger
    {
#define INPUT_STICK_EVENT_TRIGGER_LIST(E) \
E(MOVEMENT) \
E(FULL_POSITIVE) \
E(FULL_NEGATIVE)
    public:
        enum InputStickEventTriggerEnum
        {
            #define INPUT_STICK_EVENT_TRIGGER_DEF(name) name,
            INPUT_STICK_EVENT_TRIGGER_LIST(INPUT_STICK_EVENT_TRIGGER_DEF)
            #undef INPUT_STICK_EVENT_TRIGGER_DEF
        };

        InputStickEventTrigger() = default;
        [[maybe_unused]] constexpr InputStickEventTrigger(InputStickEventTriggerEnum enumValue) : value(enumValue) { }
        // prevent using as a pointer or boolean operator
        void * operator new (std::size_t) = delete;
        void * operator new[] (std::size_t) = delete;
        void operator delete (void *p) = delete;
        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator InputStickEventTriggerEnum() const { return value; }

#define GAMEPAD_STRING_DEF(name) \
        case name: return #name;

        const char* c_str() {
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
        InputStickEventTriggerEnum value;

#undef INPUT_STICK_EVENT_TRIGGER_LIST
    };

    /// InputButtonEventTrigger
    class InputButtonEventTrigger
    {
#define INPUT_BUTTON_EVENT_TRIGGER_LIST(E) \
E(JUST_PRESSED) \
E(JUST_RELEASED) \
E(HOLDING_DOWN) \
E(UP)
// HOLD, LONG_PRESS, etc

    public:
        enum InputButtonEventTriggerEnum
        {
            #define INPUT_BUTTON_EVENT_TRIGGER_DEF(name) name,
            INPUT_BUTTON_EVENT_TRIGGER_LIST(INPUT_BUTTON_EVENT_TRIGGER_DEF)
            #undef INPUT_BUTTON_EVENT_TRIGGER_DEF
        };
        InputButtonEventTrigger() = default;
        [[maybe_unused]] constexpr InputButtonEventTrigger(InputButtonEventTriggerEnum enumValue) : value(enumValue) { }
        // prevent using as a pointer or boolean operator
        void * operator new (std::size_t) = delete;
        void * operator new[] (std::size_t) = delete;
        void operator delete (void *p) = delete;
        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator InputButtonEventTriggerEnum() const { return value; }

#define GAMEPAD_STRING_DEF(name) \
        case name: return #name;

        const char* c_str() {
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

    /// InputAxisEventTrigger
    class InputAxisEventTrigger
    {
#define INPUT_AXIS_EVENT_TRIGGER_LIST(E) \
E(MOVEMENT) \
E(FULL_POSITIVE) \
E(FULL_NEGATIVE)
    public:
        enum InputAxisEventTriggerEnum
        {
            #define INPUT_AXIS_EVENT_TRIGGER_DEF(name) name,
            INPUT_AXIS_EVENT_TRIGGER_LIST(INPUT_AXIS_EVENT_TRIGGER_DEF)
            #undef INPUT_AXIS_EVENT_TRIGGER_DEF
        };

        InputAxisEventTrigger() = default;
        [[maybe_unused]] constexpr InputAxisEventTrigger(InputAxisEventTriggerEnum enumValue) : value(enumValue) { }
        // prevent using as a pointer or boolean operator
        void * operator new (std::size_t) = delete;
        void * operator new[] (std::size_t) = delete;
        void operator delete (void *p) = delete;
        explicit operator bool() const = delete;

        // Allow switch and comparisons.
        constexpr operator InputAxisEventTriggerEnum() const { return value; }

#define GAMEPAD_STRING_DEF(name) \
        case name: return #name;

        const char* c_str() {
            switch (value)
            {
                INPUT_AXIS_EVENT_TRIGGER_LIST(GAMEPAD_STRING_DEF)
                default: return "InputAxisEventTrigger Unknown";
            }
        }

        operator std::string()
        {
            switch (value)
            {
                INPUT_AXIS_EVENT_TRIGGER_LIST(GAMEPAD_STRING_DEF)
                default: return "InputAxisEventTrigger Unknown";
            }
        }
#undef GAMEPAD_STRING_DEF

    private:
        InputAxisEventTriggerEnum value;

#undef INPUT_AXIS_EVENT_TRIGGER_LIST
    };

#pragma endregion Enum Event Trigger Types

#pragma region Struct Event Pair (Trigger/Input)
    struct InputKeyboardButtonEvent
    {
        InputButtonEventTrigger ButtonTrigger{};
        KeyboardButton Button{};
    };

    struct InputGamepadButtonEvent
    {
        InputButtonEventTrigger ButtonTrigger{};
        GamepadButton Button{};
    };

    struct InputGamepadAxisEvent
    {
        InputAxisEventTrigger AxisTrigger{};
        GamepadAxis Axis{};
    };

    struct InputGamepadStickEvent
    {
        InputStickEventTrigger StickTrigger{};
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
        KeyboardButtonEventType
    };

    /// Active Event type used
    union SpecificInputEvent
    {
        InputKeyboardButtonEvent KeyboardButtonEvent;
        InputGamepadButtonEvent ButtonEvent;
        InputGamepadStickEvent StickEvent;
        InputGamepadAxisEvent AxisEvent;
    };

    /// 2D Stick value
    struct Stick
    {
        float X;
        float Y;
    };

    /// The input state for the action performed (Button, Stick or Axis)
    /// This is the result of an EventTrigger process
    // TODO: Input State must have another property to select the correct property
    union InputState
    {
        bool ButtonPressed;
        Stick Stick;
        float Axis;
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
            }
        }
    };
}

// To compute HASH for InputTrigger, so it can be used in unordered_map (if needed)
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
        // answer on https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x by Henri Menke
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
        }
    }
};

#endif //SPARKLE_SOLUTION_INPUT_EVENT_H

#pragma clang diagnostic pop