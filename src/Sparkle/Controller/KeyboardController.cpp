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

Sparkle::InputEventResult Sparkle::KeyboardController::ProcessEvent(const Sparkle::InputEvent &event)
{
    if (event.EventType != InputEventType::KeyboardButtonEventType) return Sparkle::InputEventResult{false};
    const InputKeyboardButtonEvent& keyboardEvent = event.Event.KeyboardButtonEvent;
    bool isButtonJustPressed = IsButtonJustPressed(keyboardEvent.Button);
    bool isButtonJustReleased = IsButtonJustReleased(keyboardEvent.Button);
    if (isButtonJustPressed && keyboardEvent.ButtonTrigger == InputButtonEventTrigger::JUST_PRESSED
            || isButtonJustReleased && keyboardEvent.ButtonTrigger == InputButtonEventTrigger::JUST_RELEASED
            || IsButtonPressed(keyboardEvent.Button) && keyboardEvent.ButtonTrigger == InputButtonEventTrigger::HOLDING_DOWN
            || !IsButtonPressed(keyboardEvent.Button) && keyboardEvent.ButtonTrigger == InputButtonEventTrigger::UP)
    {
        return Sparkle::InputEventResult{true, {.ButtonPressed = IsButtonPressed(keyboardEvent.Button)}};
    }
    return Sparkle::InputEventResult{false};
}
