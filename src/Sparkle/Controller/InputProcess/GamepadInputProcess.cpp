//
// Created by z3r0_ on 08/09/2025.
//

#include "GamepadInputProcess.h"

#include "Sparkle/Controller/GamepadController.h"

namespace Sparkle
{
    InputResult GamepadStickInputProcess::ProcessEvent(const InputGamepadStickEvent &event)
    {
        assert(GamepadController && "GamepadController should never be NULL");
        static const std::map<GamepadStick, const std::vector<GamepadAxis>> stickAxis =
        {
            {GamepadStick::STICK_LEFT, {GamepadAxis::AXIS_LEFT_X, GamepadAxis::AXIS_LEFT_Y}},
            {GamepadStick::STICK_RIGHT, {GamepadAxis::AXIS_RIGHT_X, GamepadAxis::AXIS_RIGHT_Y}}
        };
        Stick stickValue = {0, 0 };
        const std::vector<GamepadAxis>& axisAnalyses = stickAxis.at(event.Stick);
        bool triggerCallback = false;
        int i = 0;
        for (auto& axisEnum : axisAnalyses)
        {
            bool hasAxisMoved = GamepadController->HasAxisMoved(axisEnum);
            float axis = GamepadController->GetAxis(axisEnum);
            assert (i <= 1 && "Support only two axis");
            i++ == 0 ? stickValue.Horizontal = axis : stickValue.Vertical = axis;
            if (hasAxisMoved && event.StickTrigger == InputAnalogEventTrigger::MOVEMENT
                || axis >= 0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_POSITIVE
                || axis <= -0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_NEGATIVE)

            {
                triggerCallback = true;
            }
        }
        if (triggerCallback)
        {
            return InputResult{true, InputState{.Type=InputType::Stick, .Value={.Stick = stickValue}}};
        }
        return InputResult{false};
    }

    InputResult GamepadButtonInputProcess::ProcessEvent(const InputGamepadButtonEvent &event)
    {
        assert(GamepadController && "GamepadController should never be NULL");
        bool isButtonJustPressed = GamepadController->IsButtonJustPressed(event.Button);
        bool isButtonJustReleased = GamepadController->IsButtonJustReleased(event.Button);
        if (isButtonJustPressed && event.ButtonTrigger == InputDigitalEventTrigger::JUST_PRESSED
            || isButtonJustReleased && event.ButtonTrigger == InputDigitalEventTrigger::JUST_RELEASED
            || GamepadController->IsButtonPressed(event.Button) && event.ButtonTrigger == InputDigitalEventTrigger::HOLDING_DOWN
            || !GamepadController->IsButtonPressed(event.Button) && event.ButtonTrigger == InputDigitalEventTrigger::UP)
        {
            return InputResult{true, InputState{.Type=InputType::Button, .Value={.ButtonPressed = GamepadController->IsButtonPressed(event.Button)}}};
        }
        return InputResult{false};
    }

    Sparkle::InputResult GamepadAxisInputProcess::ProcessEvent(const InputGamepadAxisEvent &event)
    {
        assert(GamepadController && "GamepadController should never be NULL");
        bool hasAxisMoved = GamepadController->HasAxisMoved(event.Axis);
        float axis = GamepadController->GetAxis(event.Axis);
        if (hasAxisMoved && event.AxisTrigger == InputAnalogEventTrigger::MOVEMENT
            || axis >= 0.95 && event.AxisTrigger == InputAnalogEventTrigger::FULL_POSITIVE
            || axis <= -0.95 && event.AxisTrigger == InputAnalogEventTrigger::FULL_NEGATIVE)
        {
            return InputResult{true, InputState{.Type=InputType::Axis, .Value={.Axis = axis}}};
        }
        return InputResult{false};
    }
}