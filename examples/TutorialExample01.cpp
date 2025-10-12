#include "SDLInitialization.h"
#include "Sparkle/Input.h"

void PrintAction(const std::weak_ptr<Sparkle::PlayerInputController>&, const Sparkle::InputAction& action, Sparkle::InputState buttonState)
{
    SDL_Log(">> Action[%s] - BUTTON PRESSED: [%s]", action.GetName().c_str(), buttonState.Value.ButtonPressed ? "PRESSED" : "RELEASED");
}

int main(int argc, char* argv[])
{
    Sparkle::InputMap map;
    Sparkle::InputAction Action("GAME ACTION");
    map.Bind(Sparkle::GamepadButton::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, Action);
    map.Bind(Sparkle::GamepadButton::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, Action);
    map.Bind(Sparkle::KeyboardButton::KEY_SPACE, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, Action);
    map.Bind(Sparkle::KeyboardButton::KEY_SPACE, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, Action);

    Sparkle::Input input;
    auto playerInputController = input.GetNewPlayerInputController().lock();
    playerInputController->AssignKeyboard();
    playerInputController->AssignGamepad();
    playerInputController->SetInputMap(map);
    playerInputController->OnAction(Action).Bind(&PrintAction);

    return InitializeSDLAndRunInput(input);
}