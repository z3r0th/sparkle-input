//
// Created by z3r0_ on 11/01/2024.
//

#ifndef SPARKLE_SOLUTION_GAMEPAD_CONTROLLER_H
#define SPARKLE_SOLUTION_GAMEPAD_CONTROLLER_H

#include <cassert>
#include <memory>
#include <limits>
#include <array>
#include <SDL.h>

#include "Sparkle/InputController.h"
#include "Sparkle/InputEvent.h"
#include "Sparkle/Event.h"

#define ON_DISCONNECTED_EVENT_NAME "OnDisconnected"
#define ON_CONNECTED_EVENT_NAME "OnConnected"

using RawGameController = SDL_GameController;

namespace Sparkle
{
    class InputTrigger;
    class InputAction;
    class Input;

    struct InputGamepadButtonEvent;
    struct InputGamepadStickEvent;
    struct InputGamepadAxisEvent;

    /// GamepadController to represent a Gamepad device
    /// This connects to an actual Gamepad and expose an interface to check the Gamepad status (buttons, axis, etc)
    class GamepadController : public std::enable_shared_from_this<GamepadController>, public InputController
    {
        friend class Sparkle::Input;

    private:
        RawGameController *InternalGameController;

        Sparkle::Event<const std::weak_ptr<GamepadController>&> OnDisconnectedEvent;
        Sparkle::Event<const std::weak_ptr<GamepadController>&> OnConnectedEvent;

        std::array<bool, (int)GamepadButtonType::Count> Buttons;
        std::array<bool, (int)GamepadButtonType::Count> LastButtons;

        std::array<float, (int)GamepadAxisType::Count> Axis{};
        std::array<float, (int)GamepadAxisType::Count> LastAxis{};

        std::array<struct InputVector, (int)GamepadStickType::Count> Stick{};
        std::array<struct InputVector, (int)GamepadStickType::Count> LastStick{};

        unsigned int GamepadIndex = -1;
        int DeviceIndex = -1;

        /// Sets a GameController
        /// It MUST HAVE been opened before
        /// \param controller
        void SetController(RawGameController *controller, int deviceIndex);

        /// Set InternalGameController to nullptr
        /// InternalGameController MUST HAVE been closed before this method can be called
        void ClearController();

        InputResult ProcessAxis(const InputGamepadAxisEvent &event);
        InputResult ProcessButton(const InputGamepadButtonEvent &event);
        InputResult ProcessStick(const InputGamepadStickEvent &event);

    protected:
        /// If active, it should update buttons and lastButtons, axis and lastAxis with the device status
        void Update() override;

    public:
        explicit GamepadController(RawGameController *controller);
        explicit GamepadController();
        virtual ~GamepadController() = default;

        InputResult ProcessEvent(const InputTrigger &event);

        Sparkle::EventBinder<const std::weak_ptr<GamepadController>&>& OnDisconnected() { return OnDisconnectedEvent.GetBinder(); }
        Sparkle::EventBinder<const std::weak_ptr<GamepadController>&>& OnConnected() { return OnConnectedEvent.GetBinder(); }

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
        [[nodiscard]] inline bool IsButtonPressed(GamepadButtonType button)
        {
            return Buttons[static_cast<unsigned int>(button)];
        }

        /// Check if Gamepad button was just pressed
        /// Just pressed means that it is currently pressed, but last frame it was not
        /// \param button which device button is being checked
        /// \return true if just pressed
        [[nodiscard]] inline bool IsButtonJustPressed(GamepadButtonType button)
        {
            auto index = static_cast<unsigned int>(button);
            return Buttons[index] && !LastButtons[index];
        }

        /// Check if Gamepad button was just released
        /// Just released means that it is not currently pressed, but last frame it was
        /// \param button which device button is being checked
        /// \return true if just released
        [[nodiscard]] inline bool IsButtonJustReleased(GamepadButtonType button)
        {
            auto index = static_cast<unsigned int>(button);
            return !Buttons[index] && LastButtons[index];
        }

        /// Get the first/any pressed button we can find
        /// \return the first pressed button or BUTTON_NONE if none is pressed
        inline GamepadButtonType AnyPressedButton()
        {
            for(int i = 0 ; i < Buttons.size() ; ++i)
            {
                if (Buttons[i]) return GamepadButtonType(GamepadButtonType::GamepadButtonEnum(i));
            }

            return GamepadButtonType(GamepadButtonType::GamepadButtonEnum::BUTTON_NONE);
        }

        /// Get the first/any pressed button we can find
        /// \return the first pressed button or BUTTON_NONE if none is pressed
        inline GamepadButtonType AnyJustPressedButton()
        {
            for(int i = 0 ; i < Buttons.size() ; ++i)
            {
                if (Buttons[i] && !LastButtons[i]) return GamepadButtonType(GamepadButtonType::GamepadButtonEnum(i));
            }

            return GamepadButtonType(GamepadButtonType::GamepadButtonEnum::BUTTON_NONE);
        }

        /// Get all pressed buttons
        /// \return all pressed buttons
        inline std::vector<GamepadButtonType> PressedButtons()
        {
            std::vector<GamepadButtonType> pressedButtons;
            for(int i = 0 ; i < Buttons.size() ; ++i)
            {
                if (Buttons[i]) pressedButtons.push_back(GamepadButtonType(GamepadButtonType::GamepadButtonEnum(i)));
            }

            return pressedButtons;
        }

        /// Get all pressed buttons
        /// \return all pressed buttons
        inline std::vector<GamepadButtonType> JustPressedButtons()
        {
            std::vector<GamepadButtonType> pressedButtons;
            for(int i = 0 ; i < Buttons.size() ; ++i)
            {
                if (Buttons[i] && !LastButtons[i]) pressedButtons.push_back(GamepadButtonType(GamepadButtonType::GamepadButtonEnum(i)));
            }

            return pressedButtons;
        }

        /// Get the current Gamepad axis value
        /// Currently we apply 2% movement as dead-zone
        /// \param axis which device axis is being checked
        /// \return axis or trigger value - Axis is ranged[0,1] and trigger [0,1]
        [[nodiscard]] inline const float& GetAxis(GamepadAxisType axis)
        {
            return Axis[(int)axis];
        }

        /// Get the current Gamepad stick value
        /// \param stick which device stick is being checked
        /// \return stick value
        [[nodiscard]] inline const struct InputVector& GetStick(GamepadStickType stick)
        {
            return Stick[(int)stick];
        }

        /// Check if axis had a movement from last frame
        /// It has moved if an Axis value difference from last frame to this is greater than epsilon
        /// \param axis which device axis is being checked
        /// \return true if moved
        [[nodiscard]] inline bool HasAxisMoved(GamepadAxisType axis)
        {
            constexpr const float epsilon = std::numeric_limits<float>::epsilon();
            return abs(Axis[(int)axis] - LastAxis[(int)axis]) > epsilon;
        }

        /// Check if stick had a movement from last frame
        /// It has moved if any Axis value difference from last frame to this is greater than epsilon
        /// \param stick which device axis is being checked
        /// \return true if moved
        [[nodiscard]] inline bool HasStickMoved(GamepadStickType stick)
        {
            constexpr const float epsilon = std::numeric_limits<float>::epsilon();
            int stickIndex = (int)stick;
            struct InputVector currentStick = Stick[stickIndex];
            struct InputVector lastStick = LastStick[stickIndex];
            return abs(currentStick.Horizontal - lastStick.Horizontal) > epsilon || abs(currentStick.Vertical - lastStick.Vertical) > epsilon;
        }

        /// Check if axis had a movement from last frame
        /// It has moved if an Axis value difference from last frame to this is greater than epsilon
        /// \param axis which device axis is being checked
        /// \return true if moved
        [[nodiscard]] inline GamepadAxisType AnyAxisMoved()
        {
            for (int i = 0 ; i < (int)GamepadAxisType::Count ; ++i)
            {
                auto axis = GamepadAxisType::GamepadAxisEnum(i);
                if (HasAxisMoved(axis)) return axis;
            }
            return GamepadAxisType::GamepadAxisEnum::AXIS_NONE;
        }

        /// Check if any stick had a movement from last frame
        /// It has moved if any Axis value difference from last frame to this is greater than epsilon
        /// \param axis which device axis is being checked
        /// \return true if moved
        [[nodiscard]] inline GamepadStickType AnyStickMoved()
        {
            for (int i = 0 ; i < (int)GamepadStickType::Count ; ++i)
            {
                auto stick = GamepadStickType::GamepadStickEnum(i);
                if (HasStickMoved(stick)) return stick;
            }
            return GamepadStickType::GamepadStickEnum::STICK_NONE;
        }
    };
}

#endif //SPARKLE_SOLUTION_GAMEPAD_CONTROLLER_H
