//
// Created by z3r0_ on 08/09/2025.
//

#include "Sparkle/PlayerInputController.h"
#include "GamepadInputProcess.h"
#include "Sparkle/GamepadController.h"
#include "Sparkle/Input.h"

namespace Sparkle {
    unsigned int Sparkle::GamepadInputProcessHandler::GetPlayerInputIndex()
    {
        // TODO: Fix this issue
        return -1;
    }

    bool GamepadStickInputProcess::UpdateInput(const InputGamepadStickEvent &event, const InputAction &action)
    {
        if (std::shared_ptr<Sparkle::GamepadController> gamepadController = GamepadController.lock())
        {
            std::map<GamepadStick, std::vector<GamepadAxis>> stickAxis =
                    {
                            {GamepadStick::STICK_LEFT, {GamepadAxis::AXIS_LEFT_X, GamepadAxis::AXIS_LEFT_Y}},
                            {GamepadStick::STICK_RIGHT, {GamepadAxis::AXIS_RIGHT_X, GamepadAxis::AXIS_RIGHT_Y}}
                    };
            Vector2 axisValue = { 0, 0 };
            const std::vector<GamepadAxis>& axisAnalyses = stickAxis[event.Stick];
            int i = 0;
            bool triggerCallback = false;
            for (auto& axisEnum : axisAnalyses)
            {
                bool hasAxisMoved = gamepadController->HasAxisMoved(axisEnum);
                float axis = gamepadController->GetAxis(axisEnum);
                axisValue[i++] = axis;
                if (i > 2) throw std::runtime_error("We don't support stick with more than 2 axis");
                if (hasAxisMoved && event.StickTrigger == InputStickEventTrigger::MOVEMENT
                    || axis >= 0.95 && event.StickTrigger == InputStickEventTrigger::FULL_POSITIVE
                    || axis <= -0.95 && event.StickTrigger == InputStickEventTrigger::FULL_NEGATIVE)

                {
                    triggerCallback = true;
                }
            }
            if (triggerCallback)
            {
                auto it = InputMapCallback.find(action);
                if (it != InputMapCallback.end())
                {
                    it->second.Raise(GetPlayerInputIndex(), axisValue, action, event);
                }
            }
            return true;
        }
        return false;
    }

    bool GamepadButtonInputProcess::UpdateInput(const InputGamepadButtonEvent &event, const InputAction &action)
    {
        if (std::shared_ptr<Sparkle::GamepadController> gamepadController = GamepadController.lock())
        {
            bool isButtonJustPressed = gamepadController->IsButtonJustPressed(event.Button);
            bool isButtonJustReleased = gamepadController->IsButtonJustReleased(event.Button);
            if (isButtonJustPressed && event.ButtonTrigger == InputButtonEventTrigger::JUST_PRESSED
                || isButtonJustReleased && event.ButtonTrigger == InputButtonEventTrigger::JUST_RELEASED
                || gamepadController->IsButtonPressed(event.Button) && event.ButtonTrigger == InputButtonEventTrigger::HOLDING_DOWN
                || !gamepadController->IsButtonPressed(event.Button) && event.ButtonTrigger == InputButtonEventTrigger::UP)
            {
                auto it = InputMapCallback.find(action);
                if (it != InputMapCallback.end())
                {
                    it->second.Raise(GetPlayerInputIndex(), action, event);
                }
                return true;
            }
        }
        return false;
    }

    bool GamepadAxisInputProcess::UpdateInput(const InputGamepadAxisEvent &event, const InputAction &action)
    {
        if (std::shared_ptr<Sparkle::GamepadController> gamepadController = GamepadController.lock())
        {
            bool hasAxisMoved = gamepadController->HasAxisMoved(event.Axis);
            float axis = gamepadController->GetAxis(event.Axis);
            if (hasAxisMoved && event.AxisTrigger == InputAxisEventTrigger::MOVEMENT
                || axis >= 0.95 && event.AxisTrigger == InputAxisEventTrigger::FULL_POSITIVE
                || axis <= -0.95 && event.AxisTrigger == InputAxisEventTrigger::FULL_NEGATIVE)
            {
                auto it = InputMapCallback.find(action);
                if (it != InputMapCallback.end())
                {
                    it->second.Raise(GetPlayerInputIndex(), axis, action, event);
                }
                return true;
            }
        }
        return false;
    }
}