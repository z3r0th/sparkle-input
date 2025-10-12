//
// Created by z3r0_ on 14/09/2025.
//

#include "InputProcess.h"

#ifndef SPARKLE_SOLUTION_GAMEPADINPUTPROCESS_H
#define SPARKLE_SOLUTION_GAMEPADINPUTPROCESS_H

namespace Sparkle
{
    class GamepadController;
    class Vector2;
    class GamepadInputProcessHandler
    {
    protected:
        std::weak_ptr<Sparkle::GamepadController> GamepadController;
        unsigned int GetPlayerInputIndex();
    public:
        GamepadInputProcessHandler() = default;
        explicit GamepadInputProcessHandler(const std::weak_ptr<Sparkle::GamepadController> controller):GamepadController(controller){}
        virtual void SetGamepadController(const std::weak_ptr<Sparkle::GamepadController> controller) { GamepadController = controller; }
    };

    template<class T>
    class GamepadInputProcessStrategy : public GamepadInputProcessHandler, public InputProcess<T>
    {
    public:
        virtual ~GamepadInputProcessStrategy() = default;
        GamepadInputProcessStrategy() = default;
        explicit GamepadInputProcessStrategy(const std::weak_ptr<Sparkle::GamepadController> controller) : GamepadInputProcessHandler(controller) {}
    };

    class GamepadButtonInputProcess : public GamepadInputProcessStrategy<InputGamepadButtonEvent>
    {
    private:
        std::map<InputAction, Event<const unsigned int&, const InputAction&, const InputGamepadButtonEvent&>> InputMapCallback{};

    public:
        GamepadButtonInputProcess():GamepadInputProcessStrategy() {}
        explicit GamepadButtonInputProcess(const std::weak_ptr<Sparkle::GamepadController> playerInputController): GamepadInputProcessStrategy(playerInputController) {}

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

        bool UpdateInput(const InputGamepadButtonEvent &event, const InputAction &action) override;
    };

    class GamepadAxisInputProcess : public GamepadInputProcessStrategy<InputGamepadAxisEvent>
    {
    private:
        std::map<InputAction, Event<const unsigned int&, const float&, const InputAction&, const InputGamepadAxisEvent&>> InputMapCallback{};

    public:
        GamepadAxisInputProcess():GamepadInputProcessStrategy() {}
        explicit GamepadAxisInputProcess(const std::weak_ptr<Sparkle::GamepadController> GamepadController): GamepadInputProcessStrategy(GamepadController) {}

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

        bool UpdateInput(const InputGamepadAxisEvent &event, const InputAction &action) override;
    };

    class GamepadStickInputProcess : public GamepadInputProcessStrategy<InputGamepadStickEvent>
    {
    private:
        std::map<InputAction, Event<const unsigned int&, const Vector2&, const InputAction&, const InputGamepadStickEvent&>> InputMapCallback{};

    public:
        GamepadStickInputProcess():GamepadInputProcessStrategy() {}
        explicit GamepadStickInputProcess(const std::weak_ptr<Sparkle::GamepadController> GamepadController): GamepadInputProcessStrategy(GamepadController) {}

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

        bool UpdateInput(const InputGamepadStickEvent &event, const InputAction &action) override;
    };

    class GamepadInputProcess : public GamepadInputProcessStrategy<Sparkle::InputEvent>
    {
    protected:
        GamepadButtonInputProcess ButtonInputProcess;
        GamepadStickInputProcess StickInputProcess;
        GamepadAxisInputProcess AxisInputProcess;

    public:
        GamepadInputProcess():GamepadInputProcessStrategy(),ButtonInputProcess(),StickInputProcess(),AxisInputProcess() {}
        [[maybe_unused]] explicit GamepadInputProcess(const std::weak_ptr<Sparkle::GamepadController> controller):GamepadInputProcessStrategy(controller),
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

        void SetGamepadController(const std::weak_ptr<Sparkle::GamepadController> controller) override
        {
            GamepadInputProcessStrategy<Sparkle::InputEvent>::SetGamepadController(controller);
            ButtonInputProcess.SetGamepadController(controller);
            StickInputProcess.SetGamepadController(controller);
            AxisInputProcess.SetGamepadController(controller);
        }
    };
}

#endif //SPARKLE_SOLUTION_GAMEPADINPUTPROCESS_H
