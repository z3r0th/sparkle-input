//
// Created by z3r0_ on 11/01/2024.
//

#ifndef SPARKLE_SOLUTION_GAMEPAD_CONTROLLER_H
#define SPARKLE_SOLUTION_GAMEPAD_CONTROLLER_H

#include <SDL_gamecontroller.h>
#include <cassert>
#include <array>
#include <limits>
#include <memory>

#include "InputEvent.h"
#include "InputController.h"
#include <Sparkle/Event.h>

#define RawGameController SDL_GameController

#define ON_DISCONNECTED_EVENT_NAME "OnDisconnected"
#define ON_CONNECTED_EVENT_NAME "OnConnected"

namespace Sparkle
{
    class Input;

    /// GamepadController to represent a Gamepad device
    /// This connects to an actual Gamepad and expose an interface to check the Gamepad status (buttons, axis, etc)
    class GamepadController : std::enable_shared_from_this<GamepadController>, public InputController
    {
        friend class Sparkle::Input;

    private:
        RawGameController *InternalGameController;

        Sparkle::Event<std::weak_ptr<GamepadController>> OnDisconnectedEvent;
        Sparkle::Event<std::weak_ptr<GamepadController>> OnConnectedEvent;

        std::array<bool, (int)GamepadButton::Count> Buttons;
        std::array<bool, (int)GamepadButton::Count> LastButtons;

        std::array<float, (int)GamepadAxis::Count> Axis;
        std::array<float, (int)GamepadAxis::Count> LastAxis;

        unsigned int GamepadIndex = -1;
        int DeviceIndex = -1;

        /// Sets a GameController
        /// It MUST HAVE been opened before
        /// \param controller
        void SetController(RawGameController *controller, int deviceIndex);

        /// Set InternalGameController to nullptr
        /// InternalGameController MUST HAVE been closed before this method can be called
        void ClearController();

    protected:
        /// If active, it should update buttons and lastButtons, axis and lastAxis with the device status
        void Update() override;

    public:
        explicit GamepadController(RawGameController *controller): InternalGameController(controller), Buttons(), LastButtons(),OnDisconnectedEvent(ON_DISCONNECTED_EVENT_NAME),
                                                                   OnConnectedEvent(ON_CONNECTED_EVENT_NAME)
        {
            std::fill(Buttons.begin(), Buttons.end(), false);
            std::fill(LastButtons.begin(), LastButtons.end(), false);

            std::fill(Axis.begin(), Axis.end(), false);
            std::fill(LastAxis.begin(), LastAxis.end(), false);
        }

        explicit GamepadController(): InternalGameController(nullptr), Buttons(), LastButtons(),OnDisconnectedEvent(ON_DISCONNECTED_EVENT_NAME),
                                      OnConnectedEvent(ON_CONNECTED_EVENT_NAME)
        {
            std::fill(Buttons.begin(), Buttons.end(), false);
            std::fill(LastButtons.begin(), LastButtons.end(), false);

            std::fill(Axis.begin(), Axis.end(), false);
            std::fill(LastAxis.begin(), LastAxis.end(), false);
        }

        Sparkle::Event<std::weak_ptr<GamepadController>>& OnDisconnected() { return OnDisconnectedEvent; }
        Sparkle::Event<std::weak_ptr<GamepadController>>& OnConnected() { return OnConnectedEvent; }

        /// This Gamepad Controller is active if a Gamepad device is connected and assigned to it
        /// The controller is assigned by the Input
        /// \return true if active
        [[nodiscard]] inline bool IsActive() override
        {
            return InternalGameController != nullptr;
        }

        /// Get this gamepad controller index. This is an app index, not to confuse with raw game controller device index
        /// The index is managed by the Input
        /// \return GamepadIndex
        [[maybe_unused]][[nodiscard]] inline unsigned int GetIndex() const
        {
            return GamepadIndex;
        }

        /// Check if Gamepad button is pressed
        /// Buttons are updated on Input update
        /// \param button which device button is being checked
        /// \return true if button is currently pressed
        [[nodiscard]] inline bool IsButtonPressed(GamepadButton button)
        {
            return Buttons[static_cast<unsigned int>(button)];
        }

        /// Check if Gamepad button was just pressed
        /// Just pressed means that it is currently pressed, but last frame it was not
        /// \param button which device button is being checked
        /// \return true if just pressed
        [[nodiscard]] inline bool IsButtonJustPressed(GamepadButton button)
        {
            auto index = static_cast<unsigned int>(button);
            return Buttons[index] && !LastButtons[index];
        }

        /// Check if Gamepad button was just released
        /// Just released means that it is not currently pressed, but last frame it was
        /// \param button which device button is being checked
        /// \return true if just released
        [[nodiscard]] inline bool IsButtonJustReleased(GamepadButton button)
        {
            auto index = static_cast<unsigned int>(button);
            return !Buttons[index] && LastButtons[index];
        }

        /// Get the current Gamepad axis value
        /// Currently we apply 2% movement as dead-zone
        /// \param axis which device axis is being checked
        /// \return axis or trigger value - Axis is ranged[0,1] and trigger [0,1]
        [[nodiscard]] inline const float& GetAxis(GamepadAxis axis)
        {
            return Axis[(int)axis];
        }

        /// Check if axis had a movement from last frame
        /// It has moved if an Axis value difference from last frame to this is greater than epsilon
        /// \param axis which device axis is being checked
        /// \return true if moved
        [[nodiscard]] inline bool HasAxisMoved(GamepadAxis axis)
        {
            constexpr const float epsilon = std::numeric_limits<float>::epsilon();
            return abs(Axis[(int)axis] - LastAxis[(int)axis]) > epsilon;
        }
    };
}

#endif //SPARKLE_SOLUTION_GAMEPAD_CONTROLLER_H
