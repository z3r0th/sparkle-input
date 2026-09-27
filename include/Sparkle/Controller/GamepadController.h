//
// Created by z3r0_ on 11/01/2024.
//

#ifndef SPARKLE_SOLUTION_GAMEPAD_CONTROLLER_H
#define SPARKLE_SOLUTION_GAMEPAD_CONTROLLER_H

#include <cassert>
#include <memory>
#include <limits>
#include <array>
#include <cmath>
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

        std::array<bool, (int)GamepadButtonType::Count> ButtonsValue;
        std::array<bool, (int)GamepadButtonType::Count> LastButtonsValue;

        std::array<float, (int)GamepadAxisType::Count> AxisValue{};
        std::array<float, (int)GamepadAxisType::Count> LastAxisValue{};

        std::array<InputVector, (int)GamepadStickType::Count> StickValue{};
        std::array<InputVector, (int)GamepadStickType::Count> LastStickValue{};

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
            return ButtonsValue[static_cast<unsigned int>(button)];
        }

        /// Check if Gamepad button was just pressed
        /// Just pressed means that it is currently pressed, but last frame it was not
        /// \param button which device button is being checked
        /// \return true if just pressed
        [[nodiscard]] inline bool IsButtonJustPressed(GamepadButtonType button)
        {
            auto index = static_cast<unsigned int>(button);
            return ButtonsValue[index] && !LastButtonsValue[index];
        }

        /// Check if Gamepad button was just released
        /// Just released means that it is not currently pressed, but last frame it was
        /// \param button which device button is being checked
        /// \return true if just released
        [[nodiscard]] inline bool IsButtonJustReleased(GamepadButtonType button)
        {
            auto index = static_cast<unsigned int>(button);
            return !ButtonsValue[index] && LastButtonsValue[index];
        }

        /// Get the first/any pressed button we can find
        /// \return the first pressed button or BUTTON_NONE if none is pressed
        inline GamepadButtonType AnyPressedButton()
        {
            for(int i = 0 ; i < ButtonsValue.size() ; ++i)
            {
                if (ButtonsValue[i]) return GamepadButtonType(GamepadButtonType(i));
            }

            return {GamepadButtonType::BUTTON_NONE};
        }

        /// Get the first/any pressed button we can find
        /// \return the first pressed button or BUTTON_NONE if none is pressed
        inline GamepadButtonType AnyJustPressedButton()
        {
            for(int i = 0 ; i < ButtonsValue.size() ; ++i)
            {
                if (ButtonsValue[i] && !LastButtonsValue[i]) return GamepadButtonType(GamepadButtonType(i));
            }

            return {GamepadButtonType::BUTTON_NONE};
        }

        /// Get all pressed buttons
        /// \return all pressed buttons
        inline std::vector<GamepadButtonType> PressedButtons()
        {
            std::vector<GamepadButtonType> pressedButtons;
            for(int i = 0 ; i < ButtonsValue.size() ; ++i)
            {
                if (ButtonsValue[i]) pressedButtons.push_back(GamepadButtonType(GamepadButtonType(i)));
            }

            return pressedButtons;
        }

        /// Get all pressed buttons
        /// \return all pressed buttons
        inline std::vector<GamepadButtonType> JustPressedButtons()
        {
            std::vector<GamepadButtonType> pressedButtons;
            for(int i = 0 ; i < ButtonsValue.size() ; ++i)
            {
                if (ButtonsValue[i] && !LastButtonsValue[i]) pressedButtons.push_back(GamepadButtonType(GamepadButtonType(i)));
            }

            return pressedButtons;
        }

        /// Get the current Gamepad axis value
        /// Currently we apply 2% movement as dead-zone
        /// \param axis which device axis is being checked
        /// \return axis or trigger value - Axis is ranged[0,1] and trigger [0,1]
        [[nodiscard]] inline const float& GetAxis(GamepadAxisType axis)
        {
            return AxisValue[(int)axis];
        }

        /// Get the current Gamepad stick value
        /// \param stick which device stick is being checked
        /// \return stick value
        [[nodiscard]] inline const InputVector& GetStick(GamepadStickType stick)
        {
            return StickValue[(int)stick];
        }

        /// Check if axis had a movement from last frame
        /// It has moved if an Axis value difference from last frame to this is greater than epsilon
        /// \param axis which device axis is being checked
        /// \return true if moved
        [[nodiscard]] inline bool HasAxisMoved(GamepadAxisType axis)
        {
            constexpr const float epsilon = std::numeric_limits<float>::epsilon();
            return std::abs(AxisValue[(int)axis] - LastAxisValue[(int)axis]) > epsilon;
        }

        /// Check if stick had a movement from last frame
        /// It has moved if any Axis value difference from last frame to this is greater than epsilon
        /// \param stick which device axis is being checked
        /// \return true if moved
        [[nodiscard]] inline bool HasStickMoved(GamepadStickType stick)
        {
            constexpr const float epsilon = std::numeric_limits<float>::epsilon();
            int stickIndex = (int)stick;
            InputVector currentStick = StickValue[stickIndex];
            InputVector lastStick = LastStickValue[stickIndex];
            return std::abs(currentStick.Horizontal - lastStick.Horizontal) > epsilon || std::abs(currentStick.Vertical - lastStick.Vertical) > epsilon;
        }

        /// Check if axis had a movement from last frame
        /// It has moved if an Axis value difference from last frame to this is greater than epsilon
        /// \param axis which device axis is being checked
        /// \return true if moved
        [[nodiscard]] inline GamepadAxisType AnyAxisMoved()
        {
            for (int i = 0 ; i < (int)GamepadAxisType::Count ; ++i)
            {
                auto axis = GamepadAxisType(i);
                if (HasAxisMoved(axis)) return axis;
            }
            return GamepadAxisType::AXIS_NONE;
        }

        /// Check if any stick had a movement from last frame
        /// It has moved if any Axis value difference from last frame to this is greater than epsilon
        /// \param axis which device axis is being checked
        /// \return true if moved
        [[nodiscard]] inline GamepadStickType AnyStickMoved()
        {
            for (int i = 0 ; i < (int)GamepadStickType::Count ; ++i)
            {
                auto stick = GamepadStickType(i);
                if (HasStickMoved(stick)) return stick;
            }
            return GamepadStickType::STICK_NONE;
        }
    };
}

#endif //SPARKLE_SOLUTION_GAMEPAD_CONTROLLER_H
