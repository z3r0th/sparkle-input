//
// Created by z3r0_ on 10/10/2025.
//

#ifndef SPARKLE_SOLUTION_KEYBOARDCONTROLLER_H
#define SPARKLE_SOLUTION_KEYBOARDCONTROLLER_H

#include <memory>
#include <array>

#include "Sparkle/Event.h"
#include "InputController.h"
#include "InputEvent.h"

namespace Sparkle
{
    class Input;
    class KeyboardInputProcess;
    class InputKeyboardButtonEvent;
    class KeyboardController : public std::enable_shared_from_this<KeyboardController>, public InputController
    {
        friend class Sparkle::Input;

    private:
        //TODO: change int to a smaller type
        std::array<bool, (int)KeyboardButton::Count> Buttons;
        std::array<bool, (int)KeyboardButton::Count> LastButtons;

        std::unique_ptr<KeyboardInputProcess> InputProcess;

    protected:
        bool ProcessInput(const InputEvent &event, const InputAction &action) override;
        void Update() override;

    public:
        explicit KeyboardController();
        virtual ~KeyboardController();

        void Initialize();

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

        EventBinder<const unsigned int&, const InputAction&, const InputKeyboardButtonEvent&>& BinderForButton(const InputAction& action);

        template<typename T>
        void RemoveBind(T *t);

        void Clear();
    };
}


#endif //SPARKLE_SOLUTION_KEYBOARDCONTROLLER_H
