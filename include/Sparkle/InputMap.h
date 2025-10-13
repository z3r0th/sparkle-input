//
// Created by z3r0_ on 10/01/2024.
//

#ifndef SPARKLE_SOLUTION_INPUT_MAP_H
#define SPARKLE_SOLUTION_INPUT_MAP_H

#include <string>
#include <utility>
#include <vector>
#include <map>

#include "InputAction.h"
#include "InputEvent.h"

#define EMPTY_INPUT_MAP_NAME "EMPTY"

namespace Sparkle
{
    /// Map a physical InputType (Button, Key, Mouse, Axis) to specific InputAction
    class InputMap
    {
        friend class PlayerInputController;
    private:
        std::map<InputEvent, InputAction> ButtonActions{};
        std::string InputMapDescription{};
        std::string InputMapName{};

    public:


        InputMap() : InputMapDescription(), ButtonActions{}, InputMapName(EMPTY_INPUT_MAP_NAME)
        { }

        explicit InputMap(std::string  mapName, std::string  mapDescription = "")
                : InputMapName(std::move(mapName)), InputMapDescription(std::move(mapDescription))
        { }

        /// Get InputMap name
        /// \return name
        [[nodiscard]] const std::string& GetInputMapName() const
        {
            return InputMapName;
        }

        /// Get InputMap description
        /// \return description
        [[maybe_unused]][[nodiscard]] const std::string& GetInputMapDescription() const
        {
            return InputMapDescription;
        }

        void Bind(const KeyboardButton& button, const InputButtonEventTrigger& trigger, const InputAction& action)
        {
            InputEvent event = InputEvent();
            event.EventType = InputEventType::KeyboardButtonEventType;
            event.Event.KeyboardButtonEvent.Button = button;
            event.Event.KeyboardButtonEvent.ButtonTrigger = trigger;
            ButtonActions[event] = action;
        }
        /// Binds a specific GamepadButton to a specific Action through a specific Trigger
        /// You should be able to bind something like:
        ///  - When Button_A is pressed, triggers Action
        ///  - While Button_Y is hold, trigger Action
        ///  - When Button_X is released, trigger Action
        ///  - etc
        /// \param button a specific Gamepad Button
        /// \param trigger a specific Gamepad Button state to trigger the Action
        /// \param action a specific Action
        void Bind(const GamepadButton& button, const InputButtonEventTrigger& trigger, const InputAction& action)
        {
            InputEvent event = InputEvent();
            event.EventType = InputEventType::GamePadButtonEventType;
            event.Event.ButtonEvent.Button = button;
            event.Event.ButtonEvent.ButtonTrigger = trigger;
            ButtonActions[event] = action;
        }

        /// Binds a specific GamepadStick to a specific Action through a specific Trigger
        /// You should be able to bind something like:
        ///  - If Stick_Left moves, triggers Action
        ///  - If Stick is negative, triggers Action
        ///  - etc
        /// \param stick a specific Gamepad Stick
        /// \param trigger a specific Gamepad Stick state to trigger the Action
        /// \param action a specific Action
        void Bind(const GamepadStick& stick, const InputStickEventTrigger& trigger, const InputAction& action)
        {
            InputEvent event = InputEvent();
            event.EventType = InputEventType::GamePadStickEventType;
            event.Event.StickEvent.Stick = stick;
            event.Event.StickEvent.StickTrigger = trigger;
            ButtonActions[event] = action;
        }

        /// Binds a specific GamepadAxis to a specific Action through a specific Trigger
        /// You should be able to bind something like:
        ///  - If Axis_Left moves, triggers Action
        ///  - If Axis is negative, triggers Action
        ///  - etc
        /// \param axis a specific Gamepad Axis
        /// \param trigger a specific Gamepad Axis state to trigger the Action
        /// \param action a specific Action
        void Bind(const GamepadAxis& axis, const InputAxisEventTrigger& trigger, const InputAction& action)
        {
            InputEvent event = InputEvent();
            event.EventType = InputEventType::GamePadAxisEventType;
            event.Event.AxisEvent.Axis = axis;
            event.Event.AxisEvent.AxisTrigger = trigger;
            ButtonActions[event] = action;
        }

        /// Get all bind actions
        /// O(n) to get the actions
        /// \return actions
        std::vector<InputAction> GetActions()
        {
            std::vector<InputAction> actions;
            actions.reserve(ButtonActions.size());
            for (auto & ButtonAction : ButtonActions)
            {
                actions.push_back(ButtonAction.second);
            }

            return actions;
        }

        /// Get all input events
        /// O(n) to get the events
        /// \return input events
        std::vector<InputEvent> GetEventsForAction(const InputAction& inputAction)
        {
            std::vector<InputEvent> events;
            for (auto & ButtonAction : ButtonActions)
            {
                if (ButtonAction.second == inputAction)
                {
                    events.push_back(ButtonAction.first);
                }
            }

            return events;
        }
    };
}

// To compute HASH for InputEvent, so it can be used in unordered_map (if needed)
// use the Action name as HASH
template <>
struct std::hash<Sparkle::InputEvent>
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

    std::size_t operator()(const Sparkle::InputEvent& k) const
    {
        // TODO: Since we are using Union this can be simplified
        using std::size_t;
        using std::hash;
        using std::string;
        std::size_t h = 0;
        HashCombine(h,
                     (int)k.EventType,
                     (int)k.Event.KeyboardButtonEvent.Button,
                     (int)k.Event.KeyboardButtonEvent.ButtonTrigger,
                     (int)k.Event.ButtonEvent.Button,
                     (int)k.Event.ButtonEvent.ButtonTrigger,
                     (int)k.Event.StickEvent.Stick,
                     (int)k.Event.StickEvent.StickTrigger,
                     (int)k.Event.AxisEvent.Axis,
                     (int)k.Event.AxisEvent.AxisTrigger);
        return h;
    }
};

#endif //SPARKLE_SOLUTION_INPUT_MAP_H
