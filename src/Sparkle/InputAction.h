//
// Created by z3r0_ on 10/01/2024.
//

#ifndef SPARKLE_SOLUTION_INPUT_ACTION_H
#define SPARKLE_SOLUTION_INPUT_ACTION_H

#include <functional>
#include <string>
#include <utility>

#define EMPTY_ACTION_NAME "EMPTY"

namespace Sparkle
{
    /// Represents Player Input Action
    /// This could be actions like Jump, Run, Fire, OpenMenu, ActivateUI, etc
    /// This is a Name string based class. Meaning two different instances but with the same name are considered the same
    class InputAction
    {
    protected:
        std::string ActionDescription;
        std::string ActionName;

    public:
        explicit InputAction(std::string  actionName, std::string  actionDescription = "")
        : ActionName(std::move(actionName)), ActionDescription(std::move(actionDescription))
        { }

        InputAction(const InputAction& action)
        {
            ActionName = action.ActionName;
            ActionDescription = action.ActionDescription;
        }

        InputAction() : ActionName(EMPTY_ACTION_NAME), ActionDescription()
        { }

        /// Action Name
        /// \return name
        [[nodiscard]] inline const std::string& GetName() const
        {
            return ActionName;
        }

        /// Action Description
        /// \return description
        [[maybe_unused]][[nodiscard]] inline const std::string& GetDescription() const
        {
            return ActionDescription;
        }

        // comparison operators used on map
        bool operator <(const InputAction& rhs) const
        {
            return ActionName < rhs.ActionName;
        }

        // equivalence operator for consistence
        bool operator ==(const InputAction& rhs) const
        {
            return ActionName == rhs.ActionName;
        }
    };
}

// To compute HASH for InputAction, so it can be used in unordered_map (if needed)
// use the Action name as HASH
template <>
struct std::hash<Sparkle::InputAction>
{
    std::size_t operator()(const Sparkle::InputAction& k) const
    {
        using std::size_t;
        using std::hash;
        using std::string;
        return hash<string>()(k.GetName());
    }
};

#endif //SPARKLE_SOLUTION_INPUT_ACTION_H
