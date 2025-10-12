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
        std::map<InputTrigger, InputAction> ActionTrigger{};
        std::string InputMapDescription{};
        std::string InputMapName{};

    public:


        InputMap() : InputMapDescription(), ActionTrigger{}, InputMapName(EMPTY_INPUT_MAP_NAME)
        { }

        [[maybe_unused]] explicit InputMap(std::string  mapName, std::string  mapDescription = "")
                : InputMapName(std::move(mapName)), InputMapDescription(std::move(mapDescription))
        { }

        /// Get InputMap name
        /// \return name
        [[maybe_unused]] [[nodiscard]] const std::string& GetInputMapName() const
        {
            return InputMapName;
        }

        /// Get InputMap description
        /// \return description
        [[maybe_unused]] [[nodiscard]] const std::string& GetInputMapDescription() const
        {
            return InputMapDescription;
        }

        void Bind(const KeyboardButton& button, const InputDigitalEventTrigger& trigger, const InputAction& action)
        {
            InputTrigger event = InputTrigger();
            event.EventType = InputEventType::KeyboardButtonEventType;
            event.Event.KeyboardButtonEvent.Button = button;
            event.Event.KeyboardButtonEvent.ButtonTrigger = trigger;
            ActionTrigger[event] = action;
        }

        void Bind(const KeyboardAxis& axis, const InputAnalogEventTrigger& trigger, const InputAction& action)
        {
            InputTrigger event = InputTrigger();
            event.EventType = InputEventType::KeyboardAxisEventType;
            event.Event.KeyboardAxisEvent.AxisTrigger = trigger;
            event.Event.KeyboardAxisEvent.Axis = axis;
            ActionTrigger[event] = action;
        }

        void Bind(const KeyboardStick& stick, const InputAnalogEventTrigger& trigger, const InputAction& action)
        {
            InputTrigger event = InputTrigger();
            event.EventType = InputEventType::KeyboardStickEventType;
            event.Event.KeyboardStickEvent.StickTrigger = trigger;
            event.Event.KeyboardStickEvent.Stick = stick;
            ActionTrigger[event] = action;
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
        void Bind(const GamepadButton& button, const InputDigitalEventTrigger& trigger, const InputAction& action)
        {
            InputTrigger event = InputTrigger();
            event.EventType = InputEventType::GamePadButtonEventType;
            event.Event.ButtonEvent.Button = button;
            event.Event.ButtonEvent.ButtonTrigger = trigger;
            ActionTrigger[event] = action;
        }

        /// Binds a specific GamepadStick to a specific Action through a specific Trigger
        /// You should be able to bind something like:
        ///  - If Stick_Left moves, triggers Action
        ///  - If Stick is negative, triggers Action
        ///  - etc
        /// \param stick a specific Gamepad Stick
        /// \param trigger a specific Gamepad Stick state to trigger the Action
        /// \param action a specific Action
        void Bind(const GamepadStick& stick, const InputAnalogEventTrigger& trigger, const InputAction& action)
        {
            InputTrigger event = InputTrigger();
            event.EventType = InputEventType::GamePadStickEventType;
            event.Event.StickEvent.Stick = stick;
            event.Event.StickEvent.StickTrigger = trigger;
            ActionTrigger[event] = action;
        }

        /// Binds a specific GamepadAxis to a specific Action through a specific Trigger
        /// You should be able to bind something like:
        ///  - If Axis_Left moves, triggers Action
        ///  - If Axis is negative, triggers Action
        ///  - etc
        /// \param axis a specific Gamepad Axis
        /// \param trigger a specific Gamepad Axis state to trigger the Action
        /// \param action a specific Action
        void Bind(const GamepadAxis& axis, const InputAnalogEventTrigger& trigger, const InputAction& action)
        {
            InputTrigger event = InputTrigger();
            event.EventType = InputEventType::GamePadAxisEventType;
            event.Event.AxisEvent.Axis = axis;
            event.Event.AxisEvent.AxisTrigger = trigger;
            ActionTrigger[event] = action;
        }

        /// Get all bind actions
        /// O(n) to get the actions
        /// \return actions
        [[maybe_unused]] [[nodiscard]] std::vector<InputAction> GetActions()
        {
            std::vector<InputAction> actions;
            actions.reserve(ActionTrigger.size());
            for (auto & ButtonAction : ActionTrigger)
            {
                actions.push_back(ButtonAction.second);
            }

            return actions;
        }

        /// Get all input events
        /// O(n) to get the events
        /// \return input events
        [[maybe_unused]] [[nodiscard]] std::vector<InputTrigger> GetEventsForAction(const InputAction& inputAction)
        {
            std::vector<InputTrigger> events;
            for (auto & ButtonAction : ActionTrigger)
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

#endif //SPARKLE_SOLUTION_INPUT_MAP_H
