//
// Created by z3r0_ on 15/01/2024.
//

#include "Sparkle/Controller/InputProcess/GamepadInputProcess.h"
#include "Sparkle/Controller/GamepadController.h"
#include <SDL.h>

void Sparkle::GamepadController::ClearController()
{
    InternalGameController = nullptr;

    std::weak_ptr<GamepadController> weak_this = weak_from_this();
    OnDisconnectedEvent.Raise(weak_this);

    std::fill(Buttons.begin(), Buttons.end(), false);
    std::fill(LastButtons.begin(), LastButtons.end(), false);

    std::fill(Axis.begin(), Axis.end(), false);
    std::fill(LastAxis.begin(), LastAxis.end(), false);

    struct InputVector emptyStick{};
    std::fill(Stick.begin(), Stick.end(), emptyStick);
    std::fill(LastStick.begin(), LastStick.end(), emptyStick);
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
    const float DEAD_ZONE_PERCENTAGE = 2.0f / 100.0f;
    const float DEAD_ZONE = (float)(SDL_MAX_SINT16 - SDL_MIN_SINT16) * DEAD_ZONE_PERCENTAGE / SDL_MAX_SINT16;
    
    if (!IsActive())
    {
        return;
    }

    for (unsigned int i = 0 ; i < static_cast<int>(GamepadButtonType::Count) ; ++i)
    {
        LastButtons[i] = Buttons[i];
        Buttons[i] = SDL_GameControllerGetButton(InternalGameController, static_cast<SDL_GameControllerButton>(i));
    }

    for (unsigned int i = 0 ; i < static_cast<int>(GamepadAxisType::Count) ; ++i)
    {
        LastAxis[i] = Axis[i];
        float axis = (float)(SDL_GameControllerGetAxis(InternalGameController, static_cast<SDL_GameControllerAxis>(i))) / (float)(SDL_MAX_SINT16);
        if (abs(axis) <= DEAD_ZONE)
        {
            axis = 0.0;
        }
        Axis[i] = axis;
    }

    for (unsigned int i = 0 ; i < static_cast<int>(GamepadStickType::Count) ; ++i)
    {
        static const std::map<GamepadStickType, const std::vector<GamepadAxisType>> StickAxis =
        {
            {GamepadStickType::STICK_LEFT,  {GamepadAxisType::AXIS_LEFT_X,  GamepadAxisType::AXIS_LEFT_Y}},
            {GamepadStickType::STICK_RIGHT, {GamepadAxisType::AXIS_RIGHT_X, GamepadAxisType::AXIS_RIGHT_Y}}
        };
        LastStick[i] = Stick[i];
        GamepadStickType UpdateStick = static_cast<GamepadStickType::GamepadStickEnum>(i);
        struct InputVector stickValue = {.Horizontal = 0.0f, .Vertical = 0.0f};
        const std::vector<GamepadAxisType>& axisAnalyses = StickAxis.at(UpdateStick);
        int axisIndex = 0;
        for (auto& axisEnum : axisAnalyses)
        {
            float axis = GetAxis(axisEnum);
            assert (axisIndex <= 1 && "Support only two axis");
            axisIndex++ == 0 ? stickValue.Horizontal = axis : stickValue.Vertical = axis;
        }
        Stick[i] = stickValue;
    }
}

Sparkle::GamepadController::GamepadController(SDL_GameController *controller):
        InputProcess(std::make_unique<GamepadInputProcess>(this)),
        InternalGameController(controller), Buttons(), LastButtons(),
        OnDisconnectedEvent(ON_DISCONNECTED_EVENT_NAME),
        OnConnectedEvent(ON_CONNECTED_EVENT_NAME)
{
    std::fill(Buttons.begin(), Buttons.end(), false);
    std::fill(LastButtons.begin(), LastButtons.end(), false);

    std::fill(Axis.begin(), Axis.end(), false);
    std::fill(LastAxis.begin(), LastAxis.end(), false);

    struct InputVector emptyStick{};
    std::fill(Stick.begin(), Stick.end(), emptyStick);
    std::fill(LastStick.begin(), LastStick.end(), emptyStick);
}

Sparkle::GamepadController::GamepadController():
        InputProcess(std::make_unique<GamepadInputProcess>(this)),
        InternalGameController(nullptr), Buttons(), LastButtons(),
        OnDisconnectedEvent(ON_DISCONNECTED_EVENT_NAME),
        OnConnectedEvent(ON_CONNECTED_EVENT_NAME)
{
    std::fill(Buttons.begin(), Buttons.end(), false);
    std::fill(LastButtons.begin(), LastButtons.end(), false);

    std::fill(Axis.begin(), Axis.end(), false);
    std::fill(LastAxis.begin(), LastAxis.end(), false);

    struct InputVector emptyStick{};
    std::fill(Stick.begin(), Stick.end(), emptyStick);
    std::fill(LastStick.begin(), LastStick.end(), emptyStick);
}

Sparkle::InputResult Sparkle::GamepadController::ProcessEvent(const Sparkle::InputTrigger &event)
{
    return InputProcess->ProcessEvent(event);
}

Sparkle::GamepadController::~GamepadController() = default;
