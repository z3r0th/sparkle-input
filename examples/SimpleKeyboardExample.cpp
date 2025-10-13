#include "Sparkle/Input.h"
#include "Sparkle/Controller/GamepadController.h"
#include "Sparkle/PlayerInputController.h"
#include "SDLInitialization.h"

int main(int argc, char* argv[])
{
    Sparkle::Input input;
    auto playerInputController = input.GetNewPlayerInputController().lock();
    assert(playerInputController && "A player should be created");

    Sparkle::InputMap map;
    Sparkle::InputAction pressedButtonA("PressedButtonA");

    map.Bind(Sparkle::KeyboardButton::KEY_A, Sparkle::InputButtonEventTrigger::JUST_PRESSED, pressedButtonA);
    map.Bind(Sparkle::KeyboardButton::KEY_A, Sparkle::InputButtonEventTrigger::JUST_RELEASED, pressedButtonA);
    playerInputController->SetInputMap(map);

    playerInputController->OnAction(pressedButtonA).Bind([](const std::weak_ptr<Sparkle::PlayerInputController>, Sparkle::InputAction action, Sparkle::InputState buttonState)
    {
        SDL_Log(">> Action[%s] KEY PRESSED %s", action.GetName().c_str(), buttonState.ButtonPressed ? "PRESSED" : "RELEASED");
    });

    return InitializeSDLAndRunInput(input);
}
