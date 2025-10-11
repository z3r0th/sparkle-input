//
// Created by z3r0_ on 08/09/2025.
//

#include "Sparkle/PlayerInputController.h"
#include "GamepadInputProcess.h"
#include "Sparkle/GamepadController.h"

namespace Sparkle {
    std::weak_ptr<GamepadController> Sparkle::GamepadInputProcessHandler::GetGamepadController()
    {
        if (auto PlayerInputControllerLocked = PlayerInputController.lock())
        {
            return PlayerInputControllerLocked->GetGamepadController();
        }

        return {};
    }

    unsigned int Sparkle::GamepadInputProcessHandler::GetPlayerInputIndex()
    {
        if (auto PlayerInputControllerLocked = PlayerInputController.lock())
        {
            return PlayerInputControllerLocked->GetPlayerInputIndex();
        }
        assert(false);
        return -1;
    }
}