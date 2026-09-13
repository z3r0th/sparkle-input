//
// Created by z3r0_ on 11/01/2024.
//

#ifndef SPARKLE_SOLUTION_INPUT_H
#define SPARKLE_SOLUTION_INPUT_H

#include "PlayerInputController.h"
#include "InputAction.h"
#include "InputEvent.h"
#include "InputMap.h"

#include <SDL.h>

#define MAX_LOCAL_PLAYER_CONTROLLERS 100

using ControllerDeviceEvent = SDL_ControllerDeviceEvent;
using InputEvent = SDL_Event;

namespace Sparkle
{
    /// Input Manager
    /// Central point to inspect Input Related actions
    /// Get the Player Controllers, Gamepad or Mouse and keyboard to inspect the state or Bind event actions
    class Input
    {
    private:
        std::shared_ptr<PlayerInputController> CreateInputController(unsigned int index);
        std::map<unsigned int, std::shared_ptr<PlayerInputController>> PlayerInputControllers;
        std::map<unsigned int, std::shared_ptr<GamepadController>> GamepadControllers;
        std::shared_ptr<MouseController> MouseController;
        std::shared_ptr<KeyboardController> KeyboardController;

        void RemoveGamepadFromPlayer(const std::weak_ptr<GamepadController>&);
        std::shared_ptr<GamepadController> GetInactiveOrNewGamepadController(int device);
        std::shared_ptr<GamepadController> GetUnassignedGamepadController();
        unsigned int GetNextPlayerIndex();

        void HandlePlayerInputControllerRequest(const std::weak_ptr<PlayerInputController>&);

        void GamepadControllerDisconnected(const ControllerDeviceEvent& event);
        void GamepadControllerConnected(const ControllerDeviceEvent& event);

        void UpdateMouse();
        void UpdateGamepad();
        void UpdateKeyboard();

        Event<const std::weak_ptr<PlayerInputController>&, const InputState&> OnAnyKeyJustPressedEvent;
        Event<const std::weak_ptr<class KeyboardController>&, const InputState&> OnKeyboardJustPressedEvent;
        Event<const std::weak_ptr<class MouseController>&, const InputState&> OnMouseJustPressedEvent;
        Event<const std::weak_ptr<class MouseController>&, const InputState&, const MouseStick&> OnAnyMouseStickMovedEvent;
        Event<const std::weak_ptr<class GamepadController>&, const InputState&, const GamepadStick&> OnAnyGamepadStickMovedEvent;
        Event<const std::weak_ptr<GamepadController>&, const InputState&> OnGamepadJustPressedEvent;
        Event<const std::weak_ptr<PlayerInputController>&, const InputAction&, const InputState&> OnAnyActionEvent;

    public:

#pragma region Player Index
        static constexpr unsigned int FirstPlayerIndex = 0;
        static constexpr unsigned int SecondPlayerIndex = 1;
        static constexpr unsigned int ThirdPlayerIndex = 2;
        static constexpr unsigned int FourthPlayerIndex = 3;
        static constexpr unsigned int FifthPlayerIndex = 4;
        static constexpr unsigned int SixthPlayerIndex = 5;
#pragma endregion

        void UpdateEvent(InputEvent& event);
        void Update();

        explicit Input();
        ~Input();

        // TODO: * Review Naming events (MouseAxis::AXIS_X vs GamepadAxis::AXIS_RIGHT_X)
        // TODO: * Can we add auto Convertion functions to the Event classes, so we get the type directly from InputState. For example: bool ButtonPressed = InputState;
        // TODO: * Add function summary to all functions and classes

        // TODO: Make at least one complete example
        // TODO: Throw exceptions if in debug mode (like when trying to get a controller index that doesn't exist)

        // TODO: Refactor and Documentation

        // Next Version:
        // TODO: Add Mouse movement relative to last frame
        // TODO: Add Specific input support: DoubleClick, Drag, HoldingFor, maybe specific combination sequence (down, forward, X = Haduken)
        // TODO: Add Modifier keys (SHIFT, ALT, CTRL, LeftTrigger, etc), so when we are pressing a combination (CTRL + A) we can check trigger a different action
        // TODO: Add Keyboard text function - capture text/character instead of action trigger
        // TODO: A way to check for Specific Controller Type/Layout (playstation, xbox, etc)
        // TODO: Connection/Disconnection of multiple gamepads test. It should always be reassigned to the assigned player.
        // TODO: Touch/Pad support

        EventBinder<const std::weak_ptr<PlayerInputController>&, const InputAction&, const InputState&>& OnAnyPlayerAction() { return OnAnyActionEvent.GetBinder(); }
        EventBinder<const std::weak_ptr<PlayerInputController>&, const InputState&>& OnAnyKeyJustPressed() { return OnAnyKeyJustPressedEvent.GetBinder(); }
        EventBinder<const std::weak_ptr<class KeyboardController>&, const InputState&>& OnKeyboardJustPressed() { return OnKeyboardJustPressedEvent.GetBinder(); }
        EventBinder<const std::weak_ptr<class MouseController>&, const InputState&>& OnMouseJustPressed() { return OnMouseJustPressedEvent.GetBinder(); }
        EventBinder<const std::weak_ptr<GamepadController>&, const InputState&>& OnGamepadJustPressed() { return OnGamepadJustPressedEvent.GetBinder(); }
        EventBinder<const std::weak_ptr<class MouseController>&, const InputState&, const MouseStick&>& OnAnyMouseStickMoved() { return OnAnyMouseStickMovedEvent.GetBinder(); }
        EventBinder<const std::weak_ptr<class GamepadController>&, const InputState&, const GamepadStick&>& OnAnyGamepadStickMoved() { return OnAnyGamepadStickMovedEvent.GetBinder(); }

#pragma region Gamepad Proxy
        // Gamepad access functions
        // These are Proxy to access gamepad controller functions

        /// Get the button state of specific gamepad
        /// \param button Specific button to query
        /// \param controllerIndex the controller index. Default is 0
        /// \return true if button is pressed. Return false if button is not pressed or if no gamepad was found
        [[maybe_unused]][[nodiscard]] bool IsGamepadButtonPressed(GamepadButton button, unsigned int controllerIndex = 0) const;

        /// Check if gamepad button was just pressed
        /// Just pressed means that in the last frame the button was "released" and in this frame it is "pressed"
        /// \param button Specific button to query
        /// \param controllerIndex the controller index. Default is 0
        /// \return true if button was just pressed. Return false if button was not just pressed or if no gamepad was found
        [[maybe_unused]][[nodiscard]] bool IsGamepadButtonJustPressed(GamepadButton button, unsigned int controllerIndex = 0) const;

        /// Check if gamepad button was just released
        /// Just released means that in the last frame the button was "pressed" and in this frame it is "released"
        /// \param button Specific button to query
        /// \param controllerIndex the controller index. Default is 0
        /// \return true if button was just released. Return false if button was not just released or if no gamepad was found
        [[maybe_unused]][[nodiscard]] bool IsGamepadButtonJustReleased(GamepadButton button, unsigned int controllerIndex = 0) const;

        /// Get current axis value
        /// Value returned will be between -1(left and bottom) and 1(right and up). For Trigger (TRIGGER_LEFT, TRIGGER_RIGHT) it will return a value between 0 and 1.
        /// \param axis Specific Axis to query
        /// \param controllerIndex the controller index. Default is 0
        /// \return the Axis value
        [[maybe_unused]][[nodiscard]] float GetGamepadAxis(GamepadAxis axis, int controllerIndex = 0) const;

        /// Get current Stick value
        /// Value returned will be Stick (Vertical/Horizontal pair)
        /// between -1(left and bottom) and 1(right and up)
        /// \param stick Specific Stick to query
        /// \param controllerIndex the controller index. Default is 0
        /// \return the Stick value
        [[maybe_unused]][[nodiscard]] InputVector GetGamepadStick(GamepadStick stick, int controllerIndex = 0) const;

        // end Gamepad
#pragma endregion

#pragma region Keyboard Proxy

        // Keyboard access functions
        // These are Proxy to access keyboard controller functions

        /// Get Keyboard button state
        /// \param button Specific button to query
        /// \return true if button is pressed. Return false if button is not pressed
        [[maybe_unused]][[nodiscard]] bool IsKeyboardButtonPressed(KeyboardButton button) const;

        /// Check if Keyboard button was just pressed
        /// Just pressed means that in the last frame the button was "released" and in this frame it is "pressed"
        /// \param button Specific button to query
        /// \return true if button was just pressed. Return false if button was not just pressed
        [[maybe_unused]][[nodiscard]] bool IsKeyboardButtonJustPressed(KeyboardButton button) const;

        /// Check if Keyboard button was just released
        /// Just released means that in the last frame the button was "pressed" and in this frame it is "released"
        /// \param button Specific button to query
        /// \return true if button was just released. Return false if button was not just released
        [[maybe_unused]][[nodiscard]] bool IsKeyboardButtonJustReleased(KeyboardButton button) const;

        /// Get current axis value
        /// Value returned will be between -1(left and bottom) and 1(right and up)
        /// \param axis Specific Axis to query
        /// \return the Axis value
        [[maybe_unused]][[nodiscard]] float GetKeyboardAxis(KeyboardAxis axis) const;

        /// Get current Stick value
        /// Value returned will be Stick (Vertical/Horizontal pair)
        /// between -1(left and bottom) and 1(right and up)
        /// \param stick Specific Stick to query
        /// \return the Stick value
        [[maybe_unused]][[nodiscard]] Stick GetKeyboardStick(KeyboardStick stick) const;

        // end Keyboard

#pragma endregion

#pragma region Mouse Proxy

        // Mouse access functions
        // These are Proxy to access mouse controller functions

        /// Get Mouse button state
        /// \param button Specific button to query
        /// \return true if button is pressed. Return false if button is not pressed
        [[maybe_unused]][[nodiscard]] bool IsMouseButtonPressed(MouseButton button) const;

        /// Check if Mouse button was just pressed
        /// Just pressed means that in the last frame the button was "released" and in this frame it is "pressed"
        /// \param button Specific button to query
        /// \return true if button was just pressed. Return false if button was not just pressed
        [[maybe_unused]][[nodiscard]] bool IsMouseButtonJustPressed(MouseButton button) const;

        /// Check if Mouse button was just released
        /// Just released means that in the last frame the button was "pressed" and in this frame it is "released"
        /// \param button Specific button to query
        /// \return true if button was just released. Return false if button was not just released
        [[maybe_unused]][[nodiscard]] bool IsMouseButtonJustReleased(MouseButton button) const;

        /// Get current Mouse axis value
        /// Movement Axis are [0,1] top left is 0 and bottom right is 1
        /// Wheel movement is[-1,1] and -1 is down and 1 is up
        /// \param axis Specific Axis to query
        /// \return the Axis value
        [[maybe_unused]][[nodiscard]] float GetMouseAxis(MouseAxis axis) const;

        /// Get current Stick value
        /// Value returned will be Stick (Vertical/Horizontal pair)
        /// \param stick Specific Stick to query
        /// \return the Stick value
        [[maybe_unused]][[nodiscard]] InputVector GetMouseStick(MouseStick stick) const;

        // end Keyboard

#pragma endregion

#pragma region Gamepad/Keyboard/Mouse Management

        /// Get the Keyboard Controller
        /// \return the Keyboard Controller
        [[maybe_unused]][[nodiscard]] std::weak_ptr<class KeyboardController> GetKeyBoardController() { return KeyboardController; }

        /// Get the Mouse Controller
        /// \return the Mouse Controller
        [[maybe_unused]][[nodiscard]] std::weak_ptr<class MouseController> GetMouseController() { return MouseController; }

        /// Get an existing GamepadController at index. It might return nullptr if no Gamepad/Joystick were connected yet
        /// It might be already assigned to a player
        /// \param index GamepadController index
        /// \return
        [[maybe_unused]][[nodiscard]] std::shared_ptr<GamepadController> GetController(unsigned int index) const;

        ///  Remove Gamepad from player - if any assigned. This do not destroy the GamepadController.
        /// \param playerInputController the player input controller to remove the gamepad from
        [[maybe_unused]] void RemoveGamepadControllerFrom(PlayerInputController* playerInputController);

        /// Remove any controller associated with this Player input and destroy it (PlayerInputController).
        /// The Controllers (GamepadController, Mouse, Keyboard) are **not** destroyed, but put back to the pool.
        /// Removing a player does not change the index of current players, but it might be reused again if a new one is created
        /// \return true if able to destroy, false otherwise
        [[maybe_unused]] bool RemovePlayerInputController(const std::weak_ptr<PlayerInputController>&);

        /// Remove player by index. Remove any controller associated with this Player input and destroy it (PlayerInputController).
        /// The Controllers (GamepadController, Mouse, Keyboard) are **not** destroyed, but put back to the pool.
        /// Removing a player does not change the index of current players, but it might be reused again if a new one is created
        /// \param index player index
        /// \return true if able to destroy, false otherwise
        [[maybe_unused]][[nodiscard]] bool RemovePlayerInputController(unsigned int index);

        /// Check if a gamepad is assigned to any player
        /// \param gamepad the gamepad to check
        /// \return true if assigned, false otherwise
        [[maybe_unused]][[nodiscard]] bool IsGamepadAssigned(const std::weak_ptr<GamepadController>&);

        /// Check if a gamepad is assigned to a specific player
        /// \param gamepad the gamepad to check
        /// \param player the player to check
        /// \return true if assigned, false otherwise
        [[maybe_unused]][[nodiscard]] bool IsGamepadAssigned(const std::weak_ptr<GamepadController>&, const std::weak_ptr<PlayerInputController>&);

#pragma endregion

#pragma region PlayerInputController Management

        /// Get a new PlayerInputController. This Input Manager is responsible to manage, destroy and remove it.
        /// When deleting it, call `RemovePlayerInputController`
        /// \return the new PlayerInputController instance
        [[maybe_unused]][[nodiscard]] std::weak_ptr<PlayerInputController> GetNewPlayerInputController();

        /// How many PlayerInputControllers we have active.
        /// \return the amount of PlayerInputControllers
        [[maybe_unused]][[nodiscard]] inline unsigned int PlayerInputControllerCount() const { return PlayerInputControllers.size(); }

        /// Get the PlayerInputController assigned to a specific gamepad
        /// \param gamepad the gamepad to check
        /// \return the PlayerInputController or nullptr if it does not exist
        [[maybe_unused]][[nodiscard]] std::weak_ptr<PlayerInputController> GetAssignedPlayerInputController(const std::weak_ptr<GamepadController>& gamepad);

        /// Get the PlayerInputControllers assigned to a mouse
        /// \return the PlayerInputController or nullptr if it does not exist
        std::vector<std::weak_ptr<PlayerInputController>> GetAssignedMousePlayerInputControllers();

        /// Get the PlayerInputControllers assigned to a keyboard
        /// \return the PlayerInputController or nullptr if it does not exist
        std::vector<std::weak_ptr<PlayerInputController>> GetAssignedKeyboardPlayerInputControllers();

        /// Get or create new PlayerInputController. This Input Manager is responsible to manage, destroy and remove it.
        /// When deleting it, call `RemovePlayerInputController`
        /// \param index The PlayerInputController index. If it already exists, it will be returned. If not, a new one will be created.
        /// \return the new PlayerInputController instance
        [[maybe_unused]][[nodiscard]] std::weak_ptr<PlayerInputController> GetPlayerInputController(unsigned int index);
        [[maybe_unused]][[nodiscard]] std::weak_ptr<PlayerInputController> GetFirstPlayer() { return GetPlayerInputController(FirstPlayerIndex); }
        [[maybe_unused]][[nodiscard]] std::weak_ptr<PlayerInputController> GetSecondPlayer() { return GetPlayerInputController(SecondPlayerIndex); }
        [[maybe_unused]][[nodiscard]] std::weak_ptr<PlayerInputController> GetThirdPlayer() { return GetPlayerInputController(ThirdPlayerIndex); }
        [[maybe_unused]][[nodiscard]] std::weak_ptr<PlayerInputController> GetFourthPlayer() { return GetPlayerInputController(FourthPlayerIndex); }
        [[maybe_unused]][[nodiscard]] std::weak_ptr<PlayerInputController> GetFifthPlayer() { return GetPlayerInputController(FifthPlayerIndex); }
        [[maybe_unused]][[nodiscard]] std::weak_ptr<PlayerInputController> GetSixthPlayer() { return GetPlayerInputController(SixthPlayerIndex); }

#pragma endregion

    };

} // Sparkle

#endif //SPARKLE_SOLUTION_INPUT_H
