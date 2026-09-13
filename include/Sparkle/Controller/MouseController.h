//
// Created by z3r0_ on 09/09/2026.
//

#ifndef SPARKLEINPUT_MOUSECONTROLLER_H
#define SPARKLEINPUT_MOUSECONTROLLER_H

#include <cstdint>
#include <limits>
#include <array>

#include "Sparkle/InputController.h"
#include "Sparkle/InputEvent.h"

namespace Sparkle
{
    class Input;
    class MouseController : public InputController
    {
        // Input updates the buttons
        friend class Sparkle::Input;

    private:
        std::array<bool, (int)MouseButton::Count> Buttons;
        std::array<bool, (int)MouseButton::Count> LastButtons;

        std::array<float, (int)MouseAxis::Count> Axis{};
        std::array<float, (int)MouseAxis::Count> LastAxis{};

        std::array<struct InputVector, (int)MouseStick::Count> Stick{};
        std::array<struct InputVector, (int)MouseStick::Count> LastStick{};

        // Input.h will update these variables for us
        float MouseWheelX = 0.0f;
        float MouseWheelY = 0.0f;

    protected:
        void Update() override;
        InputResult ProcessButton(const InputMouseButtonEvent& event);
        InputResult ProcessAxis(const InputMouseAxisEvent& event);
        InputResult ProcessStick(const InputMouseStickEvent& event);

    public:
        explicit MouseController();

        inline bool IsActive() override { return true; }

        InputResult ProcessEvent(const Sparkle::InputTrigger &event);

        /// Check if Keyboard button is pressed
        /// Keyboard Buttons are updated on Input update
        /// \param key which device button is being checked
        /// \return true if button is currently pressed
        [[nodiscard]] inline bool IsButtonPressed(MouseButton key)
        {
            return Buttons[static_cast<unsigned int>(key)];
        }

        /// Check if Keyboard button was just pressed
        /// Just pressed means that it is currently pressed, but last frame it was not
        /// \param key which device button is being checked
        /// \return true if just pressed
        [[nodiscard]] inline bool IsButtonJustPressed(MouseButton key)
        {
            auto index = static_cast<unsigned int>(key);
            return Buttons[index] && !LastButtons[index];
        }

        /// Check if Keyboard button was just released
        /// Just released means that it is not currently pressed, but last frame it was
        /// \param key which device button is being checked
        /// \return true if just released
        [[nodiscard]] inline bool IsButtonJustReleased(MouseButton key)
        {
            auto index = static_cast<unsigned int>(key);
            return !Buttons[index] && LastButtons[index];
        }

        /// Get the first/any pressed button we can find
        /// \return the first pressed button or BUTTON_NONE if none is pressed
        inline MouseButton AnyJustPressedButton()
        {
            for(int i = 0 ; i < Buttons.size() ; ++i)
            {
                if (Buttons[i] && !LastButtons[i]) return {MouseButton::MouseButtonEnum(i)};
            }

            return {MouseButton::MouseButtonEnum::BUTTON_NONE};
        }

        /// Get the current Mouse axis value
        /// \param axis which mouse axis is being checked
        /// \return axis value
        [[nodiscard]] inline const float& GetAxis(MouseAxis axis)
        {
            return Axis[(int)axis];
        }

        /// Check if axis had a movement from last frame
        /// It has moved if an Axis value difference from last frame to this is greater than epsilon
        /// \param axis which device axis is being checked
        /// \return true if moved
        [[nodiscard]] inline bool HasAxisMoved(MouseAxis axis)
        {
            constexpr const float epsilon = std::numeric_limits<float>::epsilon();
            return abs(Axis[(int)axis] - LastAxis[(int)axis]) > epsilon;
        }

        /// Check if axis had a movement from last frame
        /// It has moved if an Axis value difference from last frame to this is greater than epsilon
        /// \param axis which axis is being checked
        /// \return true if moved
        [[nodiscard]] inline MouseAxis AnyAxisMoved()
        {
            for (int i = 0 ; i < (int)MouseAxis::Count ; ++i)
            {
                auto axis = MouseAxis::MouseAxisEnum(i);
                if (HasAxisMoved(axis)) return axis;
            }
            return MouseAxis::MouseAxisEnum::AXIS_NONE;
        }

        /// Check if stick had a movement from last frame
        /// It has moved if any Axis value difference from last frame to this is greater than epsilon
        /// \param stick which device axis is being checked
        /// \return true if moved
        [[nodiscard]] inline bool HasStickMoved(MouseStick stick)
        {
            constexpr const float epsilon = std::numeric_limits<float>::epsilon();
            int stickIndex = (int)stick;
            auto currentStick = Stick[stickIndex];
            auto lastStick = LastStick[stickIndex];
            return abs(currentStick.Horizontal - lastStick.Horizontal) > epsilon || abs(currentStick.Vertical - lastStick.Vertical) > epsilon;
        }

        /// Get the current Mouse stick value
        /// \param stick which device stick is being checked
        /// \return stick value
        [[nodiscard]] inline const struct InputVector& GetStick(MouseStick stick)
        {
            return Stick[(int)stick];
        }
    };

} // Sparkle

#endif //SPARKLEINPUT_MOUSECONTROLLER_H
