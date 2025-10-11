//
// Created by z3r0_ on 14/09/2025.
//

#include "InputProcess.h"

#ifndef SPARKLE_SOLUTION_GAMEPADINPUTPROCESS_H
#define SPARKLE_SOLUTION_GAMEPADINPUTPROCESS_H

struct Vector2 {float x; float y;
float& operator[](int index){return x;}};

namespace Sparkle
{
    class GamepadInputProcessHandler
    {
    protected:
        std::weak_ptr<Sparkle::PlayerInputController> PlayerInputController;
        std::weak_ptr<GamepadController> GetGamepadController();
        unsigned int GetPlayerInputIndex();
    public:
        GamepadInputProcessHandler() = default;
        explicit GamepadInputProcessHandler(const std::weak_ptr<Sparkle::PlayerInputController> controller):PlayerInputController(controller){}
        virtual void SetPlayerInputController(const std::weak_ptr<Sparkle::PlayerInputController> controller) { PlayerInputController = controller; }
    };

    template<class T>
    class GamepadInputProcessStrategy : public GamepadInputProcessHandler, public InputProcess<T>
    {
    public:
        virtual ~GamepadInputProcessStrategy() = default;
        GamepadInputProcessStrategy() = default;
        explicit GamepadInputProcessStrategy(const std::weak_ptr<Sparkle::PlayerInputController> controller) : GamepadInputProcessHandler(controller) {}
    };

    class GamepadButtonInputProcess : public GamepadInputProcessStrategy<InputGamepadButtonEvent>
    {
    private:
        std::map<InputAction, Event<const unsigned int&, const InputAction&, const InputGamepadButtonEvent&>> InputMapCallback{};

    public:
        GamepadButtonInputProcess():GamepadInputProcessStrategy() {}
        explicit GamepadButtonInputProcess(const std::weak_ptr<Sparkle::PlayerInputController> playerInputController): GamepadInputProcessStrategy(playerInputController) {}

        EventBinder<const unsigned int&, const InputAction&, const InputGamepadButtonEvent&>& BinderFor(const InputAction& action)
        {
            if (auto it = InputMapCallback.find(action) ; it == InputMapCallback.end())
            {
                InputMapCallback.try_emplace(action,
                                         Event<const unsigned int&, const InputAction &, const InputGamepadButtonEvent &>(action.GetName()));
            }
            if (auto it = InputMapCallback.find(action) ; it != InputMapCallback.end())
            {
                return it->second.GetBinder();
            }
            assert(false);
        }

        template<class F>
        void Bind(const InputAction& action, std::function<void(const unsigned int&, const InputAction&, const InputGamepadButtonEvent&)> function, F f)
        {
            if (!InputMapCallback.contains(action)) {
                InputMapCallback.emplace(action,
                                         Event<const unsigned int&, const InputAction &, const InputGamepadButtonEvent &>(
                                                 action.GetName()));
            }

            if (auto it = InputMapCallback.find(action) ; it != InputMapCallback.end())
            {
                auto& event = it->second;
                event.Bind(function, f);
            }
        }

        void Clear()
        {
            for (auto& pair : InputMapCallback)
            {
                pair.second.RemoveAll();
            }
            InputMapCallback.clear();
        }

        template<class F>
        void Remove(F* f)
        {
            if (f == nullptr) return;
            for (auto& pair : InputMapCallback)
            {
                pair.second.Remove(f);
            }
        }

        bool UpdateInput(const InputGamepadButtonEvent &event, const InputAction &action) override
        {
            if (std::shared_ptr<Sparkle::GamepadController> gamepadController = GetGamepadController().lock())
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
    };

    class GamepadAxisInputProcess : public GamepadInputProcessStrategy<InputGamepadAxisEvent>
    {
    private:
        std::map<InputAction, Event<const unsigned int&, const float&, const InputAction&, const InputGamepadAxisEvent&>> InputMapCallback{};

    public:
        GamepadAxisInputProcess():GamepadInputProcessStrategy() {}
        explicit GamepadAxisInputProcess(const std::weak_ptr<Sparkle::PlayerInputController> playerInputController): GamepadInputProcessStrategy(playerInputController) {}

        EventBinder<const unsigned int&, const float&, const InputAction&, const InputGamepadAxisEvent&>& BinderFor(const InputAction& action)
        {
            if (auto it = InputMapCallback.find(action) ; it == InputMapCallback.end())
            {
                InputMapCallback.emplace(action,
                                         Event<const unsigned int&, const float&, const InputAction&, const InputGamepadAxisEvent&>(action.GetName()));
            }
            if (auto it = InputMapCallback.find(action) ; it != InputMapCallback.end())
            {
                return it->second.GetBinder();
            }
            assert(false);
        }

        template<class F>
        void Bind(const InputAction& action, std::function<void(const unsigned int&, const float&, const InputAction&, const InputGamepadAxisEvent&)> function, F f)
        {
            if (!InputMapCallback.contains(action))
            {
                InputMapCallback.emplace(action,
                                         Event<const unsigned int&, const float&, const InputAction &, const InputGamepadAxisEvent &>(
                                                 action.GetName()));
            }

            if (auto it = InputMapCallback.find(action) ; it != InputMapCallback.end())
            {
                auto& event = it->second;
                event.Bind(function, f);
            }
        }

        void Clear()
        {
            for (auto& pair : InputMapCallback)
            {
                pair.second.RemoveAll();
            }
            InputMapCallback.clear();
        }

        template<class F>
        void Remove(F* f)
        {
            if (f == nullptr) return;
            for (auto& pair : InputMapCallback)
            {
                pair.second.Remove(f);
            }
        }

        bool UpdateInput(const InputGamepadAxisEvent &event, const InputAction &action) override
        {
            if (std::shared_ptr<Sparkle::GamepadController> gamepadController = GetGamepadController().lock())
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
    };

    class GamepadStickInputProcess : public GamepadInputProcessStrategy<InputGamepadStickEvent>
    {
    private:
        std::map<InputAction, Event<const unsigned int&, const Vector2&, const InputAction&, const InputGamepadStickEvent&>> InputMapCallback{};

    public:
        GamepadStickInputProcess():GamepadInputProcessStrategy() {}
        explicit GamepadStickInputProcess(const std::weak_ptr<Sparkle::PlayerInputController> playerInputController): GamepadInputProcessStrategy(playerInputController) {}

        EventBinder<const unsigned int&, const Vector2&, const InputAction&, const InputGamepadStickEvent&>& BinderFor(const InputAction& action)
        {
            if (auto it = InputMapCallback.find(action) ; it == InputMapCallback.end())
            {
                InputMapCallback.emplace(action,
                                         Event<const unsigned int&, const Vector2&, const InputAction&, const InputGamepadStickEvent&>(action.GetName()));
            }
            if (auto it = InputMapCallback.find(action) ; it != InputMapCallback.end())
            {
                return it->second.GetBinder();
            }
            assert(false);
        }

        template<class F>
        void Bind(const InputAction& action, std::function<void(const unsigned int&, const Vector2&, const InputAction&, const InputGamepadStickEvent&)> function, F f)
        {
            if (!InputMapCallback.contains(action))
            {
                InputMapCallback.emplace(action,
                                         Event<const unsigned int&, const Vector2&, const InputAction &, const InputGamepadStickEvent &>(
                                                 action.GetName()));
            }

            if (auto it = InputMapCallback.find(action) ; it != InputMapCallback.end())
            {
                auto& event = it->second;
                event.Bind(function, f);
            }
        }

        void Clear()
        {
            for (auto& pair : InputMapCallback)
            {
                pair.second.RemoveAll();
            }
            InputMapCallback.clear();
        }

        template<class F>
        void Remove(F* f)
        {
            if (f == nullptr) return;
            for (auto& pair : InputMapCallback)
            {
                pair.second.Remove(f);
            }
        }

        bool UpdateInput(const InputGamepadStickEvent &event, const InputAction &action) override
        {
            if (std::shared_ptr<Sparkle::GamepadController> gamepadController = GetGamepadController().lock())
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
    };

    class GamepadInputProcess : public GamepadInputProcessStrategy<Sparkle::InputEvent>
    {
    protected:
        GamepadButtonInputProcess ButtonInputProcess;
        GamepadStickInputProcess StickInputProcess;
        GamepadAxisInputProcess AxisInputProcess;

    public:
        GamepadInputProcess():GamepadInputProcessStrategy(),ButtonInputProcess(),StickInputProcess(),AxisInputProcess() {}
        [[maybe_unused]] explicit GamepadInputProcess(const std::weak_ptr<Sparkle::PlayerInputController> controller):GamepadInputProcessStrategy(controller),
        ButtonInputProcess(controller), StickInputProcess(controller), AxisInputProcess(controller)
        { }

        EventBinder<const unsigned int&, const InputAction&, const InputGamepadButtonEvent&>& BinderForButton(const InputAction& action)
        {
            return ButtonInputProcess.BinderFor(action);
        }

        EventBinder<const unsigned int&, const float&, const InputAction&, const InputGamepadAxisEvent&>& BinderForAxis(const InputAction& action)
        {
            return AxisInputProcess.BinderFor(action);
        }

        EventBinder<const unsigned int&, const Vector2&, const InputAction&, const InputGamepadStickEvent&>& BinderForStick(const InputAction& action)
        {
            return StickInputProcess.BinderFor(action);
        }

        template<typename T>
        void RemoveBind(T* t)
        {
            ButtonInputProcess.Remove(t);
            StickInputProcess.Remove(t);
            AxisInputProcess.Remove(t);
        }

        void Clear()
        {
            ButtonInputProcess.Clear();
            StickInputProcess.Clear();
            AxisInputProcess.Clear();
        }

        bool UpdateInput(const Sparkle::InputEvent &inputEvent, const InputAction &action) override
        {
            switch (inputEvent.EventType)
            {
                case InputEventType::GamePadButtonEventType:
                    return ButtonInputProcess.UpdateInput(inputEvent.ButtonEvent, action);
                case InputEventType::GamePadAxisEventType:
                    return AxisInputProcess.UpdateInput(inputEvent.AxisEvent, action);
                case InputEventType::GamePadStickEventType:
                    return StickInputProcess.UpdateInput(inputEvent.StickEvent, action);
                default:
                    return false;
            }
        }

        void SetPlayerInputController(const std::weak_ptr<Sparkle::PlayerInputController> controller) override
        {
            GamepadInputProcessStrategy<Sparkle::InputEvent>::SetPlayerInputController(controller);
            ButtonInputProcess.SetPlayerInputController(controller);
            StickInputProcess.SetPlayerInputController(controller);
            AxisInputProcess.SetPlayerInputController(controller);
        }
    };
}

#endif //SPARKLE_SOLUTION_GAMEPADINPUTPROCESS_H
