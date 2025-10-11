#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
//
// Created by z3r0_ on 10/01/2024.
//

#ifndef SPARKLE_SOLUTION_INPUT_EVENT_H
#define SPARKLE_SOLUTION_INPUT_EVENT_H

#include <string>

namespace Sparkle
{
    // Input related ENUMS transformed into CLASSES for convenient methods like c_str() and implicit string conversion
    // They should be used (and enforced to be used) as ENUMS

    /// KeyboardButton
    class KeyboardButton
    {
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
}

#endif //SPARKLE_SOLUTION_INPUT_EVENT_H

#pragma clang diagnostic pop