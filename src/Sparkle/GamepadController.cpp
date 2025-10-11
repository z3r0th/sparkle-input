//
// Created by z3r0_ on 15/01/2024.
//

#include "GamepadController.h"
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
    // TODO: Review dead_zone implementation
    // apply a dead_zone of 2% movement for now. This should be configurable somehow
    const float DEAD_ZONE = (float)(SDL_MAX_SINT16 - SDL_MIN_SINT16) * (2.0 / 100.0f) / SDL_MAX_SINT16;
    
    if (!IsActive())
    {
        return;
    }

    for (unsigned int i = 0 ; i < static_cast<int>(GamepadButton::Count) ; ++i)
    {
        LastButtons[i] = Buttons[i];
        Buttons[i] = SDL_GameControllerGetButton(InternalGameController, static_cast<SDL_GameControllerButton>(i));
    }

    for (unsigned int i = 0 ; i < static_cast<int>(GamepadAxis::Count) ; ++i)
    {
        LastAxis[i] = Axis[i];
        float axis = (float)(SDL_GameControllerGetAxis(InternalGameController, static_cast<SDL_GameControllerAxis>(i))) / (float)(SDL_MAX_SINT16);
        if (abs(axis) <= DEAD_ZONE)
        {
            axis = 0.0;
        }
        Axis[i] = axis;
    }
}
