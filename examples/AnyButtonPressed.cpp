#include "SDLInitialization.h"
#include "Sparkle/Input.h"

void Update(Sparkle::Input& input)
{
}

int main(int argc, char* argv[])
{
    Sparkle::Input input;
    input.OnAnyKeyJustPressed()
        .Bind([](const Sparkle::InputEventType&, const Sparkle::Input::InputControllerReference&, const Sparkle::InputState&, const Sparkle::Input::InputButton&)
        {
            SDL_Log(">> ANY BUTTON PRESSED");
        });

    input.OnGamepadJustPressed()
        .Bind([](const std::weak_ptr<Sparkle::GamepadController>&, const Sparkle::InputState&, const Sparkle::Input::InputButton&)
        {
            SDL_Log(">> GAMEPAD BUTTON PRESSED");
        });

    input.OnKeyboardJustPressed()
        .Bind([](const std::weak_ptr<class Sparkle::KeyboardController>&, const Sparkle::InputState&, const Sparkle::Input::InputButton&)
        {
           SDL_Log(">> KEYBOARD BUTTON PRESSED");
        });

    input.OnAnyPlayerAction()
        .Bind([](const std::weak_ptr<Sparkle::PlayerInputController>&, const Sparkle::InputAction& action, const Sparkle::InputState& state)
        {
            SDL_Log(">> Action[%s] - BUTTON PRESSED: [%s]", action.GetName().c_str(), state.Value.ButtonPressed ? "PRESSED" : "RELEASED");
        });

    Sparkle::InputMap map;
    Sparkle::InputAction Action("Action");
    map.Bind(Sparkle::GamepadButton::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, Action);
    map.Bind(Sparkle::KeyboardButton::KEY_SPACE, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, Action);
    input.GetFirstPlayer().lock()->SetInputMap(map);
    input.GetFirstPlayer().lock()->OnAnyAction()
        .Bind([](const std::weak_ptr<Sparkle::PlayerInputController>&, const Sparkle::InputAction& action, const Sparkle::InputState& state)
        {
            SDL_Log(">> Player Direct Any Action[%s] - BUTTON PRESSED: [%s]", action.GetName().c_str(), state.Value.ButtonPressed ? "PRESSED" : "RELEASED");
        });

    return InitializeSDLAndRunInput(input, Update);
}