//
// Created by z3r0_ on 09/09/2026.
//

#ifndef SPARKLEINPUT_MOUSECONTROLLER_H
#define SPARKLEINPUT_MOUSECONTROLLER_H

#include <cstdint>
#include <limits>
#include <array>
#include <cmath>

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
        std::array<bool, (int)MouseButtonType::Count> ButtonsValue;
        std::array<bool, (int)MouseButtonType::Count> LastButtonsValue;

        std::array<float, (int)MouseAxisType::Count> AxisValue{};
        std::array<float, (int)MouseAxisType::Count> LastAxisValue{};

        std::array<InputVector, (int)MouseStickType::Count> StickValue{};
        std::array<InputVector, (int)MouseStickType::Count> LastStickValue{};

        // Input.h will update these variables for us
        float MouseWheelXValue = 0.0f;
        float MouseWheelYValue = 0.0f;

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
        [[nodiscard]] inline bool IsButtonPressed(MouseButtonType key)
        {
            return ButtonsValue[static_cast<unsigned int>(key)];
        }

        /// Check if Keyboard button was just pressed
        /// Just pressed means that it is currently pressed, but last frame it was not
        /// \param key which device button is being checked
        /// \return true if just pressed
        [[nodiscard]] inline bool IsButtonJustPressed(MouseButtonType key)
        {
            auto index = static_cast<unsigned int>(key);
            return ButtonsValue[index] && !LastButtonsValue[index];
        }

        /// Check if Keyboard button was just released
        /// Just released means that it is not currently pressed, but last frame it was
        /// \param key which device button is being checked
        /// \return true if just released
        [[nodiscard]] inline bool IsButtonJustReleased(MouseButtonType key)
        {
            auto index = static_cast<unsigned int>(key);
            return !ButtonsValue[index] && LastButtonsValue[index];
        }

        /// Get the first/any pressed button we can find
        /// \return the first pressed button or BUTTON_NONE if none is pressed
        inline MouseButtonType AnyJustPressedButton()
        {
            for(int i = 0 ; i < ButtonsValue.size() ; ++i)
            {
                if (ButtonsValue[i] && !LastButtonsValue[i]) return {MouseButtonType(i)};
            }

            return {MouseButtonType::BUTTON_NONE};
        }

        /// Get the current Mouse axis value
        /// \param axis which mouse axis is being checked
        /// \return axis value
        [[nodiscard]] inline const float& GetAxis(MouseAxisType axis)
        {
            return AxisValue[(int)axis];
        }

        /// Check if axis had a movement from last frame
        /// It has moved if an Axis value difference from last frame to this is greater than epsilon
        /// \param axis which device axis is being checked
        /// \return true if moved
        [[nodiscard]] inline bool HasAxisMoved(MouseAxisType axis)
        {
            constexpr const float epsilon = std::numeric_limits<float>::epsilon();
            return std::abs(AxisValue[(int)axis] - LastAxisValue[(int)axis]) > epsilon;
        }

        /// Check if axis had a movement from last frame
        /// It has moved if an Axis value difference from last frame to this is greater than epsilon
        /// \param axis which axis is being checked
        /// \return true if moved
        [[nodiscard]] inline MouseAxisType AnyAxisMoved()
        {
            for (int i = 0 ; i < (int)MouseAxisType::Count ; ++i)
            {
                auto axis = MouseAxisType(i);
                if (HasAxisMoved(axis)) return axis;
            }
            return MouseAxisType::AXIS_NONE;
        }

        /// Check if stick had a movement from last frame
        /// It has moved if any Axis value difference from last frame to this is greater than epsilon
        /// \param stick which device axis is being checked
        /// \return true if moved
        [[nodiscard]] inline bool HasStickMoved(MouseStickType stick)
        {
            constexpr const float epsilon = std::numeric_limits<float>::epsilon();
            int stickIndex = (int)stick;
            auto currentStick = StickValue[stickIndex];
            auto lastStick = LastStickValue[stickIndex];
            return std::abs(currentStick.Horizontal - lastStick.Horizontal) > epsilon || std::abs(currentStick.Vertical - lastStick.Vertical) > epsilon;
        }

        /// Get the current Mouse stick value
        /// \param stick which device stick is being checked
        /// \return stick value
        [[nodiscard]] inline const InputVector& GetStick(MouseStickType stick)
        {
            return StickValue[(int)stick];
        }
    };

} // Sparkle

#endif //SPARKLEINPUT_MOUSECONTROLLER_H
