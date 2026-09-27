//
// Created by z3r0_ on 13/09/2026.
//

#include "SDLInitialization.h"
#include "Sparkle/Input.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"


#pragma region Input Actions
Sparkle::InputAction PauseAction("Pause");
Sparkle::InputAction JumpAction("Jump");
Sparkle::InputAction FireAction("Fire");
Sparkle::InputAction MoveAction("Move");
Sparkle::InputAction AimAction("Aim");
Sparkle::InputAction NextItemAction("NextItem");
Sparkle::InputAction PreviousItemAction("PreviousItem");
Sparkle::InputAction ResumeAction("Resume");
Sparkle::InputAction MoveLeftAction("Left");
Sparkle::InputAction MoveRightAction("Right");
Sparkle::InputAction MoveUpAction("Up");
Sparkle::InputAction MoveDownAction("Down");
Sparkle::InputAction ConfirmAction("Confirm");
#pragma endregion

#pragma region Input Maps

Sparkle::InputMap CreateInGameMap()
{
    Sparkle::InputMap map;

    // Gamepad mapping actions
    // With XBox Layout
    // A => Jump
    // RB or RT => Fire
    // Left Stick => Move
    // Right Stick => Aim
    // START => Pauses
    // DPAD => NextItem, PreviousItem
    map.Bind(Sparkle::GamepadButtonType::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, JumpAction);
    map.Bind(Sparkle::GamepadButtonType::BUTTON_START, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, PauseAction);
    map.Bind(Sparkle::GamepadButtonType::BUTTON_RIGHT_SHOULDER, Sparkle::InputDigitalEventTrigger::HOLDING_DOWN, FireAction);
    map.Bind(Sparkle::GamepadButtonType::BUTTON_DPAD_UP, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, NextItemAction);
    map.Bind(Sparkle::GamepadButtonType::BUTTON_DPAD_DOWN, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, PreviousItemAction);
    map.Bind(Sparkle::GamepadAxisType::TRIGGER_RIGHT, Sparkle::InputAnalogEventTrigger::FULL_POSITIVE, FireAction);
    map.Bind(Sparkle::GamepadStickType::STICK_LEFT, Sparkle::InputAnalogEventTrigger::MOVEMENT, MoveAction);
    map.Bind(Sparkle::GamepadStickType::STICK_RIGHT, Sparkle::InputAnalogEventTrigger::MOVEMENT, AimAction);

    // Keyboard mapping actions
    // Space => Jump
    // CTRL => Fire
    // Z => Fire
    // A/D => Horizontal Axis
    // W/S => Vertical Axis
    map.Bind(Sparkle::KeyboardButtonType::KEY_SPACE, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, JumpAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_ESCAPE, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, PauseAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_PAGEUP, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, NextItemAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_PAGEDOWN, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, PreviousItemAction);
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

    map.Bind(Sparkle::MouseButtonType::BUTTON_RIGHT, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, JumpAction);
    map.Bind(Sparkle::MouseButtonType::BUTTON_LEFT, Sparkle::InputDigitalEventTrigger::HOLDING_DOWN, FireAction);
    map.Bind(Sparkle::MouseStickType::MOUSE_MOVEMENT, Sparkle::InputAnalogEventTrigger::MOVEMENT, AimAction);
    map.Bind(Sparkle::MouseAxisType::SCROLL_WHEEL_Y, Sparkle::InputAnalogEventTrigger::FULL_POSITIVE, NextItemAction);
    map.Bind(Sparkle::MouseAxisType::SCROLL_WHEEL_Y, Sparkle::InputAnalogEventTrigger::FULL_NEGATIVE, PreviousItemAction);

    return map;
}

Sparkle::InputMap CreateInPauseMenuMap()
{
    Sparkle::InputMap map;

    map.Bind(Sparkle::GamepadButtonType::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, ConfirmAction);
    map.Bind(Sparkle::GamepadButtonType::BUTTON_B, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, ResumeAction);
    map.Bind(Sparkle::GamepadButtonType::BUTTON_START, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, ResumeAction);
    map.Bind(Sparkle::GamepadAxisType::AXIS_LEFT_X, Sparkle::InputAnalogEventTrigger::FULL_POSITIVE, MoveRightAction);
    map.Bind(Sparkle::GamepadAxisType::AXIS_LEFT_X, Sparkle::InputAnalogEventTrigger::FULL_NEGATIVE, MoveLeftAction);
    map.Bind(Sparkle::GamepadAxisType::AXIS_LEFT_Y, Sparkle::InputAnalogEventTrigger::FULL_POSITIVE, MoveUpAction);
    map.Bind(Sparkle::GamepadAxisType::AXIS_LEFT_Y, Sparkle::InputAnalogEventTrigger::FULL_NEGATIVE, MoveDownAction);

    map.Bind(Sparkle::KeyboardButtonType::KEY_P, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, ResumeAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_ESCAPE, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, ResumeAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_RETURN, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, ConfirmAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_A, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, MoveLeftAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_LEFT, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, MoveLeftAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_D, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, MoveRightAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_RIGHT, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, MoveRightAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_W, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, MoveUpAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_UP, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, MoveUpAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_S, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, MoveDownAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_DOWN, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, MoveDownAction);

    return map;
}

Sparkle::InputMap CreateSecondPlayerMap()
{
    // Second player can't pause and the keyboard layout is different
    Sparkle::InputMap map;

    // Gamepad mapping actions
    // With XBox Layout
    // A => Jump
    // RB or RT => Fire
    // Left Stick => Move
    // Right Stick => Aim
    // START => Pauses
    // DPAD => NextItem, PreviousItem
    map.Bind(Sparkle::GamepadButtonType::BUTTON_START, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, PauseAction);
    map.Bind(Sparkle::GamepadButtonType::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, JumpAction);
    map.Bind(Sparkle::GamepadButtonType::BUTTON_RIGHT_SHOULDER, Sparkle::InputDigitalEventTrigger::HOLDING_DOWN, FireAction);
    map.Bind(Sparkle::GamepadButtonType::BUTTON_DPAD_UP, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, NextItemAction);
    map.Bind(Sparkle::GamepadButtonType::BUTTON_DPAD_DOWN, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, PreviousItemAction);
    map.Bind(Sparkle::GamepadAxisType::TRIGGER_RIGHT, Sparkle::InputAnalogEventTrigger::FULL_POSITIVE, FireAction);
    map.Bind(Sparkle::GamepadStickType::STICK_LEFT, Sparkle::InputAnalogEventTrigger::MOVEMENT, MoveAction);
    map.Bind(Sparkle::GamepadStickType::STICK_RIGHT, Sparkle::InputAnalogEventTrigger::MOVEMENT, AimAction);

    // Keyboard mapping actions
    // Space => Jump
    // CTRL => Fire
    // Z => Fire
    // A/D => Horizontal Axis
    // W/S => Vertical Axis
    map.Bind(Sparkle::KeyboardButtonType::KEY_P, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, PauseAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_SLASH, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, JumpAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_RIGHTBRACKET, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, NextItemAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_LEFTBRACKET, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, PreviousItemAction);
    map.Bind(Sparkle::KeyboardAxisType
                     {Sparkle::KeyboardButtonType::KEY_L, Sparkle::KeyboardAxisType::POSITIVE },
             Sparkle::InputAnalogEventTrigger::FULL_POSITIVE, FireAction);
    map.Bind(Sparkle::KeyboardButtonType::KEY_RSHIFT, Sparkle::InputDigitalEventTrigger::HOLDING_DOWN, FireAction);
    map.Bind(Sparkle::KeyboardStickType
                     {
                             Sparkle::KeyboardAxisType {
                                     {Sparkle::KeyboardButtonType::KEY_LEFT, Sparkle::KeyboardAxisType::NEGATIVE},
                                     {Sparkle::KeyboardButtonType::KEY_RIGHT, Sparkle::KeyboardAxisType::POSITIVE}
                             },
                             Sparkle::KeyboardAxisType {
                                     {Sparkle::KeyboardButtonType::KEY_UP, Sparkle::KeyboardAxisType::POSITIVE},
                                     {Sparkle::KeyboardButtonType::KEY_DOWN, Sparkle::KeyboardAxisType::NEGATIVE}
                             }
                     },
             Sparkle::InputAnalogEventTrigger::MOVEMENT,
             MoveAction
    );

    map.Bind(Sparkle::KeyboardStickType
                     {
                             Sparkle::KeyboardAxisType {
                                     {Sparkle::KeyboardButtonType::KEY_KP_4, Sparkle::KeyboardAxisType::NEGATIVE},
                                     {Sparkle::KeyboardButtonType::KEY_KP_6, Sparkle::KeyboardAxisType::POSITIVE}
                             },
                             Sparkle::KeyboardAxisType {
                                     {Sparkle::KeyboardButtonType::KEY_KP_8, Sparkle::KeyboardAxisType::POSITIVE},
                                     {Sparkle::KeyboardButtonType::KEY_KP_2, Sparkle::KeyboardAxisType::NEGATIVE}
                             }
                     },
             Sparkle::InputAnalogEventTrigger::MOVEMENT,
             AimAction
    );

    return map;
}

Sparkle::InputMap SecondPlayerInputMap = CreateSecondPlayerMap();
Sparkle::InputMap InPauseMenuInputMap = CreateInPauseMenuMap();
Sparkle::InputMap InGameInputMap = CreateInGameMap();

#pragma endregion

std::shared_ptr<Sparkle::PlayerInputController> firstPlayer;
std::shared_ptr<Sparkle::PlayerInputController> secondPlayer;
Sparkle::InputAction lastAction;

void OnAnyPlayerAction(const std::weak_ptr<Sparkle::PlayerInputController>& player, const Sparkle::InputAction& action, const Sparkle::InputState& state)
{
    // avoid spamming the log
    if (action == lastAction) return;
    lastAction = action;
    switch (state.GetInputType())
    {
        case Sparkle::InputType::BUTTON:
            SDL_Log(">> ANY ACTION Player: %i => [%s] BUTTON %s", player.lock()->GetPlayerInputIndex(), action.GetName().c_str(), state.GetButton().Pressed ? "PRESSED" : "RELEASED");
            break;
        case Sparkle::InputType::AXIS:
            SDL_Log(">> ANY ACTION Player: %i => [%s] AXIS %f (More messages are suppressed to avoid spamming the log)", player.lock()->GetPlayerInputIndex(), action.GetName().c_str(), state.GetAxis().Value);
            break;
        case Sparkle::InputType::STICK:
            SDL_Log(">> ANY ACTION Player: %i => [%s] STICK [%f,%f] (More messages are suppressed to avoid spamming the log)", player.lock()->GetPlayerInputIndex(), action.GetName().c_str(), state.GetStick().Value.Horizontal, state.GetStick().Value.Vertical);
            break;
    }
}

void OnAnyKeyPressed(const std::weak_ptr<Sparkle::PlayerInputController>& player, const Sparkle::InputState& input)
{
    std::string controller;
    switch (input.GetControllerType())
    {
        case Sparkle::InputControllerType::KEYBOARD:
            controller = "Keyboard";
            break;
        case Sparkle::InputControllerType::MOUSE:
            controller = "Mouse";
            break;
        case Sparkle::InputControllerType::GAMEPAD:
            controller = "Gamepad";
            break;
    }
    SDL_Log(">> ANY KEY Pressed on controller {%s} by Player: %i", controller.c_str(), player.lock()->GetPlayerInputIndex());
}

void OnGamePaused(const std::weak_ptr<Sparkle::PlayerInputController>& player, const Sparkle::InputAction& action, const Sparkle::InputState& buttonState)
{
    if (buttonState.GetInputType() != Sparkle::InputType::BUTTON) return;
    firstPlayer->SetInputMap(Sparkle::InputMap());
    secondPlayer->SetInputMap(Sparkle::InputMap());
    player.lock()->SetInputMap(InPauseMenuInputMap);
    SDL_Log(">> Player: %i => PAUSED", player.lock()->GetPlayerInputIndex());
}

void OnGameResumed(const std::weak_ptr<Sparkle::PlayerInputController>& player, const Sparkle::InputAction& action, const Sparkle::InputState& buttonState)
{
    if (buttonState.GetInputType() != Sparkle::InputType::BUTTON) return;
    firstPlayer->SetInputMap(InGameInputMap);
    secondPlayer->SetInputMap(SecondPlayerInputMap);
    SDL_Log(">> Player: %i => RESUMED", player.lock()->GetPlayerInputIndex());
}

void OnFire(const std::weak_ptr<Sparkle::PlayerInputController>& player, const Sparkle::InputAction& action, const Sparkle::InputState& buttonState)
{
    SDL_Log(">> Player: %i => Is Firing", player.lock()->GetPlayerInputIndex());
}

void OnInput(const std::weak_ptr<Sparkle::PlayerInputController>&, const Sparkle::InputAction& action, const Sparkle::InputState& buttonState)
{
    switch (buttonState.GetInputType())
    {
        case Sparkle::InputType::BUTTON:
            SDL_Log(">> On Input Action[%s] BUTTON %s", action.GetName().c_str(), buttonState.GetButton() ? "PRESSED" : "RELEASED");
            break;
        case Sparkle::InputType::AXIS:
            SDL_Log(">> On Input Action[%s] AXIS %f", action.GetName().c_str(), buttonState.GetAxis().Value);
            break;
        case Sparkle::InputType::STICK:
            SDL_Log(">> On Input Action[%s] STICK [%f,%f]", action.GetName().c_str(), buttonState.GetStick().Value.Horizontal, buttonState.GetStick().Value.Vertical);
            break;
    }
}

void SetupInputActionCallback(const std::shared_ptr<Sparkle::PlayerInputController>& player)
{
    player->OnAction(JumpAction).Bind(&OnInput);
    player->OnAction(MoveAction).Bind(&OnInput);
    player->OnAction(AimAction).Bind(&OnInput);
    player->OnAction(NextItemAction).Bind(&OnInput);
    player->OnAction(PreviousItemAction).Bind(&OnInput);

    // PAUSE MENU ACTIONS:
    player->OnAction(MoveLeftAction).Bind(&OnInput);
    player->OnAction(MoveRightAction).Bind(&OnInput);
    player->OnAction(MoveUpAction).Bind(&OnInput);
    player->OnAction(MoveDownAction).Bind(&OnInput);
    player->OnAction(ConfirmAction).Bind(&OnInput);
}

int main(int argc, char* argv[])
{
    Sparkle::Input input;
    firstPlayer = input.GetNewPlayerInputController().lock();
    assert(firstPlayer && "A player should be created");
    firstPlayer->AssignGamepad();

    secondPlayer = input.GetNewPlayerInputController().lock();
    assert(secondPlayer && "A player should be created");
    secondPlayer->AssignGamepad();

    // Optional for the first player (keyboard and mouse should be automatically assigned)
    firstPlayer->AssignKeyboard();
    firstPlayer->AssignMouse();

    // if we add to the second and first player, mouse and keyboard inputs should happen to both
     secondPlayer->AssignKeyboard();
    // secondPlayer->AssignMouse();

    firstPlayer->OnGamepadConnected().Bind([](const std::weak_ptr<Sparkle::PlayerInputController>& player)
    { SDL_Log(">> Player %i connected", player.lock()->GetPlayerInputIndex());});
    secondPlayer->OnGamepadConnected().Bind([](const std::weak_ptr<Sparkle::PlayerInputController>& player)
    { SDL_Log(">> Player %i connected", player.lock()->GetPlayerInputIndex());});

    firstPlayer->SetInputMap(InGameInputMap);
    secondPlayer->SetInputMap(SecondPlayerInputMap);

    // Any action will trigger this function for all players.
    // We can use this for debugging, for example.
    input.OnAnyPlayerAction().Bind(&OnAnyPlayerAction);

    // On any button pressed - won't react to axis or sticks events
    input.OnAnyKeyJustPressed().Bind(&OnAnyKeyPressed);

    // when pausing, we are changing the mapping for the players. The one that paused should have logical control and only that player can resume.
    firstPlayer->OnAction(PauseAction).Bind(&OnGamePaused);
    secondPlayer->OnAction(PauseAction).Bind(&OnGamePaused);
    firstPlayer->OnAction(ResumeAction).Bind(&OnGameResumed);
    secondPlayer->OnAction(ResumeAction).Bind(&OnGameResumed);

    // Fire Action callback
    firstPlayer->OnAction(FireAction).Bind(&OnFire);
    secondPlayer->OnAction(FireAction).Bind(&OnFire);

    // setup generic callbacks for all remaining actions
    SetupInputActionCallback(firstPlayer);
    SetupInputActionCallback(secondPlayer);

    return InitializeSDLAndRunInput(input);
}

#pragma clang diagnostic pop