#ifndef SPARKLE_SOLUTION_PLAYER_INPUT_CONTROLLER_H
#define SPARKLE_SOLUTION_PLAYER_INPUT_CONTROLLER_H

#include "Sparkle/Controller/KeyboardController.h"
#include "Sparkle/Controller/GamepadController.h"
#include "Sparkle/Event.h"
#include "InputMap.h"

#include <functional>
#include <utility>
#include <memory>
#include <string>
#include <map>

#define PLAYER_CONTROLLER_UPDATE_INPUT_MAP_EVENT_NAME "__PLAYER_CONTROLLER_UPDATE_INPUT_MAP_EVENT__"
#define PLAYER_CONTROLLER_DISCONNECTED_EVENT_NAME "__PLAYER_CONTROLLER_DISCONNECTED_EVENT__"
#define PLAYER_CONTROLLER_CONNECTED_EVENT_NAME "__PLAYER_CONTROLLER_CONNECTED_EVENT__"

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

        std::map<InputAction, Event<const std::weak_ptr<PlayerInputController>, InputAction, InputState>> ActionEventMap;

        bool RequestKeyboard = false;
        bool RequestGamepad = false;

        Sparkle::InputMap InputMap;

        Event<const std::weak_ptr<PlayerInputController>> OnGamepadDisconnectedEvent;
        Event<const std::weak_ptr<PlayerInputController>> OnGamepadConnectedEvent;
        Event<const std::weak_ptr<PlayerInputController>> OnInputMapUpdatedEvent;

        /// Private constructor that Input (friend class) can access
        explicit PlayerInputController(unsigned int index) :
                PlayerInputIndex(index),
                OnGamepadConnectedEvent(std::string(PLAYER_CONTROLLER_CONNECTED_EVENT_NAME) + std::to_string(index)),
                OnGamepadDisconnectedEvent(std::string(PLAYER_CONTROLLER_DISCONNECTED_EVENT_NAME) + std::to_string(index)),
                OnInputMapUpdatedEvent(std::string(PLAYER_CONTROLLER_UPDATE_INPUT_MAP_EVENT_NAME) + std::to_string(index))
        { }

        /// Called from Input when a gamepad is connected (or assigning an active GamepadController)
        void OnGamepadConnected(const std::weak_ptr<Sparkle::GamepadController>&) { OnGamepadConnectedEvent.Raise(weak_from_this()); }

        /// Called from Input when a gamepad is disconnected (or removing the GamepadController)
        void OnGamepadDisconnected(const std::weak_ptr<Sparkle::GamepadController>&) { OnGamepadDisconnectedEvent.Raise(weak_from_this()); }

        /// Process events from input map checking assigned devices status and raising bind callbacks
        void Update();

        /// Assigns the gamepadController and connects to the events.
        /// If the GamepadController is active, raises the `OnGamepadConnectedEvent`
        /// \param gamepadController to assign
        void SetGamepadController(const std::weak_ptr<Sparkle::GamepadController>& gamepadController);

        /// Disconnects from events and sets the GamepadController to null (reset)
        /// Raises `OnGamepadDisconnectedEvent`
        void RemoveGamepadController();

        void SetKeyboardController(const std::weak_ptr<Sparkle::KeyboardController>& keyboardController);

        void RemoveKeyboardController();

    public:
        /// Bind to the action
        EventBinder<const std::weak_ptr<PlayerInputController>, InputAction, InputState>& OnAction(const InputAction&);

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
        [[maybe_unused]] [[nodiscard]] const Sparkle::InputMap& GetInputMap() const { return InputMap; }

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
        [[maybe_unused]] [[nodiscard]] EventBinder<const std::weak_ptr<PlayerInputController>>& OnInputMapUpdated() { return OnInputMapUpdatedEvent.GetBinder(); }

#pragma endregion InputMap

#pragma region Gamepad Methods

    public:

        /// GetGamepadController
        /// The gamepad might not exist (nullptr) and/or might not be connected or valid
        /// \return weak ptr to GamepadController
        [[maybe_unused]] [[nodiscard]] std::weak_ptr<Sparkle::GamepadController> GetGamepadController() const { return GamepadController; }

        /// Requests a controller to the Input.
        /// When a controller is available it will be assign to this PlayerInputController and the OnGamepadConnected callback will be called
        inline void AssignGamepad()
        {
            RequestGamepad = true;
        }

        /// Requests a keyboard to the Input.
        /// When a controller is available it will be assign to this PlayerInputController and the OnGamepadConnected callback will be called
        inline void AssignKeyboard()
        {
            RequestKeyboard = true;
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
        [[maybe_unused]] [[nodiscard]] EventBinder<const std::weak_ptr<PlayerInputController>>& OnGamepadDisconnected() { return OnGamepadDisconnectedEvent.GetBinder(); }

        /// Binding to Gamepad Connected event
        /// The controller might already be connected before you binding to it (and this event won't be triggered again - unless disconnected and connected again)
        /// use IsGamepadConnected to check if needed
        /// \example OnGamepadConnected().Bind(&Class::Method, &object)
        /// \example OnGamepadConnected().Bind([](const std::weak_ptr<PlayerInputController>){...})
        /// \return EventBinder for OnGamepadConnected
        [[maybe_unused]] [[nodiscard]] EventBinder<const std::weak_ptr<PlayerInputController>>& OnGamepadConnected() { return OnGamepadConnectedEvent.GetBinder(); }

#pragma endregion Gamepad Methods

        /// Clears all callbacks including input connection, input map update and gamepad/kbm input
        [[maybe_unused]] void Clear()
        {
            ActionEventMap.clear();
            OnGamepadDisconnectedEvent.RemoveAll();
            OnGamepadConnectedEvent.RemoveAll();
            OnInputMapUpdatedEvent.RemoveAll();
        }
    };

} // Sparkle

#endif //SPARKLE_SOLUTION_PLAYER_INPUT_CONTROLLER_H
