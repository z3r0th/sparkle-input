//
// Created by z3r0_ on 10/10/2025.
//

#include "Sparkle/Controller/KeyboardController.h"
#include "Sparkle/InputEvent.h"
#include "Sparkle/InputMap.h"
#include <SDL.h>

void Sparkle::KeyboardController::Update()
{
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    for (unsigned int i = 0 ; i < static_cast<int>(KeyboardButton::Count) ; ++i)
    {
        LastButtons[i] = Buttons[i];
        Buttons[i] = keyState[static_cast<SDL_Scancode>(i)];
    }
}

Sparkle::KeyboardController::KeyboardController() : Buttons(), LastButtons()
{
    std::fill(LastButtons.begin(), LastButtons.end(), false);
    std::fill(Buttons.begin(), Buttons.end(), false);
}

float GetAxisValueFromAxis(Sparkle::KeyboardController* controller, Sparkle::KeyboardAxis axis, Sparkle::InputStickEventTrigger trigger)
{
    bool motion1Button = controller->IsButtonPressed(axis.Motion1.Button);
    bool motion2Button = controller->IsButtonPressed(axis.Motion2.Button);
    switch (trigger)
    {
        case Sparkle::InputStickEventTrigger::MOVEMENT:
            if (motion1Button) return axis.Motion1.Range == Sparkle::KeyboardAxis::POSITIVE ? 1.0f : -1.0f;
            if (motion2Button) return axis.Motion2.Range == Sparkle::KeyboardAxis::POSITIVE ? 1.0f : -1.0f;
        case Sparkle::InputStickEventTrigger::FULL_POSITIVE:
            if (motion1Button && axis.Motion1.Range == Sparkle::KeyboardAxis::POSITIVE || motion1Button && axis.Motion1.Range == Sparkle::KeyboardAxis::FULL)
                return 1.0f;
            if (motion2Button && axis.Motion2.Range == Sparkle::KeyboardAxis::POSITIVE || motion2Button && axis.Motion2.Range == Sparkle::KeyboardAxis::FULL)
                return 1.0f;
        case Sparkle::InputStickEventTrigger::FULL_NEGATIVE:
            if (motion1Button && axis.Motion1.Range == Sparkle::KeyboardAxis::NEGATIVE || motion1Button && axis.Motion1.Range == Sparkle::KeyboardAxis::FULL)
                return -1.0f;
            if (motion2Button && axis.Motion2.Range == Sparkle::KeyboardAxis::NEGATIVE || motion2Button && axis.Motion2.Range == Sparkle::KeyboardAxis::FULL)
                return -1.0f;
            break;
    }
    return 0.0f;
}

Sparkle::InputResult Sparkle::KeyboardController::ProcessEvent(const Sparkle::InputTrigger &event)
{
    switch (event.EventType)
    {
        case InputEventType::KeyboardButtonEventType:
        {
            const InputKeyboardButtonEvent &keyboardEvent = event.Event.KeyboardButtonEvent;
            bool isButtonJustPressed = IsButtonJustPressed(keyboardEvent.Button);
            bool isButtonJustReleased = IsButtonJustReleased(keyboardEvent.Button);
            if (isButtonJustPressed && keyboardEvent.ButtonTrigger == InputButtonEventTrigger::JUST_PRESSED
                || isButtonJustReleased && keyboardEvent.ButtonTrigger == InputButtonEventTrigger::JUST_RELEASED
                || IsButtonPressed(keyboardEvent.Button) &&
                   keyboardEvent.ButtonTrigger == InputButtonEventTrigger::HOLDING_DOWN
                ||
                !IsButtonPressed(keyboardEvent.Button) && keyboardEvent.ButtonTrigger == InputButtonEventTrigger::UP) {
                return Sparkle::InputResult{true,
                                            {.Type = InputType::Button, .Value = {.ButtonPressed = IsButtonPressed(
                                                    keyboardEvent.Button)}}};
            }
            return Sparkle::InputResult{false};
        }
        case InputEventType::KeyboardAxisEventType:
        {
            const InputKeyboardAxisEvent &keyboardEvent = event.Event.KeyboardAxisEvent;
            bool motion1Button = IsButtonPressed(keyboardEvent.Axis.Motion1.Button);
            bool motion2Button = IsButtonPressed(keyboardEvent.Axis.Motion2.Button);
            if (keyboardEvent.AxisTrigger == InputAxisEventTrigger::MOVEMENT) // positive and negative trigger
            {
                if (motion1Button) return Sparkle::InputResult{true, {.Type = InputType::Axis, .Value = {.Axis =
                    keyboardEvent.Axis.Motion1.Range == KeyboardAxis::POSITIVE ? 1.0f : -1.0f}}};
                if (motion2Button) return Sparkle::InputResult{true, {.Type = InputType::Axis, .Value = {.Axis =
                    keyboardEvent.Axis.Motion2.Range == KeyboardAxis::POSITIVE ? 1.0f : -1.0f}}};
                return Sparkle::InputResult{false};
            }
            if (keyboardEvent.AxisTrigger == InputAxisEventTrigger::FULL_POSITIVE) {
                if (motion1Button && keyboardEvent.Axis.Motion1.Range == KeyboardAxis::POSITIVE ||
                    motion1Button && keyboardEvent.Axis.Motion1.Range == KeyboardAxis::FULL)
                    return Sparkle::InputResult{true, {.Type = InputType::Axis, .Value = {.Axis = 1.0f}}};
                if (motion2Button && keyboardEvent.Axis.Motion2.Range == KeyboardAxis::POSITIVE ||
                    motion2Button && keyboardEvent.Axis.Motion2.Range == KeyboardAxis::FULL)
                    return Sparkle::InputResult{true, {.Type = InputType::Axis, .Value = {.Axis = 1.0f}}};
            }
            if (keyboardEvent.AxisTrigger == InputAxisEventTrigger::FULL_NEGATIVE) {
                if (motion1Button && keyboardEvent.Axis.Motion1.Range == KeyboardAxis::NEGATIVE ||
                    motion1Button && keyboardEvent.Axis.Motion1.Range == KeyboardAxis::FULL)
                    return Sparkle::InputResult{true, {.Type = InputType::Axis, .Value = {.Axis = -1.0f}}};
                if (motion2Button && keyboardEvent.Axis.Motion2.Range == KeyboardAxis::NEGATIVE ||
                    motion2Button && keyboardEvent.Axis.Motion2.Range == KeyboardAxis::FULL)
                    return Sparkle::InputResult{true, {.Type = InputType::Axis, .Value = {.Axis = -1.0f}}};
            }
            if (IsButtonJustReleased(keyboardEvent.Axis.Motion1.Button) || IsButtonJustReleased(keyboardEvent.Axis.Motion2.Button))
            {
                return Sparkle::InputResult{true, {.Type = InputType::Axis, .Value = {.Axis = 0.0f}}};
            }

            return Sparkle::InputResult{false};
        }
        case InputEventType::KeyboardStickEventType:
        {
            const InputKeyboardStickEvent &keyboardEvent = event.Event.KeyboardStickEvent;
            if (IsButtonPressed(keyboardEvent.Stick.Vertical.Motion1.Button) || IsButtonPressed(keyboardEvent.Stick.Vertical.Motion2.Button)
                || IsButtonPressed(keyboardEvent.Stick.Horizontal.Motion1.Button) || IsButtonPressed(keyboardEvent.Stick.Horizontal.Motion2.Button))
            {
                float verticalAxis = GetAxisValueFromAxis(this, keyboardEvent.Stick.Vertical, keyboardEvent.StickTrigger);
                float horizontalAxis = GetAxisValueFromAxis(this, keyboardEvent.Stick.Horizontal,
                                                            keyboardEvent.StickTrigger);
                return Sparkle::InputResult{true,
                                            {.Type = InputType::Stick, .Value = {.Stick = {.X = horizontalAxis, .Y = verticalAxis}}}};
            }
            if ((IsButtonJustReleased(keyboardEvent.Stick.Vertical.Motion1.Button) || IsButtonJustReleased(keyboardEvent.Stick.Vertical.Motion2.Button)
            || IsButtonJustReleased(keyboardEvent.Stick.Horizontal.Motion1.Button) || IsButtonJustReleased(keyboardEvent.Stick.Horizontal.Motion2.Button)) &&
            (!IsButtonPressed(keyboardEvent.Stick.Vertical.Motion1.Button) && !IsButtonPressed(keyboardEvent.Stick.Vertical.Motion2.Button) &&
            !IsButtonPressed(keyboardEvent.Stick.Horizontal.Motion1.Button) || !IsButtonPressed(keyboardEvent.Stick.Horizontal.Motion2.Button)))
            {
                return Sparkle::InputResult{true, {.Type = InputType::Stick, .Value = {.Stick = {.X = 0.0f, .Y = 0.0f}}}};
            }
            return Sparkle::InputResult{false};
        }
    }
    return Sparkle::InputResult{false};
}
