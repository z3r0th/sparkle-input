//
// Created by z3r0_ on 10/10/2025.
//

#ifndef SPARKLE_SOLUTION_KEYBOARDINPUTPROCESS_H
#define SPARKLE_SOLUTION_KEYBOARDINPUTPROCESS_H

#include "Sparkle/Event.h"
#include "InputProcess.h"
#include "Sparkle/KeyboardController.h"

namespace Sparkle
{
    class KeyboardInputProcess : public InputProcess<Sparkle::InputEvent>
    {
    private:
        std::weak_ptr<KeyboardController> KeyboardController;
        Event<const unsigned int&, const InputAction&, const InputKeyboardButtonEvent&> OnKeyEvent;
    public:
        explicit KeyboardInputProcess() : KeyboardController() {}

        void SetKeyboardController(std::weak_ptr<class KeyboardController> keyboardController) { KeyboardController = keyboardController;}

        bool UpdateInput(const Sparkle::InputEvent &event, const InputAction &action) override
        {
            if (event.EventType != InputEventType::KeyboardButtonEventType) return false;
            const InputKeyboardButtonEvent& keyboardEvent = event.KeyboardButtonEvent;
            if (auto keyboardController = KeyboardController.lock())
            {
                bool isButtonJustPressed = keyboardController->IsButtonJustPressed(keyboardEvent.Button);
                bool isButtonJustReleased = keyboardController->IsButtonJustReleased(keyboardEvent.Button);
                if (isButtonJustPressed && keyboardEvent.ButtonTrigger == InputButtonEventTrigger::JUST_PRESSED
                    || isButtonJustReleased && keyboardEvent.ButtonTrigger == InputButtonEventTrigger::JUST_RELEASED
                    || keyboardController->IsButtonPressed(keyboardEvent.Button) && keyboardEvent.ButtonTrigger == InputButtonEventTrigger::HOLDING_DOWN
                    || !keyboardController->IsButtonPressed(keyboardEvent.Button) && keyboardEvent.ButtonTrigger == InputButtonEventTrigger::UP)
                {
                    OnKeyEvent(0, action, keyboardEvent);
                    return true;
                }
                // GET keyboard controller
                // Check the event trigger type (Pressed, Up, Holding, etc)
                // if the event trigger is the same as keyboard controller state (button A is pressed, for example)
                // raise the action and return true
            }

            return false;
        }

        EventBinder<const unsigned int&, const InputAction&, const InputKeyboardButtonEvent&>& BinderForButton(const InputAction& action)
        {
            return OnKeyEvent.GetBinder();
        }
    };

} // Sparkle

#endif //SPARKLE_SOLUTION_KEYBOARDINPUTPROCESS_H
