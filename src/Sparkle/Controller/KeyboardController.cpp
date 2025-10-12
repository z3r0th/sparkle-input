//
// Created by z3r0_ on 10/10/2025.
//

#include "Sparkle/Controller/InputProcess/KeyboardInputProcess.h"
#include "Sparkle/KeyboardController.h"
#include "Sparkle/InputEvent.h"
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

Sparkle::KeyboardController::KeyboardController() : Buttons(), LastButtons(), InputProcess(std::make_unique<KeyboardInputProcess>())
{
    std::fill(LastButtons.begin(), LastButtons.end(), false);
    std::fill(Buttons.begin(), Buttons.end(), false);
}

bool Sparkle::KeyboardController::ProcessInput(const Sparkle::InputEvent &event, const Sparkle::InputAction &action)
{
    return InputProcess->UpdateInput(event, action);
}

Sparkle::EventBinder<const unsigned int &, const Sparkle::InputAction &, const Sparkle::InputKeyboardButtonEvent &> &
Sparkle::KeyboardController::BinderForButton(const Sparkle::InputAction &action) {
    return InputProcess->BinderForButton(action);
}

void Sparkle::KeyboardController::Clear()
{
    InputProcess->Clear();
}

void Sparkle::KeyboardController::Initialize()
{
    auto weak = weak_from_this();
    InputProcess->SetKeyboardController(weak);
}

template<typename T>
void Sparkle::KeyboardController::RemoveBind(T *t)
{
    InputProcess->RemoveBind(t);
}

Sparkle::KeyboardController::~KeyboardController() = default;
