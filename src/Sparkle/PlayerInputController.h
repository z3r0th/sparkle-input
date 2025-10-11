#ifndef SPARKLE_SOLUTION_PLAYER_INPUT_CONTROLLER_H
#define SPARKLE_SOLUTION_PLAYER_INPUT_CONTROLLER_H

#include "input_process/GamepadInputProcess.h"
#include "GamepadController.h"
#include "InputMap.h"
#include "KeyboardController.h"
#include "input_process/KeyboardInputProcess.h"
#include <Sparkle/Event.h>

#include <memory>
#include <functional>
#include <utility>
#include <string>
#include <map>

#define PLAYER_CONTROLLER_UPDATE_INPUT_MAP_EVENT_NAME "__PLAYER_CONTROLLER_UPDATE_INPUT_MAP_EVENT__"
#define PLAYER_CONTROLLER_DISCONNECTED_EVENT_NAME "__PLAYER_CONTROLLER_DISCONNECTED_EVENT__"
#define PLAYER_CONTROLLER_CONNECTED_EVENT_NAME "__PLAYER_CONTROLLER_CONNECTED_EVENT__"

//TODO: Implement Keyboard and Mouse (assign and process input)

namespace Sparkle
{
    class Input;

    ///
    /// PlayerInputController holds player's input (a Gamepad and/or keyboard and mouse (KBM)).
    /// We can map actions to callbacks to how to handle it
    /// Use an InputMap to map the input to a physical button and its trigger. For example bind
    /// Action `Jump` when `Button A` is released on a gamepad and bind Action `Jump` to key `Space` when release
    /// and so on.
    /// Use `Button` for pressed and release (gamepad/keyboard/mouseclick)
    /// Use `Axis` for a single direction (Gamepad Horizontal Stick, Gamepad Left Trigger, Horizontal Mouse Movement...)
    /// Use `Stick` for Axis 2 direction (Left Stick, Mouse Movement)
    ///
    class PlayerInputController : public std::enable_shared_from_this<PlayerInputController>
    {
        /// The `Input` class manages the `PlayerInputController` lifetime (create and destroy)
        /// and also the Input Process object update
        friend class Sparkle::Input;

    private:
        unsigned int PlayerInputIndex = -1;

        std::shared_ptr<KeyboardController> KeyboardController = nullptr;
        std::shared_ptr<GamepadController> GamepadController = nullptr;
        KeyboardInputProcess KeyboardInputProcess;
        GamepadInputProcess GamepadInputProcess;
        bool RequestGamepad = false;

        Sparkle::InputMap InputMap;

        Event<const std::weak_ptr<PlayerInputController>> OnGamepadDisconnectedEvent;
        Event<const std::weak_ptr<PlayerInputController>> OnGamepadConnectedEvent;
        Event<const std::weak_ptr<PlayerInputController>> OnInputMapUpdatedEvent;

        /// Private constructor that Input (friend class) can access
        explicit PlayerInputController(unsigned int index) :
                GamepadInputProcess(),
                KeyboardInputProcess(),
                PlayerInputIndex(index),
                OnGamepadConnectedEvent(std::string(PLAYER_CONTROLLER_CONNECTED_EVENT_NAME) + std::to_string(index)),
                OnGamepadDisconnectedEvent(std::string(PLAYER_CONTROLLER_DISCONNECTED_EVENT_NAME) + std::to_string(index)),
                OnInputMapUpdatedEvent(std::string(PLAYER_CONTROLLER_UPDATE_INPUT_MAP_EVENT_NAME) + std::to_string(index))
        { }

        /// Called from Input when a gamepad is connected (or assigning an active GamepadController)
        void OnGamepadConnected(std::weak_ptr<Sparkle::GamepadController>) { OnGamepadConnectedEvent.Raise(weak_from_this()); }

        /// Called from Input when a gamepad is disconnected (or removing the GamepadController)
        void OnGamepadDisconnected(std::weak_ptr<Sparkle::GamepadController>) { OnGamepadDisconnectedEvent.Raise(weak_from_this()); }

        /// Process events from input map checking assigned devices status and raising bind callbacks
        void Update();

        /// Assigns the gamepadController and connects to the events.
        /// If the GamepadController is active, raises the `OnGamepadConnectedEvent`
        /// \param gamepadController to assign
        void SetGamepadController(std::weak_ptr<Sparkle::GamepadController> gamepadController);

        /// Disconnects from events and sets the GamepadController to null (reset)
        /// Raises `OnGamepadDisconnectedEvent`
        void RemoveGamepadController();

        /// Initialize the PlayerInputController.
        /// Some of the properties are only ready after the constructor finishes - like the weak_from_this()
        /// This method must be called just after the Constructor from the Input class (same frame)
        void Initialize();

    public:
        /// PlayerInputController cannot be directly created, get it from Input
        PlayerInputController() = delete;

        /// Get this Player Input Controller Index.
        /// The index should always be valid and greater than -1
        /// This is the index of this player controller and should not be confused with gamepad, kbm or any other input index
        /// \return PlayerInputIndex
        [[nodiscard]] unsigned int GetPlayerInputIndex() const { return PlayerInputIndex; }

#pragma region InputMap

    public:
        /// Gets the current input map
        /// \return InputMap const reference
        [[nodiscard]] const Sparkle::InputMap& GetInputMap() const { return InputMap; }

        /// Set a new input map.
        /// \related Raise the Event OnInputMapUpdated
        /// \param inputMap
        inline void SetInputMap(Sparkle::InputMap inputMap)
        {
            InputMap = std::move(inputMap);
            OnInputMapUpdatedEvent.Raise(weak_from_this());
        }

        /// Binding OnInputMapUpdated event
        /// \example OnInputMapUpdated().Bind(&Class::Method, &object);
        /// \example OnInputMapUpdated().Bind([](const std::weak_ptr<PlayerInputController>){...})
        /// \return EventBinder for OnInputMapUpdated
        EventBinder<const std::weak_ptr<PlayerInputController>>& OnInputMapUpdated() { return OnInputMapUpdatedEvent.GetBinder(); }

#pragma endregion InputMap

#pragma region Gamepad Methods

    public:

        /// GetGamepadController
        /// The gamepad might not exist (nullptr) and/or might not be connected or valid
        /// \return weak ptr to GamepadController
        [[nodiscard]] std::weak_ptr<Sparkle::GamepadController> GetGamepadController() const { return GamepadController; }

        /// Requests a controller to the Input.
        /// When a controller is available it will be assign to this PlayerInputController and the OnGamepadConnected callback will be called
        inline void AssignGamepad()
        {
            RequestGamepad = true;
        }

        /// Is this PlayerInputController's Gamepad assigned active and connected
        /// \return
        [[maybe_unused]] [[nodiscard]] bool IsGamepadConnected() { return IsGamepadAssigned() && GamepadController->IsActive(); }

        /// Does this PlayerInputController has a gamepad assigned
        /// \return
        [[nodiscard]] bool IsGamepadAssigned() { return GamepadController != nullptr; }

        /// Binding to Gamepad Disconnected event
        /// \example OnGamepadDisconnected().Bind(&Class::Method, &object);
        /// \example OnGamepadDisconnected().Bind([](const std::weak_ptr<PlayerInputController>){...})
        /// \return EventBinder for OnGamepadDisconnected
        EventBinder<const std::weak_ptr<PlayerInputController>>& OnGamepadDisconnected() { return OnGamepadDisconnectedEvent.GetBinder(); }

        /// Binding to Gamepad Connected event
        /// The controller might already be connected before you binding to it (and this event won't be triggered again - unless disconnected and connected again)
        /// use IsGamepadConnected to check if needed
        /// \example OnGamepadConnected().Bind(&Class::Method, &object)
        /// \example OnGamepadConnected().Bind([](const std::weak_ptr<PlayerInputController>){...})
        /// \return EventBinder for OnGamepadConnected
        EventBinder<const std::weak_ptr<PlayerInputController>>& OnGamepadConnected() { return OnGamepadConnectedEvent.GetBinder(); }

        /// Binding to Gamepad Button event for the specific InputAction
        /// The Event will be raised depending on how the button/action were map on \class InputMap
        /// \example OnGamepadButton().Bind(&Class::Method, &object)
        /// \example OnGamepadButton().Bind([](const unsigned int&, const Sparkle::InputAction&, const Sparkle::InputGamepadButtonEvent&){...})
        /// \param action that the button event will respond to
        /// \return EventBinder for OnGamepadButton
        EventBinder<const unsigned int&, const Sparkle::InputAction&, const Sparkle::InputGamepadButtonEvent&>& OnGamepadButton(const InputAction& action)
        {
            return GamepadInputProcess.BinderForButton(action);
        }

        /// Binding to Gamepad Axis event for the specific InputAction
        /// The Event will be raised depending on how the axis/action were map on \class InputMap
        /// Axis are a float (that can be from -1 to 1 or 0 to 1 depending if they represent a full range movement or a trigger (gamepad trigger))
        /// Axis represent a movement range (LEFT STICK HORIZONTAL or LEFT TRIGGER for example)
        /// \example OnGamepadAxis().Bind(&Class::Method, &object)
        /// \example OnGamepadAxis().Bind([](const unsigned int&, const float&, const Sparkle::InputAction&, const Sparkle::InputGamepadAxisEvent&){...})
        /// \param action that the axis event will respond to
        /// \return EventBinder for OnGamepadAxis
        EventBinder<const unsigned int&, const float&, const Sparkle::InputAction&, const Sparkle::InputGamepadAxisEvent&>& OnGamepadAxis(const InputAction& action)
        {
            return GamepadInputProcess.BinderForAxis(action);
        }

        /// Binding to Gamepad Stick event for the specific InputAction
        /// The Event will be raised depending on how the stick/action were map on \class InputMap
        /// Stick are a Vector2 (pair of float (x,y) ranging from -1 to 1).
        /// Stick represent a full movement in two direction - Typically known as left or right stick on a gamepad
        /// \example OnGamepadAxis().Bind(&Class::Method, &object)
        /// \example OnGamepadAxis().Bind([](const unsigned int&, const Vector2&, const Sparkle::InputAction&, const Sparkle::InputGamepadStickEvent&){...})
        /// \param action that the stick event will respond to
        /// \return EventBinder for OnGamepadStick
        EventBinder<const unsigned int&, const Vector2&, const InputAction&, const Sparkle::InputGamepadStickEvent&>& OnGamepadStick(const InputAction& action)
        {
            return GamepadInputProcess.BinderForStick(action);
        }

#pragma endregion Gamepad Methods

        EventBinder<const unsigned int&, const Sparkle::InputAction&, const Sparkle::InputKeyboardButtonEvent&>& OnKeyboardButton(const InputAction& action)
        {
            return KeyboardInputProcess.BinderForButton(action);
        }

        /// Clears all callbacks including input connection, input map update and gamepad/kbm input
        void Clear()
        {
            OnGamepadDisconnectedEvent.RemoveAll();
            OnGamepadConnectedEvent.RemoveAll();
            OnInputMapUpdatedEvent.RemoveAll();
            GamepadInputProcess.Clear();
        }

        /// Removes all callbacks for the `t` object related to this PlayerInputController callbacks
        /// Including input connection, input map update and gamepad/kbm input
        /// \param t the object to remove from events
        template<typename T>
        [[maybe_unused]] void RemoveBind(T* const t)
        {
            GamepadInputProcess.RemoveBind(t);
            OnGamepadDisconnectedEvent.Remove(t);
            OnGamepadConnectedEvent.Remove(t);
            OnInputMapUpdatedEvent.Remove(t);
        }

    };

} // Sparkle

#endif //SPARKLE_SOLUTION_PLAYER_INPUT_CONTROLLER_H
