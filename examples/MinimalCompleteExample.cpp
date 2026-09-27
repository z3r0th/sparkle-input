#include "SDLInitialization.h"
#include "Sparkle/Input.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"

void ButtonPressed(const std::weak_ptr<Sparkle::PlayerInputController>&, const Sparkle::InputAction& action, Sparkle::InputState buttonState)
{
    switch (buttonState.GetInputType())
    {
        case Sparkle::InputType::BUTTON:
            SDL_Log(">> Action[%s] BUTTON PRESSED %s", action.GetName().c_str(), buttonState.GetButton() ? "PRESSED" : "RELEASED");
            break;
        case Sparkle::InputType::AXIS:
            SDL_Log(">> Action[%s] AXIS ACTIVE %f", action.GetName().c_str(), buttonState.GetAxis().Value);
            break;
        case Sparkle::InputType::STICK:
            SDL_Log(">> Action[%s] STICK ACTIVE [%f,%f]", action.GetName().c_str(), buttonState.GetStick().Value.Horizontal, buttonState.GetStick().Value.Vertical);
            break;
    }
}

int main(int argc, char* argv[])
{
    Sparkle::Input input;
    auto playerInputController = input.GetNewPlayerInputController().lock();
    assert(playerInputController && "A player should be created");
    playerInputController->AssignGamepad();
    playerInputController->AssignKeyboard();

    Sparkle::InputMap map;
    Sparkle::InputAction PauseAction("Pause");
    Sparkle::InputAction JumpAction("Jump");
    Sparkle::InputAction FireAction("Fire");
    Sparkle::InputAction MoveAction("Move");
    Sparkle::InputAction AimAction("Aim");
    Sparkle::InputAction ScrollAction("Scroll");

    // Gamepad mapping actions
    // With XBox Layout
    // A => Jump
    // RB or RT => Fire
    // Left Stick => Move
    // Right Stick => Aim
    // START => Pauses
    map.Bind(Sparkle::GamepadButtonType::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, JumpAction);
    map.Bind(Sparkle::GamepadButtonType::BUTTON_START, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, PauseAction);
    map.Bind(Sparkle::GamepadButtonType::BUTTON_RIGHT_SHOULDER, Sparkle::InputDigitalEventTrigger::HOLDING_DOWN, FireAction);
    map.Bind(Sparkle::GamepadAxisType::TRIGGER_RIGHT, Sparkle::InputAnalogEventTrigger::FULL_POSITIVE, FireAction);
    map.Bind(Sparkle::GamepadStickType::STICK_LEFT, Sparkle::InputAnalogEventTrigger::MOVEMENT, MoveAction);
    map.Bind(Sparkle::GamepadStickType::STICK_RIGHT, Sparkle::InputAnalogEventTrigger::MOVEMENT, AimAction);

    // Keyboard mapping actions
    // Space => Jump
    // CTRL => Fire
    // Z => Fire
    // A/D => Horizontal Axis
    // W/S => Vertical Axis
    map.Bind(Sparkle::KeyboardButtonType::KEY_SPACE, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, JumpAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_ESCAPE, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, PauseAction);
    map.Bind(Sparkle::KeyboardAxisType
            {Sparkle::KeyboardButtonType::KEY_LCTRL, Sparkle::KeyboardAxisType::POSITIVE },
             Sparkle::InputAnalogEventTrigger::FULL_POSITIVE, FireAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_Z, Sparkle::InputDigitalEventTrigger::HOLDING_DOWN, FireAction);
    map.Bind(Sparkle::KeyboardStickType
            {
                Sparkle::KeyboardAxisType {
                        {Sparkle::KeyboardButtonType::KEY_A, Sparkle::KeyboardAxisType::NEGATIVE},
                        {Sparkle::KeyboardButtonType::KEY_D, Sparkle::KeyboardAxisType::POSITIVE}
                },
                Sparkle::KeyboardAxisType {
                        {Sparkle::KeyboardButtonType::KEY_W, Sparkle::KeyboardAxisType::POSITIVE},
                        {Sparkle::KeyboardButtonType::KEY_S, Sparkle::KeyboardAxisType::NEGATIVE}
                }
            },
            Sparkle::InputAnalogEventTrigger::MOVEMENT,
            MoveAction
    );

    map.Bind(Sparkle::MouseButtonType::BUTTON_RIGHT, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, JumpAction);
    map.Bind(Sparkle::MouseButtonType::BUTTON_LEFT, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, FireAction);
    map.Bind(Sparkle::MouseAxisType::SCROLL_WHEEL_Y, Sparkle::InputAnalogEventTrigger::MOVEMENT, ScrollAction);
    map.Bind(Sparkle::MouseStickType::MOUSE_MOVEMENT, Sparkle::InputAnalogEventTrigger::MOVEMENT, MoveAction);

    playerInputController->SetInputMap(map);

    playerInputController->OnAction(PauseAction).Bind(&ButtonPressed);
    playerInputController->OnAction(JumpAction).Bind(&ButtonPressed);
    playerInputController->OnAction(FireAction).Bind(&ButtonPressed);
    playerInputController->OnAction(MoveAction).Bind(&ButtonPressed);
    playerInputController->OnAction(AimAction).Bind(&ButtonPressed);
    playerInputController->OnAction(ScrollAction).Bind(&ButtonPressed);

    return InitializeSDLAndRunInput(input);
}

#pragma clang diagnostic pop