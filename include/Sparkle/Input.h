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

// TODO: Make mouse example
// TODO: Make at least one complete example

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
        std::map<unsigned int, std::shared_ptr<PlayerInputController>> PlayerInputControllers;
        std::map<unsigned int, std::shared_ptr<GamepadController>> GamepadControllers;
        std::shared_ptr<KeyboardController> KeyboardController;

        void RemoveGamepadFromPlayer(const std::weak_ptr<GamepadController>&);
        std::shared_ptr<GamepadController> GetInactiveOrNewGamepadController(int device);
        std::shared_ptr<GamepadController> GetUnassignedGamepadController();
        unsigned int GetNextPlayerIndex();

        void HandlePlayerInputControllerRequest(const std::weak_ptr<PlayerInputController>&);

        void GamepadControllerDisconnected(const ControllerDeviceEvent& event);
        void GamepadControllerConnected(const ControllerDeviceEvent& event);

        void UpdateGamepad();
        void UpdateKeyboard();

    public:
        void UpdateEvent(InputEvent& event);
        void Update();

        explicit Input();
        ~Input();

        std::weak_ptr<class KeyboardController> GetKeyBoardController() { return KeyboardController; }

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

        // end Gamepad

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

        [[maybe_unused]][[nodiscard]] bool IsGamepadAssigned(const std::weak_ptr<GamepadController>&);

        [[maybe_unused]][[nodiscard]] bool IsGamepadAssigned(const std::weak_ptr<GamepadController>&, const std::weak_ptr<PlayerInputController>&);

        /// Get a new PlayerInputController. This Input Manager is responsible to manage, destroy and remove it.
        /// When deleting it, call `RemovePlayerInputController`
        /// \return the new PlayerInputController instance
        [[maybe_unused]][[nodiscard]] std::weak_ptr<PlayerInputController> GetNewPlayerInputController();

        /// Get an already created PlayerInputController by its assigned index
        /// \param index The PlayerInputController index
        /// \return the Existing PlayerInputController or nullptr if it does not exist
        [[maybe_unused]][[nodiscard]] std::weak_ptr<PlayerInputController> GetPlayerInputController(unsigned int index) const;

        /// How many PlayerInputControllers we have active.
        /// \return the amount of PlayerInputControllers
        [[maybe_unused]][[nodiscard]] inline unsigned int PlayerInputControllerCount() const { return PlayerInputControllers.size(); }

        [[maybe_unused]][[nodiscard]] std::weak_ptr<PlayerInputController> GetAssignedPlayerInputController(const std::weak_ptr<GamepadController>& gamepad);
    };

} // Sparkle

#endif //SPARKLE_SOLUTION_INPUT_H
