#include <iostream>
#include "Sparkle/Input.h"
#include "Sparkle/GamepadController.h"
#include "Sparkle/PlayerInputController.h"
#include "SDLInitialization.h"

int main(int argc, char* argv[])
{
    Sparkle::Input input;
    auto playerInputController = input.GetNewPlayerInputController().lock();
    if (!playerInputController) return -1;
    Sparkle::InputMap map;
    Sparkle::InputAction pressedButtonA("PressedButtonA");
    map.Bind(Sparkle::KeyboardButton::KEY_A, Sparkle::InputButtonEventTrigger::JUST_PRESSED, pressedButtonA);
    playerInputController->OnKeyboardButton(pressedButtonA).Bind([](const unsigned int&, const Sparkle::InputAction&, const Sparkle::InputKeyboardButtonEvent&){
        SDL_Log(">> KEY A PRESSED");
    });
    playerInputController->SetInputMap(map);

    return InitializeSDLAndRunInput(input);
}
