//
// Created by z3r0_ on 11/01/2024.
//

#include "Sparkle/Input.h"

namespace Sparkle
{
    Input::Input()
    {
        KeyboardController = std::make_shared<class KeyboardController>();
    }

    std::shared_ptr<GamepadController> Input::GetInactiveOrNewGamepadController(int device)
    {
        for (unsigned int i = 0 ; i < SDL_NumJoysticks() ; ++i)
        {
            // reach an index that does not have a Gamepad controller,
            // this means that we already check any other index
            if (GamepadControllers.count(i) == 0)
            {
                auto gamepad = std::make_shared<GamepadController>();
                gamepad->GamepadIndex = i;
                GamepadControllers[i] = gamepad;
                return gamepad;
            }

            // we have a gamepad controller in this index, check if we can use it
            auto gamepad = GamepadControllers[i];
            assert(gamepad != nullptr);
            if (gamepad->DeviceIndex == device || !gamepad->IsActive())
            {
                return gamepad;
            }
        }

        // should never reach this part of code
        assert(false);
    }

    std::shared_ptr<GamepadController> Input::GetController(unsigned int index) const
    {
        auto it = GamepadControllers.find(index);
        if (it == GamepadControllers.end())
        {
            return nullptr;
        }
        return it->second;
    }

    std::shared_ptr<GamepadController> Input::GetUnassignedGamepadController()
    {
        for (auto & it : GamepadControllers)
        {
            auto GamepadController = it.second;
            if (!IsGamepadAssigned(GamepadController))
            {
                return GamepadController;
            }
        }

        // all GamepadControllers are assigned, and we don't have any available yet
        return nullptr;
    }

    unsigned int Input::GetNextPlayerIndex()
    {
        for (unsigned int i = 0 ; i < MAX_LOCAL_PLAYER_CONTROLLERS ; ++i)
        {
            if (PlayerInputControllers.count(i) == 0)
            {
                return i;
            }
        }

        // should never reach this part of code
        assert(false);
    }

    void Input::GamepadControllerDisconnected(const ControllerDeviceEvent &event)
    {
        auto device = event.which;
        for (auto & GamepadController : GamepadControllers)
        {
            if (device == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(GamepadController.second->InternalGameController)))
            {
                SDL_Log("Disconnecting Device {%u}", device);
                auto sdl_controller = GamepadController.second->InternalGameController;
                SDL_GameControllerClose(sdl_controller);
                GamepadController.second->ClearController();
            }
        }
    }

    void Input::GamepadControllerConnected(const ControllerDeviceEvent &event)
    {
        auto device = event.which;
        if (!SDL_IsGameController(device))
        {
            return;
        }
        SDL_Log("Connecting Device {%u}", device);
        auto sdl_controller = SDL_GameControllerOpen(device);
        auto gamepad = GetInactiveOrNewGamepadController(device);
        if (gamepad->IsActive())
        {
            // it can be the case when a controller is reconnected too quickly that it doesn't get disconnected.
            // In such cases, the gamepad still holds the reference and should not call SetController again
            return;
        }
        gamepad->SetController(sdl_controller, device);
    }

    std::weak_ptr<PlayerInputController> Input::GetNewPlayerInputController()
    {
        auto index = GetNextPlayerIndex();
        assert(PlayerInputControllers.find(index) == PlayerInputControllers.end());
        PlayerInputControllers[index] = std::shared_ptr<PlayerInputController>(new PlayerInputController(index));
        return { PlayerInputControllers[index] };
    }

    bool Input::RemovePlayerInputController(const std::weak_ptr<PlayerInputController>& inputControllerPtr)
    {
        if (auto inputController = inputControllerPtr.lock())
        {
            return RemovePlayerInputController(inputController->PlayerInputIndex);
        }

        return false;
    }

    bool Input::RemovePlayerInputController(unsigned int index)
    {
        auto it = PlayerInputControllers.find(index);
        if (it == PlayerInputControllers.end())
        {
            return false;
        }
        RemoveGamepadFromPlayer(it->second->GamepadController);
        it->second.reset();
        PlayerInputControllers.erase(it);
        return true;
    }

    void Input::RemoveGamepadFromPlayer(const std::weak_ptr<GamepadController>& gamepad)
    {
        if (gamepad.expired())
        {
            return;
        }

        auto playerInputControllerPtr = GetAssignedPlayerInputController(gamepad);
        if (auto playerInputController = playerInputControllerPtr.lock())
        {
            if (playerInputController)
            {
                playerInputController->RemoveGamepadController();
            }
        }
    }

    void Input::RemoveGamepadControllerFrom(PlayerInputController *playerInputController)
    {
        RemoveGamepadFromPlayer(playerInputController->GamepadController);
    }

    std::weak_ptr<PlayerInputController> Input::GetPlayerInputController(unsigned int index) const
    {
        auto it = PlayerInputControllers.find(index);
        if (it != PlayerInputControllers.end())
        {
            return it->second;
        }

        return std::weak_ptr<PlayerInputController>();
    }

    void Input::Update()
    {
        for (auto & playerInputControllersPair : PlayerInputControllers)
        {
            std::shared_ptr<PlayerInputController> playerInputController = playerInputControllersPair.second;
            HandlePlayerInputControllerRequest(playerInputController->weak_from_this());

            playerInputController->Update();
        }

        UpdateGamepad();
        UpdateKeyboard();
    }

    void Input::HandlePlayerInputControllerRequest(const std::weak_ptr<PlayerInputController>& playerInputControllerPtr)
    {
        if (auto playerInputController = playerInputControllerPtr.lock())
        {
            if (playerInputController->RequestGamepad && playerInputController->GamepadController == nullptr)
            {
                auto gamepadController = GetUnassignedGamepadController();
                if (gamepadController != nullptr)
                {
                    playerInputController->RequestGamepad = false;
                    playerInputController->SetGamepadController(gamepadController);
                }
            }
            if (playerInputController->RequestKeyboard && playerInputController->KeyboardController == nullptr)
            {
                playerInputController->RequestKeyboard = false;
                playerInputController->KeyboardController = KeyboardController;
            }
        }
    }

    void Input::UpdateEvent(InputEvent& event)
    {
        // Update Gamepad Events
        if (event.type == SDL_CONTROLLERDEVICEADDED)
        {
            GamepadControllerConnected(event.cdevice);
        }
        else if (event.type == SDL_CONTROLLERDEVICEREMOVED)
        {
            GamepadControllerDisconnected(event.cdevice);
        }
    }

    Input::~Input()
    {
        if (!PlayerInputControllers.empty())
        {
            std::vector<std::shared_ptr<PlayerInputController>> inputControllers;
            for (const auto& it: PlayerInputControllers)
            {
                inputControllers.push_back(it.second);
            }
            for (const auto& controller : inputControllers)
            {
                RemovePlayerInputController(controller);
            }
            inputControllers.clear();
            PlayerInputControllers.clear();
        }
        KeyboardController.reset();
        GamepadControllers.clear();
    }

    [[maybe_unused]] bool Input::IsGamepadButtonPressed(GamepadButton button, unsigned int controllerIndex) const
    {
        auto controller = GetController(controllerIndex);
        if (controller == nullptr)
        {
            return false;
        }

        return controller->IsButtonPressed(button);
    }

    bool Input::IsGamepadButtonJustPressed(GamepadButton button, unsigned int controllerIndex) const
    {
        auto controller = GetController(controllerIndex);
        if (controller == nullptr)
        {
            return false;
        }

        return controller->IsButtonJustPressed(button);
    }

    bool Input::IsGamepadButtonJustReleased(GamepadButton button, unsigned int controllerIndex) const
    {
        auto controller = GetController(controllerIndex);
        if (controller == nullptr)
        {
            return false;
        }

        return controller->IsButtonJustReleased(button);
    }

    float Input::GetGamepadAxis(GamepadAxis axis, int controllerIndex) const
    {
        auto controller= GetController(controllerIndex);
        if (controller == nullptr)
        {
            return 0.0;
        }

        return controller->GetAxis(axis);
    }

    std::weak_ptr<PlayerInputController> Input::GetAssignedPlayerInputController(const std::weak_ptr<GamepadController>& gamepad)
    {
        if (auto gamepadController = gamepad.lock())
        {
            for (const auto& it: PlayerInputControllers)
            {
                if (it.second->GamepadController == gamepadController) return it.second;
            }
        }

        return std::weak_ptr<PlayerInputController>();
    }

    bool Input::IsGamepadAssigned(const std::weak_ptr<GamepadController>& gamepad)
    {
        if (gamepad.expired()) return false;
        return std::any_of(PlayerInputControllers.begin(), PlayerInputControllers.end(),
                           [&](const auto& it) { return IsGamepadAssigned(gamepad, it.second); });
    }

    bool Input::IsGamepadAssigned(const std::weak_ptr<GamepadController>& gamepad, const std::weak_ptr<PlayerInputController>& player)
    {
        if (auto playerInputController = player.lock())
        {
            auto gamepadAssignedIt = PlayerInputControllers.find(playerInputController->GetPlayerInputIndex());
            if (gamepadAssignedIt == PlayerInputControllers.end()) return false;
            const auto& gamepadAssigned = *gamepadAssignedIt;
            return gamepadAssigned.second->GamepadController == gamepad.lock();
        }

        return false;
    }

    void Input::UpdateGamepad()
    {
        for (auto & gamepadController : GamepadControllers)
        {
            gamepadController.second->Update();
        }
    }

    void Input::UpdateKeyboard()
    {
        KeyboardController->Update();
    }
} // Sparkle