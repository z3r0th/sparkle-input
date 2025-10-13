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
        Stick axisValue = { 0, 0 };
        const std::vector<GamepadAxis>& axisAnalyses = stickAxis.at(event.Stick);
        bool triggerCallback = false;
        int i = 0;
        for (auto& axisEnum : axisAnalyses)
        {
            bool hasAxisMoved = GamepadController->HasAxisMoved(axisEnum);
            float axis = GamepadController->GetAxis(axisEnum);
            assert (i <= 1 && "Support only two axis");
            i++ == 0 ? axisValue.X = axis : axisValue.Y = axis;
            if (hasAxisMoved && event.StickTrigger == InputStickEventTrigger::MOVEMENT
                || axis >= 0.95 && event.StickTrigger == InputStickEventTrigger::FULL_POSITIVE
                || axis <= -0.95 && event.StickTrigger == InputStickEventTrigger::FULL_NEGATIVE)

            {
                triggerCallback = true;
            }
        }
        if (triggerCallback)
        {
            return InputResult{true, InputState{.Stick = axisValue}};
        }
        return InputResult{false};
    }

    InputResult GamepadButtonInputProcess::ProcessEvent(const InputGamepadButtonEvent &event)
    {
        assert(GamepadController && "GamepadController should never be NULL");
        bool isButtonJustPressed = GamepadController->IsButtonJustPressed(event.Button);
        bool isButtonJustReleased = GamepadController->IsButtonJustReleased(event.Button);
        if (isButtonJustPressed && event.ButtonTrigger == InputButtonEventTrigger::JUST_PRESSED
            || isButtonJustReleased && event.ButtonTrigger == InputButtonEventTrigger::JUST_RELEASED
            || GamepadController->IsButtonPressed(event.Button) && event.ButtonTrigger == InputButtonEventTrigger::HOLDING_DOWN
            || !GamepadController->IsButtonPressed(event.Button) && event.ButtonTrigger == InputButtonEventTrigger::UP)
        {
            return InputResult{true, InputState{.ButtonPressed = GamepadController->IsButtonPressed(event.Button)}};
        }
        return InputResult{false};
    }

    Sparkle::InputResult GamepadAxisInputProcess::ProcessEvent(const InputGamepadAxisEvent &event)
    {
        assert(GamepadController && "GamepadController should never be NULL");
        bool hasAxisMoved = GamepadController->HasAxisMoved(event.Axis);
        float axis = GamepadController->GetAxis(event.Axis);
        if (hasAxisMoved && event.AxisTrigger == InputAxisEventTrigger::MOVEMENT
            || axis >= 0.95 && event.AxisTrigger == InputAxisEventTrigger::FULL_POSITIVE
            || axis <= -0.95 && event.AxisTrigger == InputAxisEventTrigger::FULL_NEGATIVE)
        {
            return InputResult{true, InputState{.Axis = axis}};
        }
        return InputResult{false};
    }
}