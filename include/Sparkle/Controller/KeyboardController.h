//
// Created by z3r0_ on 10/10/2025.
//

#ifndef SPARKLE_SOLUTION_KEYBOARDCONTROLLER_H
#define SPARKLE_SOLUTION_KEYBOARDCONTROLLER_H

#include <cstdint>
#include <array>

#include "Sparkle/InputController.h"
#include "Sparkle/InputEvent.h"

namespace Sparkle
{
    class Input;

    class KeyboardController : public InputController
    {
        // Input updates the buttons
        friend class Sparkle::Input;

    private:
        std::array<bool, (int)KeyboardButtonType::Count> ButtonsValue;
        std::array<bool, (int)KeyboardButtonType::Count> LastButtonsValue;

    protected:
        void Update() override;
        InputResult ProcessButton(const InputKeyboardButtonEvent& event);
        InputResult ProcessAxis(const InputKeyboardAxisEvent& event);
        InputResult ProcessStick(const InputKeyboardStickEvent& event);

    public:
        explicit KeyboardController();

        inline bool IsActive() override { return true; }

        InputResult ProcessEvent(const Sparkle::InputTrigger &event);

        /// Check if Keyboard button is pressed
        /// Keyboard Buttons are updated on Input update
        /// \param key which device button is being checked
        /// \return true if button is currently pressed
        [[nodiscard]] inline bool IsButtonPressed(KeyboardButtonType key)
        {
            return ButtonsValue[static_cast<unsigned int>(key)];
        }

        /// Check if Keyboard button was just pressed
        /// Just pressed means that it is currently pressed, but last frame it was not
        /// \param key which device button is being checked
        /// \return true if just pressed
        [[nodiscard]] inline bool IsButtonJustPressed(KeyboardButtonType key)
        {
            auto index = static_cast<unsigned int>(key);
            return ButtonsValue[index] && !LastButtonsValue[index];
        }

        /// Check if Keyboard button was just released
        /// Just released means that it is not currently pressed, but last frame it was
        /// \param key which device button is being checked
        /// \return true if just released
        [[nodiscard]] inline bool IsButtonJustReleased(KeyboardButtonType key)
        {
            auto index = static_cast<unsigned int>(key);
            return !ButtonsValue[index] && LastButtonsValue[index];
        }

        /// Get the first/any pressed button we can find
        /// \return the first pressed button or BUTTON_NONE if none is pressed
        inline KeyboardButtonType AnyJustPressedButton()
        {
            for(int i = 0 ; i < ButtonsValue.size() ; ++i)
            {
                if (ButtonsValue[i] && !LastButtonsValue[i]) return {KeyboardButtonType(i)};
            }

            return {KeyboardButtonType::KEY_NONE};
        }

        /// Get the current Keyboard axis value
        /// \param axis which device axis is being checked
        /// \return axis value
        float GetAxis(KeyboardAxisType);

        /// Get the current Keyboard stick value
        /// \param stick which device stick is being checked
        /// \return stick value
        Stick GetStick(Sparkle::KeyboardStickType stick);
    };
}


#endif //SPARKLE_SOLUTION_KEYBOARDCONTROLLER_H
