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

            if (auto gamepadController = GamepadController.lock(); gamepadController != nullptr)
            {
                if (gamepadController != nullptr && gamepadController->IsActive())
                {
                    if (const auto Result = gamepadController->ProcessEvent(event); Result.IsActive)
                    {
                        OnAnyActionEvent(weak_from_this(), ButtonAction.second, Result.InputState);
                        auto it = ActionEventMap.find(ButtonAction.second);
                        if (it == ActionEventMap.end()) continue;
                        it->second(weak_from_this(), ButtonAction.second, Result.InputState);
                        continue;
                    }
                }
            }


            if (auto keyboardController = KeyboardController.lock(); keyboardController != nullptr)
            {
                if (keyboardController != nullptr && keyboardController->IsActive())
                {
                    if (const auto Result = keyboardController->ProcessEvent(event); Result.IsActive)
                    {
                        OnAnyActionEvent(weak_from_this(), ButtonAction.second, Result.InputState);
                        auto it = ActionEventMap.find(ButtonAction.second);
                        if (it == ActionEventMap.end()) continue;
                        it->second(weak_from_this(), ButtonAction.second, Result.InputState);
                        continue;
                    }
                }
            }


            if (auto mouseController = MouseController.lock(); mouseController != nullptr)
            {
                if (mouseController != nullptr && mouseController->IsActive())
                {
                    if (const auto Result = mouseController->ProcessEvent(event); Result.IsActive)
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
    }

    void PlayerInputController::SetGamepadController(const std::weak_ptr<Sparkle::GamepadController>& gamepadController)
    {
        assert(GamepadController.expired());
        GamepadController.reset();
        if (gamepadController.expired())
        {
            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Gamepad controller is invalid. Aborting.");
            return;
        }
        GamepadController = gamepadController;
        RequestGamepad = false;
        if (auto gamepadControllerPtr = GamepadController.lock(); gamepadControllerPtr != nullptr)
        {
            gamepadControllerPtr->OnConnected().Bind(&PlayerInputController::OnGamepadConnected, this);
            gamepadControllerPtr->OnDisconnected().Bind(&PlayerInputController::OnGamepadDisconnected, this);

            // if the gamepad is active, it is already connected. Call the event as we are just subscribing to an already connected controller
            if (gamepadControllerPtr->IsActive())
            {
                OnGamepadConnected(gamepadController);
            }
        }
    }

    void PlayerInputController::RemoveGamepadController()
    {
        assert(!GamepadController.expired());
        OnGamepadDisconnectedEvent(weak_from_this());
        if (auto gamepadController = GamepadController.lock(); gamepadController != nullptr)
        {
            gamepadController->OnConnected().Remove(this);
            gamepadController->OnDisconnected().Remove(this);
        }
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
        assert(KeyboardController.expired());
        KeyboardController = keyboardController;
        RequestKeyboard = false;
    }

    void PlayerInputController::RemoveKeyboardController()
    {
        KeyboardController.reset();
    }

    void PlayerInputController::SetMouseController(const std::weak_ptr<Sparkle::MouseController> &mouseController)
    {
        assert(MouseController.expired());
        MouseController = mouseController;
        RequestMouse = false;
    }

    void PlayerInputController::RemoveMouseController()
    {
        MouseController.reset();
    }
} // Sparkle