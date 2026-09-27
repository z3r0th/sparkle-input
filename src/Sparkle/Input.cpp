//
// Created by z3r0_ on 11/01/2024.
//

#include "Sparkle/Input.h"

namespace Sparkle
{
    Input::Input()
    {
        KeyboardDeviceController = std::make_shared<KeyboardController>();
        MouseDeviceController = std::make_shared<MouseController>();
    }

    std::shared_ptr<GamepadController> Input::GetInactiveOrNewGamepadController(int device)
    {
        for (unsigned int i = 0 ; i < SDL_NumJoysticks() ; ++i)
        {
            // reach an index that does not have a Gamepad controller,
            // this means that we already check any other index
            if (GamepadDeviceControllers.count(i) == 0)
            {
                auto gamepad = std::make_shared<GamepadController>();
                gamepad->GamepadIndex = i;
                GamepadDeviceControllers[i] = gamepad;
                return gamepad;
            }

            // we have a gamepad controller in this index, check if we can use it
            auto gamepad = GamepadDeviceControllers[i];
            assert(gamepad != nullptr);
            if (gamepad->DeviceIndex == device || !gamepad->IsActive())
            {
                return gamepad;
            }
        }

        return {};
    }

    std::weak_ptr<GamepadController> Input::GetGamepadController(unsigned int index) const
    {
        auto it = GamepadDeviceControllers.find(index);
        if (it == GamepadDeviceControllers.end())
        {
            return {};
        }
        return it->second;
    }

    std::shared_ptr<GamepadController> Input::GetUnassignedGamepadController()
    {
        for (auto & it : GamepadDeviceControllers)
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
        return -1;
    }

    void Input::GamepadControllerDisconnected(const ControllerDeviceEvent &event)
    {
        auto device = event.which;
        for (auto & GamepadController : GamepadDeviceControllers)
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
        auto gamepad = GetInactiveOrNewGamepadController(device);
        if (gamepad->IsActive())
        {
            // it can be the case when a controller is reconnected too quickly that it doesn't get disconnected.
            // In such cases, the gamepad still holds the reference and should not call SetController again
            return;
        }
        auto sdl_controller = SDL_GameControllerOpen(device);
        gamepad->SetController(sdl_controller, device);
    }

    std::weak_ptr<PlayerInputController> Input::GetNewPlayerInputController()
    {
        auto index = GetNextPlayerIndex();
        if (index == -1) return {};
        assert(PlayerInputControllers.find(index) == PlayerInputControllers.end());
        PlayerInputControllers[index] = CreateInputController(index);
        return { PlayerInputControllers[index] };
    }

    bool Input::RemovePlayerInputController(const std::weak_ptr<PlayerInputController>& inputControllerPtr)
    {
        if (auto inputController = inputControllerPtr.lock())
        {
            return RemovePlayerInputController(inputController->GetPlayerInputIndex());
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
        RemoveGamepadFromPlayer(it->second->GetGamepadController());
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
        RemoveGamepadFromPlayer(playerInputController->GetGamepadController());
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
        UpdateMouse();

        for (int i = 0 ; i < (int)MouseStickType::Count; ++i)
        {
            auto mouseStick = MouseStickType(i);
            if (MouseDeviceController->HasStickMoved(mouseStick))
            {
                auto stick = Stick {.StickType = {.MouseStick = mouseStick}, .Value = MouseDeviceController->GetStick(mouseStick)};
                auto state = InputState (stick, InputControllerType::MOUSE);
                OnAnyMouseStickMovedEvent(MouseDeviceController, state);
            }
        }

        for (auto & GamepadControllerPair : GamepadDeviceControllers)
        {
            auto GamepadController = GamepadControllerPair.second;
            if (GamepadController->IsActive())
            {
                for (int i = 0 ; i < (int)GamepadStickType::Count; ++i)
                {
                    auto stickType = GamepadStickType(i);
                    if (GamepadController->HasStickMoved(stickType))
                    {
                        auto stick = Stick {.StickType = {.GamepadStick = stickType}, .Value = GamepadController->GetStick(stickType)};
                        auto state = InputState(stick, InputControllerType::GAMEPAD);
                        OnAnyGamepadStickMovedEvent(GamepadController, state);
                    }
                }
            }
        }
    }

    void Input::HandlePlayerInputControllerRequest(const std::weak_ptr<PlayerInputController>& playerInputControllerPtr)
    {
        if (auto playerInputController = playerInputControllerPtr.lock())
        {
            if (playerInputController->IsRequestingGamepad() && playerInputController->GetGamepadController().expired())
            {
                auto gamepadController = GetUnassignedGamepadController();
                if (gamepadController != nullptr)
                {
                    playerInputController->SetGamepadController(gamepadController);
                }
            }
            if (playerInputController->IsRequestingKeyboard() && playerInputController->GetKeyboardController().expired())
            {
                playerInputController->SetKeyboardController(KeyboardDeviceController);
            }
            if (playerInputController->IsRequestingMouse() && playerInputController->GetMouseController().expired())
            {
                playerInputController->SetMouseController(MouseDeviceController);
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
        else if (event.type == SDL_MOUSEWHEEL)
        {
            MouseDeviceController->MouseWheelYValue = 0.0f;
            MouseDeviceController->MouseWheelXValue = 0.0f;
            MouseDeviceController->MouseWheelXValue += (float)event.wheel.x;
            MouseDeviceController->MouseWheelYValue += (float)event.wheel.y;
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
        KeyboardDeviceController.reset();
        GamepadDeviceControllers.clear();
        MouseDeviceController.reset();
    }

    [[maybe_unused]] bool Input::IsGamepadButtonPressed(GamepadButtonType button, unsigned int controllerIndex) const
    {
        auto controller = GetGamepadController(controllerIndex);
        if (controller.expired())
        {
            return false;
        }

        return controller.lock()->IsButtonPressed(button);
    }

    bool Input::IsGamepadButtonJustPressed(GamepadButtonType button, unsigned int controllerIndex) const
    {
        auto controller = GetGamepadController(controllerIndex);
        if (controller.expired())
        {
            return false;
        }

        return controller.lock()->IsButtonJustPressed(button);
    }

    bool Input::IsGamepadButtonJustReleased(GamepadButtonType button, unsigned int controllerIndex) const
    {
        auto controller = GetGamepadController(controllerIndex);
        if (controller.expired())
        {
            return false;
        }

        return controller.lock()->IsButtonJustReleased(button);
    }

    float Input::GetGamepadAxis(GamepadAxisType axis, int controllerIndex) const
    {
        auto controller= GetGamepadController(controllerIndex);
        if (controller.expired())
        {
            return 0.0;
        }

        return controller.lock()->GetAxis(axis);
    }

    InputVector Input::GetGamepadStick(GamepadStickType stick, int controllerIndex) const
    {
        auto controller= GetGamepadController(controllerIndex);
        if (controller.expired())
        {
            return {};
        }

        return controller.lock()->GetStick(stick);
    }

    std::weak_ptr<PlayerInputController> Input::GetAssignedPlayerInputController(const std::weak_ptr<GamepadController>& gamepad)
    {
        if (gamepad.expired()) return {};
        auto gamepadController = gamepad.lock();
        for (const auto& it: PlayerInputControllers)
        {
            if (it.second->GetGamepadController().lock() == gamepadController) return it.second;
        }
        return {};
    }

    bool Input::IsGamepadAssigned(const std::weak_ptr<GamepadController>& gamepad)
    {
        if (gamepad.expired()) return false;
        return std::any_of(PlayerInputControllers.begin(), PlayerInputControllers.end(),
                           [&](const auto& it) { return IsGamepadAssigned(gamepad, it.second); });
    }

    bool Input::IsGamepadAssigned(const std::weak_ptr<GamepadController>& gamepad, const std::weak_ptr<PlayerInputController>& player)
    {
        if (gamepad.expired() || player.expired()) return false;
        if (auto playerInputController = player.lock())
        {
            auto gamepadAssignedIt = PlayerInputControllers.find(playerInputController->GetPlayerInputIndex());
            if (gamepadAssignedIt == PlayerInputControllers.end()) return false;
            const auto& gamepadAssigned = *gamepadAssignedIt;
            return gamepadAssigned.second->GetGamepadController().lock() == gamepad.lock();
        }

        return false;
    }

    void Input::UpdateGamepad()
    {
        for (auto & gamepadController : GamepadDeviceControllers)
        {
            std::shared_ptr<GamepadController> gamepad = gamepadController.second;
            gamepad->Update();
            auto pressedButton = gamepad->AnyJustPressedButton();
            if (pressedButton != GamepadButtonType::BUTTON_NONE)
            {
                Button button = {.ButtonType = {.GamepadButton = pressedButton}, .Pressed = true};
                auto inputState = InputState(button, InputControllerType::GAMEPAD);
                if (auto player = GetAssignedPlayerInputController(gamepad); !player.expired())
                {
                    OnAnyKeyJustPressedEvent(player, inputState);
                }
                OnGamepadJustPressedEvent(gamepad, inputState);
            }
            if (gamepad->AnyAxisMoved() != GamepadAxisType::AXIS_NONE)
            {}
        }
    }

    void Input::UpdateMouse()
    {
        MouseDeviceController->Update();
        auto pressedButton = MouseDeviceController->AnyJustPressedButton();
        if (pressedButton != MouseButtonType::BUTTON_NONE)
        {
            Button button = {.ButtonType = {.MouseButton = pressedButton}, .Pressed = true};
            auto inputState = InputState(button, InputControllerType::MOUSE);
            auto players = GetAssignedMousePlayerInputControllers();
            for (auto & player : players)
            {
                OnAnyKeyJustPressedEvent(player, inputState);
            }
            OnMouseJustPressedEvent(MouseDeviceController, inputState);
        }
        if (MouseDeviceController->AnyAxisMoved() != MouseAxisType::AXIS_NONE)
        {}
    }

    void Input::UpdateKeyboard()
    {
        KeyboardDeviceController->Update();
        auto pressedButton = KeyboardDeviceController->AnyJustPressedButton();
        if (pressedButton != KeyboardButtonType::KEY_NONE)
        {
            Button button = {.ButtonType = {.KeyboardButton = pressedButton}, .Pressed = true};
            auto inputState = InputState(button, InputControllerType::KEYBOARD);
            auto players = GetAssignedKeyboardPlayerInputControllers();
            for (auto & player : players)
            {
                OnAnyKeyJustPressedEvent(player, inputState);
            }
            OnKeyboardJustPressedEvent(KeyboardDeviceController, inputState);
        }
    }

    std::weak_ptr<PlayerInputController> Input::GetPlayerInputController(unsigned int index)
    {
        if (index >= MAX_LOCAL_PLAYER_CONTROLLERS)
        {
            SDL_Log("Invalid Player Input Controller Index {%u}", index);
            assert(false);
        }
        auto controller = PlayerInputControllers.find(index);
        if (controller != PlayerInputControllers.end())
        {
            return controller->second;
        }
        auto playerInputController = CreateInputController(index);
        PlayerInputControllers[index] = playerInputController;
        return { PlayerInputControllers[index] };
    }

    std::shared_ptr<PlayerInputController> Input::CreateInputController(unsigned int index)
    {
        auto playerInputController = std::shared_ptr<PlayerInputController>(new PlayerInputController(index));
        playerInputController->OnAnyAction()
            .Bind([this](const std::weak_ptr<PlayerInputController>& player, const InputAction& action, const InputState& state)
            {
                OnAnyActionEvent(player, action, state);
            });
        if (index == FirstPlayerIndex)
        {
            playerInputController->AssignKeyboard();
            playerInputController->AssignMouse();
        }
        playerInputController->AssignGamepad();
        return playerInputController;
    }

    bool Input::IsMouseButtonPressed(MouseButtonType button) const
    {
        return MouseDeviceController->IsButtonPressed(button);
    }

    float Input::GetMouseAxis(MouseAxisType axis) const
    {
        return MouseDeviceController->GetAxis(axis);
    }

    bool Input::IsKeyboardButtonPressed(KeyboardButtonType button) const
    {
        return KeyboardDeviceController->IsButtonPressed(button);
    }

    bool Input::IsKeyboardButtonJustPressed(KeyboardButtonType button) const
    {
        return KeyboardDeviceController->IsButtonJustPressed(button);
    }

    bool Input::IsKeyboardButtonJustReleased(KeyboardButtonType button) const
    {
        return KeyboardDeviceController->IsButtonJustReleased(button);
    }

    float Input::GetKeyboardAxis(KeyboardAxisType axis) const
    {
        return KeyboardDeviceController->GetAxis(axis);
    }

    Stick Input::GetKeyboardStick(KeyboardStickType stick) const
    {
        return KeyboardDeviceController->GetStick(stick);
    }

    bool Input::IsMouseButtonJustPressed(MouseButtonType button) const
    {
        return MouseDeviceController->IsButtonJustPressed(button);
    }

    bool Input::IsMouseButtonJustReleased(MouseButtonType button) const
    {
        return MouseDeviceController->IsButtonJustReleased(button);
    }

    InputVector Input::GetMouseStick(MouseStickType stick) const
    {
        return MouseDeviceController->GetStick(stick);
    }

    std::vector<std::weak_ptr<PlayerInputController>> Input::GetAssignedMousePlayerInputControllers()
    {
        std::vector<std::weak_ptr<PlayerInputController>> assignedPlayers;
        for (auto & it : PlayerInputControllers)
        {
            auto playerInputController = it.second;
            if (playerInputController->GetMouseController().lock() == MouseDeviceController)
            {
                assignedPlayers.push_back(playerInputController);
            }
        }
        return assignedPlayers;
    }

    std::vector<std::weak_ptr<PlayerInputController>> Input::GetAssignedKeyboardPlayerInputControllers()
    {
        std::vector<std::weak_ptr<PlayerInputController>> assignedPlayers;
        for (auto & it : PlayerInputControllers)
        {
            auto playerInputController = it.second;
            if (playerInputController->GetKeyboardController().lock() == KeyboardDeviceController)
            {
                assignedPlayers.push_back(playerInputController);
            }
        }
        return assignedPlayers;
    }

} // Sparkle