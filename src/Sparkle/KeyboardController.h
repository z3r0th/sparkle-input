//
// Created by z3r0_ on 10/10/2025.
//

#ifndef SPARKLE_SOLUTION_KEYBOARDCONTROLLER_H
#define SPARKLE_SOLUTION_KEYBOARDCONTROLLER_H

#include <memory>
#include "InputController.h"
#include "InputEvent.h"
#include <array>

namespace Sparkle
{
    class Input;
    class KeyboardController : std::enable_shared_from_this<KeyboardController>, public InputController
    {
        friend class Sparkle::Input;

    private:
        //TODO: change int to a smaller type
        std::array<bool, (int)KeyboardButton::Count> Buttons;
        std::array<bool, (int)KeyboardButton::Count> LastButtons;

    protected:
        void Update() override;

    public:
        explicit KeyboardController() : Buttons(), LastButtons()
        {
            std::fill(LastButtons.begin(), LastButtons.end(), false);
            std::fill(Buttons.begin(), Buttons.end(), false);
        }
        inline bool IsActive() override { return true; }

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
