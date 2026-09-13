//
// Created by z3r0_ on 09/09/2026.
//

#include "Sparkle/Controller/MouseController.h"
#include "Sparkle/InputEvent.h"
#include "Sparkle/InputMap.h"
#include "Sparkle/Input.h"
#include <SDL.h>

namespace Sparkle
{

    void MouseController::Update()
    {
        int x, y;
        Uint32 buttons = SDL_GetMouseState(&x, &y);
        constexpr const float DEAD_ZONE = std::numeric_limits<float>::epsilon();

        for (unsigned int i = 0 ; i < static_cast<int>(MouseButton::Count) ; ++i)
        {
            LastButtons[i] = Buttons[i];
            Buttons[i] = buttons & SDL_BUTTON(static_cast<int>(i));
        }

        for (unsigned int i = 0 ; i < static_cast<int>(MouseAxis::Count) ; ++i)
        {
            LastAxis[i] = Axis[i];
            float axis = 0.0f;
            switch (static_cast<MouseAxis::MouseAxisEnum>(i))
            {
                case MouseAxis::MouseAxisEnum::AXIS_X:
                    axis = (float)x;
                    break;
                case MouseAxis::MouseAxisEnum::AXIS_Y:
                    axis = (float)y;
                    break;
                case MouseAxis::MouseAxisEnum::SCROLL_WHEEL_X:
                    axis = MouseWheelX;
                    break;
                case MouseAxis::MouseAxisEnum::SCROLL_WHEEL_Y:
                    axis = MouseWheelY;
                    break;
                case MouseAxis::MouseAxisEnum::AXIS_NONE:
                case MouseAxis::MouseAxisEnum::Count:
                    break;
            }
            if (abs(axis) <= DEAD_ZONE)
            {
                axis = 0.0;
            }
            Axis[i] = axis;
        }

        static const std::map<MouseStick, const std::vector<MouseAxis>> StickAxis =
        {
            {MouseStick::MOUSE_MOVEMENT, {MouseAxis::AXIS_X, MouseAxis::AXIS_Y}},
        };
        for (unsigned int i = 0 ; i < static_cast<int>(MouseStick::Count) ; ++i)
        {
            LastStick[i] = Stick[i];
            MouseStick UpdateStick = static_cast<MouseStick::MouseStickEnum>(i);
            struct InputVector stickValue = {0, 0 };
            const std::vector<MouseAxis>& axisAnalyses = StickAxis.at(UpdateStick);
            int axisIndex = 0;
            for (auto& axisEnum : axisAnalyses)
            {
                float axis = GetAxis(axisEnum);
                assert (axisIndex <= 1 && "Support only two axis");
                axisIndex++ == 0 ? stickValue.Horizontal = axis : stickValue.Vertical = axis;
            }
            Stick[i] = stickValue;
        }
    }

    InputResult MouseController::ProcessButton(const InputMouseButtonEvent &mouseEvent)
    {
        bool isButtonJustPressed = IsButtonJustPressed(mouseEvent.Button);
        bool isButtonJustReleased = IsButtonJustReleased(mouseEvent.Button);
        if (isButtonJustPressed && mouseEvent.ButtonTrigger == InputDigitalEventTrigger::JUST_PRESSED
            || isButtonJustReleased && mouseEvent.ButtonTrigger == InputDigitalEventTrigger::JUST_RELEASED
            || IsButtonPressed(mouseEvent.Button) && mouseEvent.ButtonTrigger == InputDigitalEventTrigger::HOLDING_DOWN
            || !IsButtonPressed(mouseEvent.Button) && mouseEvent.ButtonTrigger == InputDigitalEventTrigger::UP)
        {
            Button button = {.ButtonType = {.MouseButton = mouseEvent.Button}, .Pressed = IsButtonPressed(mouseEvent.Button)};
            return Sparkle::InputResult{true, {.Type = InputType::Button, .Value = {.Button = button}}};
        }
        return Sparkle::InputResult{false};
    }

    InputResult MouseController::ProcessAxis(const InputMouseAxisEvent &event)
    {
        bool hasAxisMoved = HasAxisMoved(event.Axis);
        float axisValue = GetAxis(event.Axis);
        if (event.AxisTrigger == InputAnalogEventTrigger::CONTINUOUS
            || hasAxisMoved && event.AxisTrigger == InputAnalogEventTrigger::MOVEMENT
            || axisValue >= 0.95 && event.AxisTrigger == InputAnalogEventTrigger::FULL_POSITIVE
            || axisValue <= -0.95 && event.AxisTrigger == InputAnalogEventTrigger::FULL_NEGATIVE)
        {
            class Axis axis = {.AxisType = {.MouseAxis = event.Axis}, .Value = axisValue};
            return InputResult{true, InputState{.Type=InputType::Axis, .Value={.Axis = axis}}};
        }
        return InputResult{false};
    }

    InputResult MouseController::ProcessStick(const InputMouseStickEvent &event)
    {
        struct InputVector stickValue = Stick[event.Stick];
        bool hasStickMoved = HasStickMoved(event.Stick);
        if (hasStickMoved && event.StickTrigger == InputAnalogEventTrigger::MOVEMENT
            || (stickValue.Horizontal >= 0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_POSITIVE || stickValue.Vertical >= 0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_POSITIVE)
            || (stickValue.Vertical <= -0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_NEGATIVE) || (stickValue.Horizontal <= -0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_NEGATIVE))

        {
            struct Stick stick = {.StickType = {.MouseStick = event.Stick}, .Stick = stickValue};
            return InputResult{true, InputState{.Type=InputType::Stick, .Value={.Stick = stick}}};
        }
        return InputResult{false};
    }

    InputResult MouseController::ProcessEvent(const InputTrigger &event)
    {
        switch (event.EventType)
        {
            case InputEventType::MouseButtonEventType:
                return ProcessButton(event.Event.MouseButtonEvent);

            case InputEventType::MouseAxisEventType:
                return ProcessAxis(event.Event.MouseAxisEvent);

            case InputEventType::MouseStickEventType:
                return ProcessStick(event.Event.MouseStickEvent);

            default:
                return Sparkle::InputResult{false};
        }
    }

    Sparkle::MouseController::MouseController() : Buttons(), LastButtons()
    {
        std::fill(LastButtons.begin(), LastButtons.end(), false);
        std::fill(Buttons.begin(), Buttons.end(), false);

        std::fill(Axis.begin(), Axis.end(), false);
        std::fill(LastAxis.begin(), LastAxis.end(), false);
    }
} // Sparkle