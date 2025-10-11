//
// Created by z3r0_ on 07/09/2025.
//

#ifndef SPARKLE_SOLUTION_INPUTPROCESS_H
#define SPARKLE_SOLUTION_INPUTPROCESS_H

#include "Sparkle/InputAction.h"
#include "Sparkle/InputMap.h"
#include <Sparkle/Event.h>
#include <memory>
#include "Sparkle/GamepadController.h"

namespace Sparkle
{
    class PlayerInputController;
    template<class T>
    class InputProcess
    {
    public:
        virtual bool UpdateInput(const T &inputEvent, const InputAction &action) = 0;
    };

}

#endif //SPARKLE_SOLUTION_INPUTPROCESS_H
