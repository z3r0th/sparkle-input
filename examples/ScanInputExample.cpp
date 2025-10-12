#include "SDLInitialization.h"
#include "Sparkle/Input.h"

void Update(Sparkle::Input& input)
{
    if (auto keyboard = input.GetKeyBoardController().lock())
    {
        if (keyboard->IsButtonPressed(Sparkle::KeyboardButton::KEY_SPACE))
        {
            SDL_Log(">> SPACE PRESSED");
        }
    }
}

int main(int argc, char* argv[])
{
    Sparkle::Input input;
    return InitializeSDLAndRunInput(input, Update);
}