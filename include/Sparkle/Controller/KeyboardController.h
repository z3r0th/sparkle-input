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

    // TODO: Type text mode, modifier type, state check (capslock for example)
    class KeyboardController : public InputController
    {
        // Input updates the buttons
        friend class Sparkle::Input;

    private:
        std::array<bool, (int)KeyboardButton::Count> Buttons;
        std::array<bool, (int)KeyboardButton::Count> LastButtons;

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
        [[nodiscard]] inline bool IsButtonPressed(KeyboardButton key)
        {
            return Buttons[static_cast<unsigned int>(key)];
        }

        /// Check if Keyboard button was just pressed
        /// Just pressed means that it is currently pressed, but last frame it was not
        /// \param key which device button is being checked
        /// \return true if just pressed
        [[nodiscard]] inline bool IsButtonJustPressed(KeyboardButton key)
        {
            auto index = static_cast<unsigned int>(key);
            return Buttons[index] && !LastButtons[index];
        }

        /// Check if Keyboard button was just released
        /// Just released means that it is not currently pressed, but last frame it was
        /// \param key which device button is being checked
        /// \return true if just released
        [[nodiscard]] inline bool IsButtonJustReleased(KeyboardButton key)
        {
            auto index = static_cast<unsigned int>(key);
            return !Buttons[index] && LastButtons[index];
        }
    };
}


#endif //SPARKLE_SOLUTION_KEYBOARDCONTROLLER_H
