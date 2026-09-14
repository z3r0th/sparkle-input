#include "SDLInitialization.h"
#include "Sparkle/Input.h"

float lastMouseX = 0.0f;
void Update(Sparkle::Input& input)
{
    if (input.IsKeyboardButtonPressed(Sparkle::KeyboardButtonType::KEY_A))
    {
        SDL_Log(">> KEYBOARD A PRESSED");
    }
    if (auto keyboard = input.GetKeyBoardController().lock())
    {
        if (keyboard->IsButtonPressed(Sparkle::KeyboardButtonType::KEY_SPACE))
        {
            SDL_Log(">> SPACE PRESSED");
        }
        if (auto button = keyboard->AnyJustPressedButton();button != Sparkle::KeyboardButtonType::KEY_NONE)
        {
            SDL_Log(">> ANY KEY PRESSED: %s", button.c_str());
        }
    }
    if (auto mouse = input.GetMouseController().lock())
    {
        if (mouse->IsButtonPressed(Sparkle::MouseButtonType::BUTTON_LEFT))
        {
            SDL_Log(">> LEFT MOUSE BUTTON PRESSED");
        }
        if (auto button = mouse->AnyJustPressedButton();button != Sparkle::MouseButtonType::BUTTON_NONE)
        {
            SDL_Log(">> ANY MOUSE BUTTON PRESSED: %s", button.c_str());
        }
        float mouseX = mouse->GetAxis(Sparkle::MouseAxisType::AXIS_X);
        if (std::abs(lastMouseX - mouseX) > 0.01f)
        {
            SDL_Log(">> MOUSE X AXIS: %f", mouseX);
        }
        lastMouseX = mouseX;
    }
    if (auto gamepad = input.GetGamepadController(0).lock())
    {
        if (gamepad->IsButtonPressed(Sparkle::GamepadButtonType::BUTTON_A))
        {
            SDL_Log(">> A BUTTON PRESSED");
        }
        if (gamepad->GetAxis(Sparkle::GamepadAxisType::TRIGGER_RIGHT) > 0.5f)
        {
            SDL_Log(">> RIGHT TRIGGER PRESSED");
        }
    }
}

int main(int argc, char* argv[])
{
    Sparkle::Input input;
    return InitializeSDLAndRunInput(input, Update);
}