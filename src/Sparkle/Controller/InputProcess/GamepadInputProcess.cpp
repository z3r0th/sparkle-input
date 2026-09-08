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
        bool hasStickMoved = GamepadController->HasStickMoved(event.Stick);
        InputVector stickValue = GamepadController->GetStick(event.Stick);
        if (event.StickTrigger == InputAnalogEventTrigger::CONTINUOUS
            || hasStickMoved && event.StickTrigger == InputAnalogEventTrigger::MOVEMENT
            || (stickValue.Horizontal >= 0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_POSITIVE || stickValue.Vertical >= 0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_POSITIVE)
            || (stickValue.Vertical <= -0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_NEGATIVE) || (stickValue.Horizontal <= -0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_NEGATIVE))
        {
            Stick stick = {.StickType = {.GamepadStick = event.Stick}, .Value = stickValue};
            return InputResult{true, InputState{.Type=InputType::STICK, .Input={.Stick = stick}}};
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
            Button button = {.ButtonType = {.GamepadButton = event.Button}, .Pressed = GamepadController->IsButtonPressed(event.Button)};
            return InputResult{true, InputState{.Type=InputType::BUTTON, .Input={.Button = button}}};
        }
        return InputResult{false};
    }

    Sparkle::InputResult GamepadAxisInputProcess::ProcessEvent(const InputGamepadAxisEvent &event)
    {
        assert(GamepadController && "GamepadController should never be NULL");
        bool hasAxisMoved = GamepadController->HasAxisMoved(event.Axis);
        float axisValue = GamepadController->GetAxis(event.Axis);
        if (event.AxisTrigger == InputAnalogEventTrigger::CONTINUOUS
            || hasAxisMoved && event.AxisTrigger == InputAnalogEventTrigger::MOVEMENT
            || axisValue >= 0.95 && event.AxisTrigger == InputAnalogEventTrigger::FULL_POSITIVE
            || axisValue <= -0.95 && event.AxisTrigger == InputAnalogEventTrigger::FULL_NEGATIVE)
        {
            Axis axis = {.AxisType = {.GamepadAxis = event.Axis}, .Value = axisValue};
            return InputResult{true, InputState{.Type=InputType::AXIS, .Input={.Axis = axis}}};
        }
        return InputResult{false};
    }
}