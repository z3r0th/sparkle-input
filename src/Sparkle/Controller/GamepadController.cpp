//
// Created by z3r0_ on 15/01/2024.
//

#include "Sparkle/Controller/GamepadController.h"
#include <SDL.h>

void Sparkle::GamepadController::ClearController()
{
    InternalGameController = nullptr;

    std::weak_ptr<GamepadController> weak_this = weak_from_this();
    OnDisconnectedEvent.Raise(weak_this);

    std::fill(ButtonsValue.begin(), ButtonsValue.end(), false);
    std::fill(LastButtonsValue.begin(), LastButtonsValue.end(), false);

    std::fill(AxisValue.begin(), AxisValue.end(), false);
    std::fill(LastAxisValue.begin(), LastAxisValue.end(), false);

    InputVector emptyStick{};
    std::fill(StickValue.begin(), StickValue.end(), emptyStick);
    std::fill(LastStickValue.begin(), LastStickValue.end(), emptyStick);
}

void Sparkle::GamepadController::SetController(SDL_GameController *controller, int deviceIndex)
{
    assert(InternalGameController == nullptr);
    if (InternalGameController != nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GamepadController, should NEVER set controller with one currently open. Abort this.");
        return;
    }

    InternalGameController = controller;
    DeviceIndex = deviceIndex;

    std::weak_ptr<GamepadController> weak_this = weak_from_this();
    OnConnectedEvent.Raise(weak_this);
}

void Sparkle::GamepadController::Update() {
    // apply a dead_zone of 2% movement for now. This should be configurable in the future
    constexpr const float DEAD_ZONE = 2.0f / 100.0f;
    
    if (!IsActive())
    {
        return;
    }

    for (unsigned int i = 0 ; i < static_cast<int>(GamepadButtonType::Count) ; ++i)
    {
        LastButtonsValue[i] = ButtonsValue[i];
        ButtonsValue[i] = SDL_GameControllerGetButton(InternalGameController, static_cast<SDL_GameControllerButton>(i));
    }

    for (unsigned int i = 0 ; i < static_cast<int>(GamepadAxisType::Count) ; ++i)
    {
        LastAxisValue[i] = AxisValue[i];
        float axis = (float)(SDL_GameControllerGetAxis(InternalGameController, static_cast<SDL_GameControllerAxis>(i))) / (float)(SDL_MAX_SINT16);
        if (abs(axis) <= DEAD_ZONE)
        {
            axis = 0.0;
        }
        AxisValue[i] = axis;
    }

    for (unsigned int i = 0 ; i < static_cast<int>(GamepadStickType::Count) ; ++i)
    {
        static const std::map<GamepadStickType, const std::vector<GamepadAxisType>> StickAxis =
        {
            {GamepadStickType::STICK_LEFT,  {GamepadAxisType::AXIS_LEFT_X,  GamepadAxisType::AXIS_LEFT_Y}},
            {GamepadStickType::STICK_RIGHT, {GamepadAxisType::AXIS_RIGHT_X, GamepadAxisType::AXIS_RIGHT_Y}}
        };
        LastStickValue[i] = StickValue[i];
        auto UpdateStick = GamepadStickType(i);
        InputVector stickValue = {.Horizontal = 0.0f, .Vertical = 0.0f};
        const std::vector<GamepadAxisType>& axisAnalyses = StickAxis.at(UpdateStick);
        int axisIndex = 0;
        for (auto& axisEnum : axisAnalyses)
        {
            float axis = GetAxis(axisEnum);
            assert (axisIndex <= 1 && "Support only two axis");
            axisIndex++ == 0 ? stickValue.Horizontal = axis : stickValue.Vertical = axis;
        }
        StickValue[i] = stickValue;
    }
}

Sparkle::GamepadController::GamepadController(SDL_GameController *controller):
        InternalGameController(controller), ButtonsValue(), LastButtonsValue(),
        OnDisconnectedEvent(ON_DISCONNECTED_EVENT_NAME),
        OnConnectedEvent(ON_CONNECTED_EVENT_NAME)
{
    std::fill(ButtonsValue.begin(), ButtonsValue.end(), false);
    std::fill(LastButtonsValue.begin(), LastButtonsValue.end(), false);

    std::fill(AxisValue.begin(), AxisValue.end(), false);
    std::fill(LastAxisValue.begin(), LastAxisValue.end(), false);

    InputVector emptyStick{};
    std::fill(StickValue.begin(), StickValue.end(), emptyStick);
    std::fill(LastStickValue.begin(), LastStickValue.end(), emptyStick);
}

Sparkle::GamepadController::GamepadController():
        InternalGameController(nullptr), ButtonsValue(), LastButtonsValue(),
        OnDisconnectedEvent(ON_DISCONNECTED_EVENT_NAME),
        OnConnectedEvent(ON_CONNECTED_EVENT_NAME)
{
    std::fill(ButtonsValue.begin(), ButtonsValue.end(), false);
    std::fill(LastButtonsValue.begin(), LastButtonsValue.end(), false);

    std::fill(AxisValue.begin(), AxisValue.end(), false);
    std::fill(LastAxisValue.begin(), LastAxisValue.end(), false);

    InputVector emptyStick{};
    std::fill(StickValue.begin(), StickValue.end(), emptyStick);
    std::fill(LastStickValue.begin(), LastStickValue.end(), emptyStick);
}

Sparkle::InputResult Sparkle::GamepadController::ProcessEvent(const Sparkle::InputTrigger &event)
{
    switch (event.EventType)
    {
        case InputEventType::GamepadButtonEventType:
            return ProcessButton(event.Event.GamepadButtonEvent);

        case InputEventType::GamepadAxisEventType:
            return ProcessAxis(event.Event.GamepadAxisEvent);

        case InputEventType::GamepadStickEventType:
            return ProcessStick(event.Event.GamepadStickEvent);

        default:
            return Sparkle::InputResult{false};
    }
}

Sparkle::InputResult Sparkle::GamepadController::ProcessStick(const InputGamepadStickEvent &event)
{
    bool hasStickMoved = HasStickMoved(event.Stick);
    InputVector stickValue = GetStick(event.Stick);
    if (event.StickTrigger == InputAnalogEventTrigger::CONTINUOUS
        || hasStickMoved && event.StickTrigger == InputAnalogEventTrigger::MOVEMENT
        || (stickValue.Horizontal >= 0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_POSITIVE || stickValue.Vertical >= 0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_POSITIVE)
        || (stickValue.Vertical <= -0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_NEGATIVE) || (stickValue.Horizontal <= -0.95 && event.StickTrigger == InputAnalogEventTrigger::FULL_NEGATIVE))
    {
        Stick stick = {.StickType = {.GamepadStick = event.Stick}, .Value = stickValue};
        return InputResult{true, InputState{.Type=InputType::STICK, .Input={.Stick = stick}}};
    }
    return InputResult{false};
}

Sparkle::InputResult Sparkle::GamepadController::ProcessButton(const InputGamepadButtonEvent &event)
{
    bool isButtonJustPressed = IsButtonJustPressed(event.Button);
    bool isButtonJustReleased = IsButtonJustReleased(event.Button);
    if (isButtonJustPressed && event.ButtonTrigger == InputDigitalEventTrigger::JUST_PRESSED
        || isButtonJustReleased && event.ButtonTrigger == InputDigitalEventTrigger::JUST_RELEASED
        || IsButtonPressed(event.Button) && event.ButtonTrigger == InputDigitalEventTrigger::HOLDING_DOWN
        || !IsButtonPressed(event.Button) && event.ButtonTrigger == InputDigitalEventTrigger::UP)
    {
        Button button = {.ButtonType = {.GamepadButton = event.Button}, .Pressed = IsButtonPressed(event.Button)};
        return InputResult{true, InputState{.Type=InputType::BUTTON, .Input={.Button = button}}};
    }
    return InputResult{false};
}

Sparkle::InputResult Sparkle::GamepadController::ProcessAxis(const InputGamepadAxisEvent &event)
{
    bool hasAxisMoved = HasAxisMoved(event.Axis);
    float axisValue = GetAxis(event.Axis);
    if (event.AxisTrigger == InputAnalogEventTrigger::CONTINUOUS
        || hasAxisMoved && event.AxisTrigger == InputAnalogEventTrigger::MOVEMENT
        || axisValue >= 0.95 && event.AxisTrigger == InputAnalogEventTrigger::FULL_POSITIVE
        || axisValue <= -0.95 && event.AxisTrigger == InputAnalogEventTrigger::FULL_NEGATIVE)
    {
        Axis axis = {.AxisType = {.GamepadAxis = event.Axis}, .Value = axisValue};
        return InputResult{true, InputState{.Type=InputType::AXIS, .Input={.Axis = axis}}};
    }
    return InputResult{false};
}
