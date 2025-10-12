//
// Created by z3r0_ on 10/01/2024.
//

#include "Sparkle/PlayerInputController.h"

namespace Sparkle
{
    void PlayerInputController::Update()
    {
        if (GamepadController != nullptr && GamepadController->IsActive())
        {
            for (auto &ButtonAction: InputMap.ActionTrigger)
            {
                auto event = ButtonAction.first;
                if (const auto Result = GamepadController->ProcessEvent(event); Result.IsActive)
                {
                    auto it = ActionEventMap.find(ButtonAction.second);
                    if (it == ActionEventMap.end()) continue;
                    it->second(weak_from_this(), ButtonAction.second, Result.InputState);
                }
            }
        }

        if (KeyboardController != nullptr && KeyboardController->IsActive())
        {
            for (auto &ButtonAction: InputMap.ActionTrigger)
            {
                auto event = ButtonAction.first;
                if (const auto Result = KeyboardController->ProcessEvent(event); Result.IsActive)
                {
                    auto it = ActionEventMap.find(ButtonAction.second);
                    if (it == ActionEventMap.end()) continue;
                    it->second(weak_from_this(), ButtonAction.second, Result.InputState);
                }
            }
        }
    }

    void PlayerInputController::SetGamepadController(const std::weak_ptr<Sparkle::GamepadController>& gamepadController)
    {
        assert(GamepadController == nullptr);
        GamepadController = gamepadController.lock();
        GamepadController->OnConnected().Bind(&PlayerInputController::OnGamepadConnected, this);
        GamepadController->OnDisconnected().Bind(&PlayerInputController::OnGamepadDisconnected, this);

        // if the gamepad is active, it is already connected. Call the event as we are just subscribing to an already connected controller
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

    EventBinder<const std::weak_ptr<PlayerInputController>, InputAction, InputState>&
    PlayerInputController::OnAction(const InputAction & action)
    {
        auto it = ActionEventMap.find(action);
        if (it != ActionEventMap.end())
        {
            return it->second.GetBinder();
        }
        ActionEventMap.emplace(action, Event<const std::weak_ptr<PlayerInputController>, InputAction, InputState>());
        return ActionEventMap[action].GetBinder();
    }

    void PlayerInputController::SetKeyboardController(const std::weak_ptr<Sparkle::KeyboardController> &keyboardController)
    {
        assert(KeyboardController == nullptr);
        KeyboardController = keyboardController.lock();
    }

    void PlayerInputController::RemoveKeyboardController()
    {
        KeyboardController.reset();
    }
} // Sparkle