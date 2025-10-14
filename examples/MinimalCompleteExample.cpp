#include "SDLInitialization.h"
#include "Sparkle/Input.h"

void ButtonPressed(const std::weak_ptr<Sparkle::PlayerInputController>&, const Sparkle::InputAction& action, Sparkle::InputState buttonState)
{
    SDL_Log(">> Action[%s] KEY PRESSED %s", action.GetName().c_str(), buttonState.ButtonPressed ? "PRESSED" : "RELEASED");
}

int main(int argc, char* argv[])
{
    Sparkle::Input input;
    auto playerInputController = input.GetNewPlayerInputController().lock();
    assert(playerInputController && "A player should be created");
    playerInputController->AssignGamepad();

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
    // START => Pause
    map.Bind(Sparkle::GamepadButton::BUTTON_A, Sparkle::InputButtonEventTrigger::JUST_PRESSED, JumpAction);
    map.Bind(Sparkle::GamepadButton::BUTTON_START, Sparkle::InputButtonEventTrigger::JUST_RELEASED, PauseAction);
    // TODO: This is being triggered twice
    map.Bind(Sparkle::GamepadButton::BUTTON_RIGHT_SHOULDER, Sparkle::InputButtonEventTrigger::HOLDING_DOWN, FireAction);
    //map.Bind(Sparkle::GamepadAxis::TRIGGER_RIGHT, Sparkle::InputAxisEventTrigger::FULL_POSITIVE, FireAction);
    map.Bind(Sparkle::GamepadStick::STICK_LEFT, Sparkle::InputStickEventTrigger::MOVEMENT, MoveAction);
    map.Bind(Sparkle::GamepadStick::STICK_RIGHT, Sparkle::InputStickEventTrigger::MOVEMENT, AimAction);

    // Keyboard mapping actions
    // Space => Jump
    // CTRL => Fire
    // Z => Fire
    // A/D => Horizontal Axis
    // W/S => Vertical Axis
    // map.Bind(Sparkle::KeyboardButton::KEY_SPACE, Sparkle::InputButtonEventTrigger::JUST_PRESSED, JumpAction);
    // map.Bind(Sparkle::KeyboardButton::KEY_ESCAPE, Sparkle::InputButtonEventTrigger::JUST_PRESSED, PauseAction);
    // map.Bind(Sparkle::KeyboardButton::KEY_CTRL, Sparkle::InputButtonEventTrigger::HOLDING_DOWN, FireAction);
    // map.Bind(Sparkle::GamepadAxis::KEY_Z, Sparkle::InputButtonEventTrigger::HOLDING_DOWN, FireAction);
    // TODO: How to make AWSD to respond as a Stick or Axis so we can respond to it as a movement?
    //map.Bind(Sparkle::GamepadStick::STICK_LEFT, Sparkle::InputStickEventTrigger::MOVEMENT, MoveAction);
    //map.Bind(Sparkle::GamepadStick::STICK_RIGHT, Sparkle::InputStickEventTrigger::MOVEMENT, AimAction);

    playerInputController->SetInputMap(map);

    playerInputController->OnAction(PauseAction).Bind(&ButtonPressed);
    playerInputController->OnAction(JumpAction).Bind(&ButtonPressed);
    playerInputController->OnAction(FireAction).Bind(&ButtonPressed);
    playerInputController->OnAction(MoveAction).Bind(&ButtonPressed);
    playerInputController->OnAction(AimAction).Bind(&ButtonPressed);

    return InitializeSDLAndRunInput(input);
}
