//
// Created by z3r0_ on 12/10/2025.
//

#ifndef SPARKLEINPUT_SDLINITIALIZATION_H
#define SPARKLEINPUT_SDLINITIALIZATION_H

#include <iostream>
#include <SDL.h>

#include "Sparkle/Input.h"

int InitializeSDLAndRunInput(Sparkle::Input& input, std::function<void(Sparkle::Input&)> func = nullptr)
{
    Sparkle::Input Input = std::move(input);
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

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
        return 1;
    }

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
        while (SDL_PollEvent(&e))
        {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            Input.UpdateEvent(e);
        }
        Input.Update();

        // Set draw color to blue
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        // Clear the screen with the set color
        SDL_RenderClear(renderer);

        // Update the screen
        SDL_RenderPresent(renderer);

        if (func) func(Input);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

#endif //SPARKLEINPUT_SDLINITIALIZATION_H
