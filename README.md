# About

Sparkle Input is an input module built on top of SDL2 that converts raw keyboard and 
controller events into meaningful in-game actions. Instead of wiring gameplay to 
device-specific codes, you define actions like `Jump`, `Pause`, or `Reload`, etc. and map them to the physical input. 
This keeps game logic clean, reduces duplication, and makes it easy to support new devices or 
adjust controls mid-development and realtime. With per-player support and an event-driven design, 
Sparkle Input helps keep input handling organized, portable, and straightforward.

# Sparkle

[Sparkle Project](https://gitlab.com/sparkle-game-engine/) is a small personal project to learn to design and build a UI engine.
The project is currently private.

# Features
- Abstraction — input handled through clean device abstractions (Gamepad, Keyboard, Mouse).
- Action mapping — map logical actions to physical inputs through triggers.
- Event-driven — respond to input with event callbacks, no manual polling required.
- Player-centric controllers — per-player input routing, ready for local multiplayer.
- SDL2 backend — cross-platform input foundation.

# Concepts

| Term | Meaning |
|---|---|
| **Controller** | The physical input device used to control the game (gamepad, keyboard, mouse). |
| **Gamepad** | A game input controller, such as an Xbox or PlayStation controller. |
| **Keyboard** | The computer keyboard. |
| **Mouse** | The computer mouse. |
| **Map** | How a *Controller* input and an *Action* are bound together, through a *Trigger*. |
| **Trigger** | How a physical input fires — a button press/release/hold, or a moving axis. |
| **Action** | The logical action the game reacts to (jump, pause, reload), independent of device. |
| **Axis** | A one-dimensional floating-point input, e.g. a gamepad trigger or one axis of a stick. |
| **Stick** | A two-dimensional floating-point input — the Horizontal + Vertical axes of a stick. |
| **Digital Trigger** | A trigger that fires on press/release — used with buttons. |
| **Analog Trigger** | A trigger that fires based on a floating value — used with axes/sticks. |

# Overview

How to use Sparkle Input:

1. Initialize SDL2 in your app (video/events subsystem)
2. Run the input loop. Call `UpdateEvent` when Polling SDL events and `Update` once per frame.
3. Create a PlayerInputController for each player and assign devices to it.
4. Define Game Actions.
5. Create an InputMap and bind Actions to Device Input through Triggers.
6. Bind callbacks to actions on the PlayerInputController.

# Installation

## Requirements

- CMake 3.30 or newer
- A C++20-capable compiler
- SDL2 (fetched automatically if not already installed — see below)

## FetchContent
``` cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.30)

project(MyApp LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  SparkleInput
  GIT_REPOSITORY https://gitlab.com/sparkle-game-engine/sparkle-input.git
  GIT_TAG main
)
set(SPARKLE_INPUT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPARKLE_INPUT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SparkleInput)

add_executable(MyApp src/main.cpp)
target_link_libraries(MyApp PRIVATE Sparkle::SparkleInput)
```

SDL2 and Sparkle Events are fetched automatically as part of the build
(FetchContent, falling back to find_package if either is already installed on the system)
— no manual setup required.

### Building the examples/tests standalone

```bash
git clone https://gitlab.com/sparkle-game-engine/sparkle-input.git
cd sparkle-input
cmake -B build -DSPARKLE_INPUT_BUILD_EXAMPLES=ON
cmake --build build
```

# Examples

## SDL Initialization

This is a simple SDL2 initialization function that initializes SDL2 and creates a window and renderer and 
then runs the input loop. We use it throughout the examples to make it easier to test the input system.

```cpp
#ifndef SPARKLEINPUT_SDLINITIALIZATION_H
#define SPARKLEINPUT_SDLINITIALIZATION_H

#include <iostream>
#include <SDL.h>

#include "Sparkle/Input.h"

int InitializeSDLAndRunInput(Sparkle::Input& input, std::function<void(Sparkle::Input&)> func = nullptr)
{
    Sparkle::Input Input = std::move(input);
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow(
            "SDL2 Window Example",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            SDL_WINDOW_SHOWN
    );

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
        return 1;
    }

    if (!window) 
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) 
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    bool quit = false;
    SDL_Event e;
    
    while (!quit) {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) 
            {
                quit = true;
            }
            Input.UpdateEvent(e);
        }
        Input.Update();
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        if (func) func(Input);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

#endif

```

## Example 1: Basic usage

`TutorialExample01`

```cpp
// TutorialExample01.cpp
#include "SDLInitialization.h"
#include "Sparkle/Input.h"

void PrintAction(const std::weak_ptr<Sparkle::PlayerInputController>&, const Sparkle::InputAction& action, Sparkle::InputState buttonState)
{
    SDL_Log(">> Action[%s] - BUTTON PRESSED: [%s]", action.GetName().c_str(), buttonState.GetButton() ? "PRESSED" : "RELEASED");
}

int main(int argc, char* argv[])
{
    Sparkle::InputMap map;
    Sparkle::InputAction Action("GAME ACTION");
    map.Bind(Sparkle::GamepadButtonType::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, Action);
    map.Bind(Sparkle::GamepadButtonType::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, Action);
    map.Bind(Sparkle::KeyboardButtonType::KEY_SPACE, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, Action);
    map.Bind(Sparkle::KeyboardButtonType::KEY_SPACE, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, Action);

    Sparkle::Input input;
    auto playerInputController = input.GetNewPlayerInputController().lock();
    playerInputController->AssignKeyboard();
    playerInputController->AssignGamepad();
    playerInputController->SetInputMap(map);
    playerInputController->OnAction(Action).Bind(&PrintAction);

    return InitializeSDLAndRunInput(input);
}
}
```

# Roadmap

- KEYBOARD Text input support
- GAMEPAD Text input support
- Save/Load key mapping
- More device support (Wheel, VR, Touch, etc.)
- Runtime device/PlayerInputController reassignment
- Rumble/Vibration support
- Battery level support/notification
- Configurable dead zone
- SDL3 migration
- Tests

# Changelog

```terminaloutput
v0.9.0 Initial Release
```

# License

MIT License. Free to use in commercial and non-commercial projects

