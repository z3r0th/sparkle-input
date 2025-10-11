#include <iostream>
#include "Sparkle/Input.h"
#include "Sparkle/GamepadController.h"
#include "Sparkle/PlayerInputController.h"

int main(int argc, char* argv[])
{
    Sparkle::Input input;
    auto playerInputController = input.GetNewPlayerInputController().lock();
    if (!playerInputController) return -1;
    Sparkle::InputMap map;
    Sparkle::InputAction pressedButtonA("PressedButtonA");
    map.Bind(Sparkle::KeyboardButton::KEY_A, Sparkle::InputButtonEventTrigger::JUST_PRESSED, pressedButtonA);
    playerInputController->OnKeyboardButton(pressedButtonA).Bind([](const unsigned int&, const Sparkle::InputAction&, const Sparkle::InputKeyboardButtonEvent&){
        SDL_Log(">> KEY A PRESSED");
    });
    playerInputController->SetInputMap(map);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
            "SDL2 Window Example",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            SDL_WINDOW_SHOWN // Flag to make the window visible
    );

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a renderer for the window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    // Game loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Set draw color to blue
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        // Clear the screen with the set color
        SDL_RenderClear(renderer);

        // Update the screen
        SDL_RenderPresent(renderer);

        input.UpdateEvent(e);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}
