//
// Created by z3r0_ on 10/01/2024.
//

#include "PlayerInputController.h"

namespace Sparkle
{
    void PlayerInputController::Update()
    {
        for (auto & ButtonAction : InputMap.ButtonActions)
        {
            auto event = ButtonAction.first;
            if (GamepadController != nullptr && GamepadController->IsActive())
            {
                GamepadInputProcess.UpdateInput(event, ButtonAction.second);
            }
        }

        for (auto & ButtonAction : InputMap.ButtonActions)
        {
            auto event = ButtonAction.first;
            if (KeyboardController != nullptr && KeyboardController->IsActive())
            {
                KeyboardInputProcess.UpdateInput(event, ButtonAction.second);
            }
        }
    }

    void PlayerInputController::SetGamepadController(std::weak_ptr<Sparkle::GamepadController> gamepadController)
    {
        assert(GamepadController == nullptr);
        GamepadController = gamepadController.lock();
        GamepadController->OnConnected().Bind(&PlayerInputController::OnGamepadConnected, this);
        GamepadController->OnDisconnected().Bind(&PlayerInputController::OnGamepadDisconnected, this);

        // if gamepad is active, it is already connected. Call the event as we are just subscribing to an already connected controller
        if (GamepadController->IsActive())
        {
            OnGamepadConnected(gamepadController);
        }
    }

    void PlayerInputController::RemoveGamepadController()
    {
        assert(GamepadController != nullptr);
        OnGamepadDisconnectedEvent(weak_from_this());
        GamepadController->OnConnected().Remove(this);
        GamepadController->OnDisconnected().Remove(this);
        GamepadController.reset();
    }

    void PlayerInputController::Initialize()
    {
        GamepadInputProcess.SetPlayerInputController(weak_from_this());
        KeyboardInputProcess.SetKeyboardController(KeyboardController);
    }
} // Sparkle