#include "SDLInitialization.h"
#include "Sparkle/Input.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"

void ButtonPressed(const std::weak_ptr<Sparkle::PlayerInputController>&, const Sparkle::InputAction& action, Sparkle::InputState buttonState)
{
    switch (buttonState.Type)
    {
        case Sparkle::InputType::Button:
            SDL_Log(">> Action[%s] BUTTON PRESSED %s", action.GetName().c_str(), buttonState.Value.ButtonPressed ? "PRESSED" : "RELEASED");
            break;
        case Sparkle::InputType::Axis:
            SDL_Log(">> Action[%s] AXIS ACTIVE %f", action.GetName().c_str(), buttonState.Value.Axis);
            break;
        case Sparkle::InputType::Stick:
            SDL_Log(">> Action[%s] STICK ACTIVE [%f,%f]", action.GetName().c_str(), buttonState.Value.Stick.Horizontal, buttonState.Value.Stick.Vertical);
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

    // Gamepad mapping actions
    // With XBox Layout
    // A => Jump
    // RB or RT => Fire
    // Left Stick => Move
    // Right Stick => Aim
    // START => Pauses
    map.Bind(Sparkle::GamepadButton::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, JumpAction);
    map.Bind(Sparkle::GamepadButton::BUTTON_START, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, PauseAction);
    map.Bind(Sparkle::GamepadButton::BUTTON_RIGHT_SHOULDER, Sparkle::InputDigitalEventTrigger::HOLDING_DOWN, FireAction);
    map.Bind(Sparkle::GamepadAxis::TRIGGER_RIGHT, Sparkle::InputAnalogEventTrigger::FULL_POSITIVE, FireAction);
    map.Bind(Sparkle::GamepadStick::STICK_LEFT, Sparkle::InputAnalogEventTrigger::MOVEMENT, MoveAction);
    map.Bind(Sparkle::GamepadStick::STICK_RIGHT, Sparkle::InputAnalogEventTrigger::MOVEMENT, AimAction);

    // Keyboard mapping actions
    // Space => Jump
    // CTRL => Fire
    // Z => Fire
    // A/D => Horizontal Axis
    // W/S => Vertical Axis
    map.Bind(Sparkle::KeyboardButton::KEY_SPACE, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, JumpAction);
    map.Bind(Sparkle::KeyboardButton::KEY_ESCAPE, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, PauseAction);
    map.Bind(Sparkle::KeyboardAxis
            { Sparkle::KeyboardButton::KEY_LCTRL, Sparkle::KeyboardAxis::POSITIVE },
             Sparkle::InputAnalogEventTrigger::FULL_POSITIVE, FireAction);
    map.Bind(Sparkle::KeyboardButton::KEY_Z, Sparkle::InputDigitalEventTrigger::HOLDING_DOWN, FireAction);
    map.Bind(Sparkle::KeyboardStick
            {
                Sparkle::KeyboardAxis {
                        {Sparkle::KeyboardButton::KEY_A, Sparkle::KeyboardAxis::NEGATIVE},
                        {Sparkle::KeyboardButton::KEY_D, Sparkle::KeyboardAxis::POSITIVE}
                },
                Sparkle::KeyboardAxis {
                        {Sparkle::KeyboardButton::KEY_W, Sparkle::KeyboardAxis::POSITIVE},
                        {Sparkle::KeyboardButton::KEY_S, Sparkle::KeyboardAxis::NEGATIVE}
                }
            },
            Sparkle::InputAnalogEventTrigger::MOVEMENT,
            MoveAction
    );

    playerInputController->SetInputMap(map);

    playerInputController->OnAction(PauseAction).Bind(&ButtonPressed);
    playerInputController->OnAction(JumpAction).Bind(&ButtonPressed);
    playerInputController->OnAction(FireAction).Bind(&ButtonPressed);
    playerInputController->OnAction(MoveAction).Bind(&ButtonPressed);
    playerInputController->OnAction(AimAction).Bind(&ButtonPressed);

    return InitializeSDLAndRunInput(input);
}

#pragma clang diagnostic pop