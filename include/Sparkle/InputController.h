//
// Created by z3r0_ on 10/10/2025.
//

#ifndef SPARKLE_SOLUTION_INPUTCONTROLLER_H
#define SPARKLE_SOLUTION_INPUTCONTROLLER_H

namespace Sparkle
{
    class InputTrigger;
    class InputAction;

    class InputController
    {
    protected:
        /// If active, it should update buttons and lastButtons, axis and lastAxis with the device status
        virtual void Update() = 0;

    public:
        /// Is this controller active to the player?
        /// \return true if active
        [[nodiscard]] virtual inline bool IsActive() = 0;
    };

} // Sparkle

#endif //SPARKLE_SOLUTION_INPUTCONTROLLER_H
