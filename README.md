# About

Sparkle Input is an input module built on top of SDL2 that converts raw keyboard and 
controller events into meaningful in-game actions. Instead of wiring gameplay to 
device-specific codes, you define actions like Jump, Pause, or Reload, etc. and map them to the input. 
This keeps game logic clean, reduces duplication, and makes it easy to support new devices or 
adjust controls mid-development and realtime. With per-player support and an event-driven design, 
Sparkle Input helps keep input handling organized, portable, and straightforward.

# Sparkle

[Sparkle Project](https://gitlab.com/sparkle-game-engine/) is a small personal project to learn to design and build a UI engine.
The project is currently private.

# Summary

### Controller
Controller is the physical input device used to control the game (gamepad, keyboard, mouse, etc.)
### Gamepad
Gamepad is a game input controller (like xbox or playstation controller) 
### Keyboard
Keyboard is the computer keyboard
### Mouse
Mouse is the computer mouse
### Map
Map is how we bind a *Controller* and *Action* to a *Trigger*
### Trigger
Trigger is how we trigger a physical input. Like a button pressed, released, holding, etc.
### Action
Action is the logical action that the game can take (jump, pause, reload, etc.). We bind the action to 
a physical input through a *Trigger*
### Axis
Axis is a one-dimensional floating input. Like Horizontal *Axis* for a Gamepad *Stick* or Gamepad *Trigger*.
### Stick
Stick is a two-dimensional floating input. Like Horizontal and Vertical Axis for a Gamepad *Stick*.
### Digital Trigger
Digital Trigger is a trigger that can be pressed or released. Like a Button.
### Analog Trigger
Analog Trigger is a trigger that represents a floating value. Like an Axis.

# Features

- Abstraction: Input handled through abstractions.
- Action mapping: Map actions to physical inputs through triggers.
- Event-driven: Respond to input events with event callbacks.
- Player-centric controllers: per-player input routing.
- SDL2 backend: cross-platform input foundation.

# Installation

## Requirements

- CMake 4.0 or newer
- A C++20-capable compiler

## FetchContent
``` cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 4.0)

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

# Overview

How to use Sparkle Input:

- Initialize SDL2 in your app (video/events subsystem)
- Run the input loop. Call `UpdateEvent` when Polling SDL events and `Update` once per frame.
- Create a PlayerInputController for each player and assign devices to it.
- Define Game Actions.
- Create an InputMap (probably one for each player).
- Use the map to bind Actions to Device Input through Triggers.
- Use PlayerInputController to bind Actions to a Method.

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
    SDL_Log(">> Action[%s] - BUTTON PRESSED: [%s]", action.GetName().c_str(), buttonState.Value.ButtonPressed ? "PRESSED" : "RELEASED");
}

int main(int argc, char* argv[])
{
    Sparkle::InputMap map;
    Sparkle::InputAction Action("GAME ACTION");
    map.Bind(Sparkle::GamepadButton::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, Action);
    map.Bind(Sparkle::GamepadButton::BUTTON_A, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, Action);
    map.Bind(Sparkle::KeyboardButton::KEY_SPACE, Sparkle::InputDigitalEventTrigger::JUST_PRESSED, Action);
    map.Bind(Sparkle::KeyboardButton::KEY_SPACE, Sparkle::InputDigitalEventTrigger::JUST_RELEASED, Action);

    Sparkle::Input input;
    auto playerInputController = input.GetNewPlayerInputController().lock();
    playerInputController->AssignKeyboard();
    playerInputController->AssignGamepad();
    playerInputController->SetInputMap(map);
    playerInputController->OnAction(Action).Bind(&PrintAction);

    return InitializeSDLAndRunInput(input);
}
```

# Roadmap

- Mouse support
- Keyboard Text input support
- Gamepad Text input support
- Save/Load key mapping
- More devices Support (Wheel, VR, Touch, etc.)
- Device/PlayerInputController Reassignment
- Rumble/Vibration support
- Battery level support/notification
- Tests
- Documentation
- Examples
- Device metadata support

# Changelog

```terminaloutput
v0.9.0 Initial Release
```

# License

MIT License. Free to use in commercial and non-commercial projects

