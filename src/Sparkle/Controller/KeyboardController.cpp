//
// Created by z3r0_ on 10/10/2025.
//

#include "Sparkle/Controller/KeyboardController.h"
#include "Sparkle/InputEvent.h"
#include "Sparkle/InputMap.h"
#include <SDL.h>

float GetValueFromAxis(Sparkle::KeyboardController* controller, Sparkle::KeyboardAxisType axis, Sparkle::InputAnalogEventTrigger trigger)
{
    bool motion1Button = controller->IsButtonPressed(axis.Motion1.Button);
    bool motion2Button = controller->IsButtonPressed(axis.Motion2.Button);
    switch (trigger)
    {
        case Sparkle::InputAnalogEventTrigger::MOVEMENT:
        case Sparkle::InputAnalogEventTrigger::CONTINUOUS:
            if (motion1Button) return axis.Motion1.Range == Sparkle::KeyboardAxisType::POSITIVE ? 1.0f : -1.0f;
            if (motion2Button) return axis.Motion2.Range == Sparkle::KeyboardAxisType::POSITIVE ? 1.0f : -1.0f;
            break;
        case Sparkle::InputAnalogEventTrigger::FULL_POSITIVE:
            if (motion1Button && axis.Motion1.Range == Sparkle::KeyboardAxisType::POSITIVE || motion1Button && axis.Motion1.Range == Sparkle::KeyboardAxisType::FULL)
                return 1.0f;
            if (motion2Button && axis.Motion2.Range == Sparkle::KeyboardAxisType::POSITIVE || motion2Button && axis.Motion2.Range == Sparkle::KeyboardAxisType::FULL)
                return 1.0f;
            break;
        case Sparkle::InputAnalogEventTrigger::FULL_NEGATIVE:
            if (motion1Button && axis.Motion1.Range == Sparkle::KeyboardAxisType::NEGATIVE || motion1Button && axis.Motion1.Range == Sparkle::KeyboardAxisType::FULL)
                return -1.0f;
            if (motion2Button && axis.Motion2.Range == Sparkle::KeyboardAxisType::NEGATIVE || motion2Button && axis.Motion2.Range == Sparkle::KeyboardAxisType::FULL)
                return -1.0f;
            break;
    }
    return 0.0f;
}

void Sparkle::KeyboardController::Update()
{
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);
    for (unsigned int i = 0 ; i < static_cast<int>(KeyboardButtonType::Count) ; ++i)
    {
        LastButtonsValue[i] = ButtonsValue[i];
        ButtonsValue[i] = keyState[static_cast<SDL_Scancode>(i)];
    }
}

Sparkle::KeyboardController::KeyboardController() : ButtonsValue(), LastButtonsValue()
{
    std::fill(LastButtonsValue.begin(), LastButtonsValue.end(), false);
    std::fill(ButtonsValue.begin(), ButtonsValue.end(), false);
}

Sparkle::InputResult Sparkle::KeyboardController::ProcessEvent(const Sparkle::InputTrigger &trigger)
{
    return std::visit([this](auto&& event) -> InputResult
    {
      using EventT = std::decay_t<decltype(event)>;

      if constexpr (std::is_same_v<EventT, InputKeyboardButtonEvent>)
          return ProcessButton(event);
      else if constexpr (std::is_same_v<EventT, InputKeyboardAxisEvent>)
          return ProcessAxis(event);
      else if constexpr (std::is_same_v<EventT, InputKeyboardStickEvent>)
          return ProcessStick(event);
      else
          return InputResult{false};
    }, trigger.Event);
}

Sparkle::InputResult Sparkle::KeyboardController::ProcessButton(const Sparkle::InputKeyboardButtonEvent &keyboardEvent)
{
    bool isButtonJustPressed = IsButtonJustPressed(keyboardEvent.Button);
    bool isButtonJustReleased = IsButtonJustReleased(keyboardEvent.Button);
    if (isButtonJustPressed && keyboardEvent.ButtonTrigger == InputDigitalEventTrigger::JUST_PRESSED
        || isButtonJustReleased && keyboardEvent.ButtonTrigger == InputDigitalEventTrigger::JUST_RELEASED
        || IsButtonPressed(keyboardEvent.Button) && keyboardEvent.ButtonTrigger == InputDigitalEventTrigger::HOLDING_DOWN
        || !IsButtonPressed(keyboardEvent.Button) && keyboardEvent.ButtonTrigger == InputDigitalEventTrigger::UP)
    {
        Button button = {.ButtonType = keyboardEvent.Button, .Pressed = IsButtonPressed(keyboardEvent.Button)};
        return Sparkle::InputResult{true, InputState(button, InputControllerType::KEYBOARD)};
    }
    return Sparkle::InputResult{false};
}

Sparkle::InputResult Sparkle::KeyboardController::ProcessAxis(const Sparkle::InputKeyboardAxisEvent &keyboardEvent)
{
    bool motion1Button = IsButtonPressed(keyboardEvent.Axis.Motion1.Button);
    bool motion2Button = IsButtonPressed(keyboardEvent.Axis.Motion2.Button);
    if (motion1Button || motion2Button)
    {
        float axisValue = GetValueFromAxis(this, keyboardEvent.Axis, keyboardEvent.AxisTrigger);
        Axis axis = Axis{.AxisType = keyboardEvent.Axis, .Value = axisValue};
        return Sparkle::InputResult{true, InputState(axis, InputControllerType::KEYBOARD)};
    }
    if (IsButtonJustReleased(keyboardEvent.Axis.Motion1.Button) || IsButtonJustReleased(keyboardEvent.Axis.Motion2.Button))
    {
        Axis axis = Axis{.AxisType = keyboardEvent.Axis, .Value = 0.0f};
        return Sparkle::InputResult{true, InputState(axis, InputControllerType::KEYBOARD)};
    }
    return Sparkle::InputResult{false};
}

Sparkle::InputResult Sparkle::KeyboardController::ProcessStick(const Sparkle::InputKeyboardStickEvent &keyboardEvent)
{
    if (IsButtonPressed(keyboardEvent.Stick.Vertical.Motion1.Button) || IsButtonPressed(keyboardEvent.Stick.Vertical.Motion2.Button)
        || IsButtonPressed(keyboardEvent.Stick.Horizontal.Motion1.Button) || IsButtonPressed(keyboardEvent.Stick.Horizontal.Motion2.Button))
    {
        float verticalAxis = GetValueFromAxis(this, keyboardEvent.Stick.Vertical, keyboardEvent.StickTrigger);
        float horizontalAxis = GetValueFromAxis(this, keyboardEvent.Stick.Horizontal,
                                                keyboardEvent.StickTrigger);

        Stick stick = {.StickType = keyboardEvent.Stick, .Value = {.Horizontal = horizontalAxis, .Vertical = verticalAxis}};
        return Sparkle::InputResult{true, InputState(stick, InputControllerType::KEYBOARD)};
    }
    if ((IsButtonJustReleased(keyboardEvent.Stick.Vertical.Motion1.Button) || IsButtonJustReleased(keyboardEvent.Stick.Vertical.Motion2.Button)
         || IsButtonJustReleased(keyboardEvent.Stick.Horizontal.Motion1.Button) || IsButtonJustReleased(keyboardEvent.Stick.Horizontal.Motion2.Button)) &&
        (!IsButtonPressed(keyboardEvent.Stick.Vertical.Motion1.Button) && !IsButtonPressed(keyboardEvent.Stick.Vertical.Motion2.Button) &&
         !IsButtonPressed(keyboardEvent.Stick.Horizontal.Motion1.Button) && !IsButtonPressed(keyboardEvent.Stick.Horizontal.Motion2.Button)))
    {
        Stick stick = {.StickType = keyboardEvent.Stick, .Value = {.Horizontal = 0.0f, .Vertical = 0.0f}};
        return Sparkle::InputResult{true, InputState(stick, InputControllerType::KEYBOARD)};
    }
    return Sparkle::InputResult{false};
}

float Sparkle::KeyboardController::GetAxis(Sparkle::KeyboardAxisType axis)
{
    auto event = Sparkle::InputKeyboardAxisEvent { .AxisTrigger = {InputAnalogEventTrigger::MOVEMENT}, .Axis = axis };
    auto result = ProcessAxis(event);
    return result.IsActive ? result.InputState.GetAxis().Value : 0.0f;
}

Sparkle::Stick Sparkle::KeyboardController::GetStick(Sparkle::KeyboardStickType stick)
{
    auto event = Sparkle::InputKeyboardStickEvent { .StickTrigger = {InputAnalogEventTrigger::MOVEMENT}, .Stick = stick };
    auto result = ProcessStick(event);
    Stick empty = {.StickType = stick, .Value = {.Horizontal = 0.0f, .Vertical = 0.0f}};
    return result.IsActive ? result.InputState.GetStick() : empty;
}
