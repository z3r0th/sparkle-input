
#include "SDLInitialization.h"
#include "Sparkle/Input.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"

int main(int argc, char* argv[])
{
    Sparkle::Input input;
    return InitializeSDLAndRunInput(input, [](Sparkle::Input& Input)
    {
        if (auto Keyboard = Input.GetKeyBoardController().lock())
        {
            if (!Keyboard->IsActive()) { std::cout << "Keyboard is not active" << std::endl; }
            if (Keyboard->IsButtonJustPressed(Sparkle::KeyboardButton::KEY_A)) { std::cout << "Key \'A\' just pressed" << std::endl; }
            if (Keyboard->IsButtonJustReleased(Sparkle::KeyboardButton::KEY_A)) { std::cout << "Key \'A\' just released" << std::endl; }
        }
    });
}
#pragma clang diagnostic pop