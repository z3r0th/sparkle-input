//
// Created by z3r0_ on 10/10/2025.
//

#include "KeyboardController.h"
#include "InputEvent.h"
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
