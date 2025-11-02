1. Generated README (TO EDIT)
2. SparkleInput is a lightweight, C++20 input abstraction layer built on SDL2 that turns raw device signals into clean, semantic gameplay actions. It unifies keyboard and gamepad handling under a single API, so you design around “Jump” or “Interact” instead of scancodes and button IDs, making gameplay code simpler, safer, and more portable. The library is event-driven (via Sparkle Events), enabling decoupled systems: input maps emit actions, and game logic subscribes to them without tight coupling to device specifics. Designed for game development, it supports per-player controllers and action mapping, letting you bind multiple physical inputs to the same in-game action or rebind at runtime. With a CMake-first setup, you can integrate through FetchContent, install+find_package, or add_subdirectory, and it will fetch SDL2 and Sparkle Events when needed. This approach reduces boilerplate SDL event handling, centralizes input logic, and improves testability and maintainability. Advantages include cross-platform consistency, easier prototyping (change bindings without touching gameplay code), clearer separation of concerns, and straightforward scaling from keyboard-only prototypes to multi-controller setups. The included examples demonstrate SDL initialization, action mapping, and per-frame processing, helping you get from input to gameplay response fast.

2. About SparkleInput is a lightweight, SDL2-powered C++ input library that unifies keyboard and gamepad input into a clean, event-driven model. It integrates with the Sparkle Events system to let you map raw inputs to semantic actions and listen to them in a decoupled way. The library is suitable for games and interactive applications that want a simple, extensible input layer.
2. Features

- Unified input: keyboard and gamepad handled through common abstractions
- Action mapping: map multiple physical inputs to a single logical action
- Event-driven: publish/subscribe via Sparkle Events
- Player-centric controllers: per-player input routing
- SDL2 backend: proven cross-platform input foundation
- CMake-friendly: FetchContent, install + find_package, or add_subdirectory
- Examples included: small demo programs to get started quickly

1. Installation Requirements:

- CMake 4.0 or newer
- A C++20-capable compiler
- SDL2 (fetched automatically if not preinstalled)
- Sparkle Events (fetched automatically)

Option A — FetchContent (recommended for projects without system packages):
``` cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
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

add_executable(my_app src/main.cpp)
target_link_libraries(my_app PRIVATE Sparkle::SparkleInput)
```
Option B — System-wide install + find_package:
1. In the SparkleInput source tree:
``` bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target install
```
1. In your project:
``` cmake
find_package(SparkleInput REQUIRED)
add_executable(my_app src/main.cpp)
target_link_libraries(my_app PRIVATE Sparkle::SparkleInput)
```
Option C — add_subdirectory (vendor as submodule):
``` cmake
add_subdirectory(external/SparkleInput)
add_executable(my_app src/main.cpp)
target_link_libraries(my_app PRIVATE Sparkle::SparkleInput)
```
Build options:
- SPARKLE_INPUT_BUILD_TESTS: ON/OFF (default ON, currently no tests added)
- SPARKLE_INPUT_BUILD_EXAMPLES: ON/OFF (default ON)

1. Usage High-level flow:

- Initialize SDL2 in your app (video/events subsystem)
- Create input controllers (keyboard, gamepad) and a PlayerInputController
- Define InputAction names and an InputMap to bind physical inputs (keys/buttons/axes) to actions
- Pump SDL events each frame and pass them to SparkleInput
- Subscribe to action events via the event system or poll action states

Minimal example outline:
``` cpp
// C++
#include <Sparkle/Input.h>
#include <Sparkle/InputMap.h>
#include <Sparkle/InputAction.h>
#include <Sparkle/PlayerInputController.h>
#include <Sparkle/Controller/KeyboardController.h>
#include <Sparkle/Controller/GamepadController.h>

// Pseudocode outline:
// 1) Initialize SDL2
// 2) Create InputMap, add actions (e.g., "MoveLeft", "Jump")
// 3) Bind keys/buttons to actions
// 4) Create controllers, attach to PlayerInputController
// 5) In your loop, poll SDL events and feed them to SparkleInput
// 6) Listen for action events or query action states
int main() {
    // SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

    // Define actions and bindings
    // InputMap map;
    // map.bindKey("Jump", SDL_SCANCODE_SPACE);
    // map.bindGamepadButton("Jump", SDL_CONTROLLER_BUTTON_A);

    // Setup controllers
    // KeyboardController keyboard;
    // GamepadController gamepad(0); // first gamepad
    // PlayerInputController player(map);
    // player.attach(&keyboard);
    // player.attach(&gamepad);

    // Main loop
    // SDL_Event e;
    // while (running) {
    //   while (SDL_PollEvent(&e)) {
    //     player.processEvent(e);
    //   }
    //   if (player.isTriggered("Jump")) {
    //     // jump logic
    //   }
    // }
    // SDL_Quit();
    return 0;
}
```
Note: Names are indicative of the public headers; consult the examples for concrete, buildable code.
1. Examples Build examples (enabled by default):
``` bash
cmake -S . -B build -DSPARKLE_INPUT_BUILD_EXAMPLES=ON
cmake --build build --config Release
```
Run them from:
- build/bin/examples on most platforms

The examples demonstrate:
- SDL2 initialization for input
- Keyboard and gamepad bindings
- Basic action mapping and event handling

1. Changelog

- 0.9.0
    - Initial public release of SparkleInput
    - SDL2 backend integration
    - Event-driven input via Sparkle Events
    - Keyboard and gamepad controllers
    - CMake package config and examples

1. Roadmap

- 0.9.x
    - API polish, documentation and examples expansion
    - Gamepad hotplugging and device remapping improvements

- 1.0.0
    - Stable API
    - Extended action/axis configuration and serialization
    - Comprehensive tests
    - Platform nuances coverage (Linux, Windows, macOS)

- Post-1.0
    - Rumble/haptics abstraction
    - Input recording/replay
    - Mouse and touch input modules

1. License (MIT) Copyright (c) Sparkle Game Engine contributors

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
Additional Sections
- Supported Platforms
    - Cross-platform via SDL2 (Windows, macOS, Linux). Other platforms may work if SDL2 supports them.

- Contributing
    - Issues and merge requests are welcome. Please:
        - Keep PRs focused and documented
        - Add/adjust examples where relevant
        - Follow existing code style and CMake patterns

- FAQ
    - Does this require a system SDL2 install?
        - Not necessarily. The build will fetch SDL2 automatically if a suitable package isn’t found.

    - Can I integrate without installing?
        - Yes. Use FetchContent or add_subdirectory.

- Troubleshooting
    - Link errors with SDL2main:
        - Some platforms don’t provide SDL2::SDL2main. The build only links it when available. If your app requires it (e.g., certain Windows GUI subsystems), link order matters: link SDL2main before SDL2.

    - Multiple SDL instances:
        - Initialize and quit SDL2 in your application; avoid initializing SDL in both your app and external libs.

    - Headers not found:
        - If using find_package, ensure CMAKE_PREFIX_PATH or default install locations include SparkleInput’s install prefix.


TODO:
- Configure Gamepad dead zone value (GamepadController::Update)