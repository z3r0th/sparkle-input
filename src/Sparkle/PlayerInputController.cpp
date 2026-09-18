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

            if (auto gamepadController = GamepadDeviceController.lock(); gamepadController != nullptr)
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


            if (auto keyboardController = KeyboardDeviceController.lock(); keyboardController != nullptr)
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


            if (auto mouseController = MouseDeviceController.lock(); mouseController != nullptr)
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
        assert(GamepadDeviceController.expired());
        GamepadDeviceController.reset();
        if (gamepadController.expired())
        {
            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Gamepad controller is invalid. Aborting.");
            return;
        }
        GamepadDeviceController = gamepadController;
        RequestGamepad = false;
        if (auto gamepadControllerPtr = GamepadDeviceController.lock(); gamepadControllerPtr != nullptr)
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
        assert(!GamepadDeviceController.expired());
        OnGamepadDisconnectedEvent(weak_from_this());
        if (auto gamepadController = GamepadDeviceController.lock(); gamepadController != nullptr)
        {
            gamepadController->OnConnected().Remove(this);
            gamepadController->OnDisconnected().Remove(this);
        }
        GamepadDeviceController.reset();
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
        assert(KeyboardDeviceController.expired());
        KeyboardDeviceController = keyboardController;
        RequestKeyboard = false;
    }

    void PlayerInputController::RemoveKeyboardController()
    {
        KeyboardDeviceController.reset();
    }

    void PlayerInputController::SetMouseController(const std::weak_ptr<Sparkle::MouseController> &mouseController)
    {
        assert(MouseDeviceController.expired());
        MouseDeviceController = mouseController;
        RequestMouse = false;
    }

    void PlayerInputController::RemoveMouseController()
    {
        MouseDeviceController.reset();
    }
} // Sparkle