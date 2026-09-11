//
// Created by z3r0_ on 10/01/2024.
//

#include "Sparkle/PlayerInputController.h"

namespace Sparkle
{
    void PlayerInputController::Update()
    {
        for (auto &ButtonAction: InputMap.ActionTrigger)
        {
            const auto event = ButtonAction.first;

            if (GamepadController != nullptr && GamepadController->IsActive())
            {
                if (const auto Result = GamepadController->ProcessEvent(event); Result.IsActive)
                {
                    OnAnyActionEvent(weak_from_this(), ButtonAction.second, Result.InputState);
                    auto it = ActionEventMap.find(ButtonAction.second);
                    if (it == ActionEventMap.end()) continue;
                    it->second(weak_from_this(), ButtonAction.second, Result.InputState);
                    continue;
                }
            }

            if (KeyboardController != nullptr && KeyboardController->IsActive())
            {
                if (const auto Result = KeyboardController->ProcessEvent(event); Result.IsActive)
                {
                    OnAnyActionEvent(weak_from_this(), ButtonAction.second, Result.InputState);
                    auto it = ActionEventMap.find(ButtonAction.second);
                    if (it == ActionEventMap.end()) continue;
                    it->second(weak_from_this(), ButtonAction.second, Result.InputState);
                    continue;
                }
            }

            if (MouseController != nullptr && MouseController->IsActive())
            {
                if (const auto Result = MouseController->ProcessEvent(event); Result.IsActive)
                {
                    OnAnyActionEvent(weak_from_this(), ButtonAction.second, Result.InputState);
                    auto it = ActionEventMap.find(ButtonAction.second);
                    if (it == ActionEventMap.end()) continue;
                    it->second(weak_from_this(), ButtonAction.second, Result.InputState);
                    continue;
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

    EventBinder<const std::weak_ptr<PlayerInputController>&, const InputAction&, const InputState&>&
    PlayerInputController::OnAction(const InputAction & action)
    {
        auto it = ActionEventMap.find(action);
        if (it != ActionEventMap.end())
        {
            return it->second.GetBinder();
        }
        ActionEventMap.emplace(action, Event<const std::weak_ptr<PlayerInputController>&, const InputAction&, const InputState&>());
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