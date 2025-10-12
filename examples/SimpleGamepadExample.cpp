#include "SDLInitialization.h"
#include "Sparkle/Input.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"

int main(int argc, char* argv[])
{
    Sparkle::Input input;
    auto playerInputController = input.GetNewPlayerInputController().lock();
    assert(playerInputController && "A player should be created");

    Sparkle::InputMap map;
    Sparkle::InputAction pressedButtonA("PressedButtonA");

    map.Bind(Sparkle::GamepadButton::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, pressedButtonA);
    map.Bind(Sparkle::GamepadButton::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, pressedButtonA);
    playerInputController->SetInputMap(map);
    playerInputController->AssignGamepad();

    playerInputController->OnAction(pressedButtonA).Bind([](const std::weak_ptr<Sparkle::PlayerInputController>&, const Sparkle::InputAction& action, Sparkle::InputState buttonState)
    {
        SDL_Log(">> Action[%s] KEY PRESSED %s", action.GetName().c_str(), buttonState.Value.ButtonPressed ? "PRESSED" : "RELEASED");
    });

    return InitializeSDLAndRunInput(input);
}

#pragma clang diagnostic pop