//
// Created by z3r0_ on 14/09/2025.
//

#include "Sparkle/InputEvent.h"

#ifndef SPARKLE_SOLUTION_GAMEPADINPUTPROCESS_H
#define SPARKLE_SOLUTION_GAMEPADINPUTPROCESS_H

namespace Sparkle
{

    class GamepadController;
    class GamepadInputProcessHandler
    {
    protected:
        Sparkle::GamepadController* GamepadController;
    public:
        explicit GamepadInputProcessHandler(Sparkle::GamepadController* controller):GamepadController(controller){}
    };

    template<class T>
    class GamepadInputProcessStrategy : public GamepadInputProcessHandler
    {
    public:
        virtual ~GamepadInputProcessStrategy() = default;
        explicit GamepadInputProcessStrategy(Sparkle::GamepadController* controller) : GamepadInputProcessHandler(controller) {}
        virtual Sparkle::InputResult ProcessEvent(const T &inputEvent) = 0;
    };

    class GamepadButtonInputProcess : public GamepadInputProcessStrategy<InputGamepadButtonEvent>
    {
    public:
        explicit GamepadButtonInputProcess(Sparkle::GamepadController* playerInputController): GamepadInputProcessStrategy(playerInputController) {}
        Sparkle::InputResult ProcessEvent(const InputGamepadButtonEvent &event) override;
    };

    class GamepadAxisInputProcess : public GamepadInputProcessStrategy<InputGamepadAxisEvent>
    {
    public:
        explicit GamepadAxisInputProcess(Sparkle::GamepadController* GamepadController): GamepadInputProcessStrategy(GamepadController) {}
        Sparkle::InputResult ProcessEvent(const InputGamepadAxisEvent &event) override;
    };

    class GamepadStickInputProcess : public GamepadInputProcessStrategy<InputGamepadStickEvent>
    {
    public:
        explicit GamepadStickInputProcess(Sparkle::GamepadController* GamepadController): GamepadInputProcessStrategy(GamepadController) {}
        Sparkle::InputResult ProcessEvent(const InputGamepadStickEvent &event) override;
    };

    class GamepadInputProcess : public GamepadInputProcessStrategy<Sparkle::InputTrigger>
    {
    protected:
        GamepadButtonInputProcess ButtonInputProcess;
        GamepadStickInputProcess StickInputProcess;
        GamepadAxisInputProcess AxisInputProcess;

    public:
        [[maybe_unused]] explicit GamepadInputProcess(Sparkle::GamepadController* controller):GamepadInputProcessStrategy(controller),
        ButtonInputProcess(controller), StickInputProcess(controller), AxisInputProcess(controller)
        { }

        Sparkle::InputResult ProcessEvent(const Sparkle::InputTrigger &inputEvent) override
        {
            switch (inputEvent.EventType)
            {
                case InputEventType::GamePadButtonEventType:
                    return ButtonInputProcess.ProcessEvent(inputEvent.Event.ButtonEvent);
                case InputEventType::GamePadAxisEventType:
                    return AxisInputProcess.ProcessEvent(inputEvent.Event.AxisEvent);
                case InputEventType::GamePadStickEventType:
                    return StickInputProcess.ProcessEvent(inputEvent.Event.StickEvent);
                default:
                    return Sparkle::InputResult{false};
            }
        }
    };
}

#endif //SPARKLE_SOLUTION_GAMEPADINPUTPROCESS_H
