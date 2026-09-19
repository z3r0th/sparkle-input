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

        for (unsigned int i = 0 ; i < static_cast<int>(MouseButtonType::Count) ; ++i)
        {
            LastButtonsValue[i] = ButtonsValue[i];
            ButtonsValue[i] = buttons & SDL_BUTTON(static_cast<int>(i));
        }

        for (unsigned int i = 0 ; i < static_cast<int>(MouseAxisType::Count) ; ++i)
        {
            LastAxisValue[i] = AxisValue[i];
            float axis = 0.0f;
            auto MouseAxis = MouseAxisType(i);
            switch (MouseAxis)
            {
                case MouseAxisType::AXIS_X:
                    axis = (float)x;
                    break;
                case MouseAxisType::AXIS_Y:
                    axis = (float)y;
                    break;
                case MouseAxisType::SCROLL_WHEEL_X:
                    axis = MouseWheelXValue;
                    break;
                case MouseAxisType::SCROLL_WHEEL_Y:
                    axis = MouseWheelYValue;
                    break;
                case MouseAxisType::AXIS_NONE:
                case MouseAxisType::Count:
                    break;
            }
            if (abs(axis) <= DEAD_ZONE)
            {
                axis = 0.0;
            }
            AxisValue[i] = axis;
        }

        static const std::map<MouseStickType, const std::vector<MouseAxisType>> StickAxis =
        {
            {MouseStickType::MOUSE_MOVEMENT, {MouseAxisType::AXIS_X, MouseAxisType::AXIS_Y}},
        };
        for (unsigned int i = 0 ; i < static_cast<int>(MouseStickType::Count) ; ++i)
        {
            LastStickValue[i] = StickValue[i];
            auto UpdateStick = MouseStickType(i);
            InputVector stickValue = {0, 0 };
            const std::vector<MouseAxisType>& axisAnalyses = StickAxis.at(UpdateStick);
            int axisIndex = 0;
            for (auto& axisEnum : axisAnalyses)
            {
                float axis = GetAxis(axisEnum);
                assert (axisIndex <= 1 && "Support only two axis");
                axisIndex++ == 0 ? stickValue.Horizontal = axis : stickValue.Vertical = axis;
            }
            StickValue[i] = stickValue;
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
            return Sparkle::InputResult{true, {.Type = InputType::BUTTON, .Input = {.Button = button}}};
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
            Axis axis = {.AxisType = {.MouseAxis = event.Axis}, .Value = axisValue};
            return InputResult{true, InputState{.Type=InputType::AXIS, .Input={.Axis = axis}}};
        }
        return InputResult{false};
    }

    InputResult MouseController::ProcessStick(const InputMouseStickEvent &event)
    {
        InputVector stickValue = StickValue[(int)event.Stick];
        bool hasStickMoved = HasStickMoved(event.Stick);
        if (hasStickMoved && event.StickTrigger == InputAnalogEventTrigger::MOVEMENT
            || (stickValue.Horizontal >= 0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_POSITIVE || stickValue.Vertical >= 0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_POSITIVE)
            || (stickValue.Vertical <= -0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_NEGATIVE) || (stickValue.Horizontal <= -0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_NEGATIVE))

        {
            Stick stick = {.StickType = {.MouseStick = event.Stick}, .Value = stickValue};
            return InputResult{true, InputState{.Type=InputType::STICK, .Input={.Stick = stick}}};
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

    Sparkle::MouseController::MouseController() : ButtonsValue(), LastButtonsValue()
    {
        std::fill(LastButtonsValue.begin(), LastButtonsValue.end(), false);
        std::fill(ButtonsValue.begin(), ButtonsValue.end(), false);

        std::fill(AxisValue.begin(), AxisValue.end(), false);
        std::fill(LastAxisValue.begin(), LastAxisValue.end(), false);
    }
} // Sparkle