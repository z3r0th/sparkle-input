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


----

## Me
Analyze and criticize the codebase, considering it is a framework for game development focused on input handling (currently gamepad and keyboard), make a small commercial and marketing assertment of what the project is about. Also, make suggestions for future improvements and fixes. Also make an analysis of current project maturity for using on indie and professional game development.  Finally, as an experienced game developer and C++ engineer, summarize your first impressions of this project

## AI Assistant
## Executive summary (commercial/marketing)
SparkleInput is a focused, C++20 input framework for games that turns raw SDL2 keyboard and gamepad signals into clean, semantic actions like “Jump,” “Pause,” or “Aim.” Its action-mapping and event-driven design let you write gameplay once and bind any device to it—speeding up prototyping, reducing boilerplate, and keeping systems decoupled. For indie teams and tool-minded pros, SparkleInput offers a pragmatic sweet spot: simple to drop in, portable across platforms, and structured around per-player controllers so local multiplayer and input swapping are straightforward. If you want consistent input behavior without wrestling scancodes, buttons, and device churn, SparkleInput gives you the clean abstraction and extensibility you need.
## Strengths
- Clear action abstraction
    - Logical actions decoupled from physical inputs for keyboard and gamepad.
    - Digital and analog triggers supported (button, axis, stick).

- Per-player input orchestration
    - PlayerInputController coordinates devices and action dispatch per user.

- Event-driven integration
    - Sparkle Events enables subscribe/raise patterns for low coupling.

- SDL2 backend
    - Cross-platform device support with hotplug awareness (connect/disconnect).

- Usability
    - Minimal complete example and intuitive “bind–subscribe–update” flow.

- Reasonable architecture for growth
    - InputTrigger and InputMap provide a flexible base for future devices and triggers.

## Critical review (engineering)
- Build system inconsistencies
    - CMake minimum required version is set unrealistically high, and the target features advertise C++17 while the project uses C++20. This will confuse package consumers and CI.
    - Mixed install and FetchContent strategies are good, but defaults build examples; tests are toggled ON but commented out, which can mislead integrators.

- Robustness and defensive coding
    - Control flow relies on assert(false) in functions expected to return values (undefined behavior in Release); these should return safe fallbacks or error codes.
    - A few places rely on assert-based preconditions for runtime states that can happen in end-user environments (e.g., device churn).

- Runtime behavior and edge cases
    - Gamepad dead-zone computation likely doubles the intended threshold due to the math used; the inline comment says 2% but the formula yields closer to ~4%.
    - Device index and state are not fully reset on disconnect (DeviceIndex persists), which may affect reassignment.
    - Update path polls whole input maps every frame for both keyboard and gamepad. This is fine for small maps, but O(n) per action per device can scale poorly for large bindings or many players.

- API ergonomics and consistency
    - InputMap uses std::map with a rich comparator, but a hash is provided for InputTrigger and not used. For high-frequency lookups, consider a flat/unordered container.
    - Documentation and naming conventions are not fully standardized; some comments claim axis ranges [0,1] when sticks are commonly [-1,1].
    - KeyboardController has a TODO around text input and modifiers; IME and key-repeat modes are common needs.

- Potential logic issues to review
    - Stick and axis handling in the keyboard controller has complex boolean expressions that mix || and && without clear grouping; risk of unintended fallthrough or edge behavior around releases to zero.
    - Switch fallthroughs in helper logic for keyboard axis processing are subtle; readable branching (or explicit [[fallthrough]]/break) would reduce bugs.
    - SpecificInputEvent is a union of non-trivial members; usage relies on disciplined writes/reads keyed by EventType. That’s valid, but easy to misuse—consider std::variant for safety and clarity if binary size is not a concern.

- Testing and quality gates
    - No active automated tests. For an input framework, platform and device matrix tests are essential (hotplug, reconnection, multiple controllers, axis noise).

## Suggestions and future improvements
- Build and packaging
    - Fix CMake minimum version and align C++ standard flags. Provide a minimal-config option (BUILD_EXAMPLES=OFF by default for package consumers).
    - Add CI matrices (Windows/macOS/Linux) building both shared and static, with example smoke tests.

- API and ergonomics
    - Add runtime rebinding and serialization for InputMap (JSON/TOML). This is a big win for games (settings screens, key remapping).
    - Provide per-axis dead-zone, sensitivity curves, and inversion settings. Triggers vs. sticks should have independent defaults.
    - Consider std::variant for SpecificInputEvent and a tagged struct for InputState for stronger type safety.
    - Expose query APIs for action state (pressed/just pressed/released value) in addition to event callbacks for polling-friendly loops.

- Performance and scalability
    - Bucket InputTriggers by device/type to reduce per-frame iteration. Optionally precompute lookup tables keyed by device event to accelerate dispatch.
    - Consider using flat_hash_map/unordered_map for InputMap with the provided hash to lower lookup overhead.

- Device management
    - Normalize dead-zone math; allow configuration at controller and action level.
    - Fully clear device metadata on disconnect; ensure consistent reassignment behavior and index reuse.
    - Add hotplug stress handling (quick unplug/replug) and duplicate device guards.

- Feature coverage
    - Add mouse input (axes, buttons, wheel), text input (IME), and modifier state.
    - Rumble/haptics abstraction, LED, and battery level where available.
    - Multi-player orchestration helpers (auto-assign first active device, on-demand join/leave).
    - Recording/replay for input-driven testing and deterministic repro cases.

- Quality
    - Introduce unit/integration tests: trigger evaluation, map serialization, hotplug, multi-controller scenarios.
    - Static analysis and sanitizers builds. Sample fuzzers around trigger parsing/binding.

- Documentation and examples
    - Expand examples to cover: multiplayer join, runtime rebinding UI, axis curves, and persistence.
    - API reference comments for public headers (Doxygen-compatible). Clear semantics for ranges, frames, and “just pressed” definitions.

## Maturity assessment
- Indie projects and prototypes
    - Ready for prototyping and small to mid-scope indie games. The action mapping and per-player model are immediately useful, and SDL2 ensures broad device support. Lack of tests and some edge-case roughness suggest you should bake in time for integration testing on your target platforms.

- Professional/production
    - Promising but pre-1.0. To be production-ready for larger teams, it needs: consistent build packaging, strong test coverage, robust device lifecycle handling, runtime rebinding with persistence, and comprehensive docs. The architecture supports this evolution, but the current state requires due diligence and targeted improvements before shipping at scale.

## First impressions (as a game dev/C++ engineer)
- The project shows solid intentions: action-centric design, clear separation of input devices, and a pragmatic event system. The code reads straightforwardly, and the example demonstrates a clean developer experience.
- Some corners feel early-stage: build settings are inconsistent, asserts leak into runtime pathways, and a few logic expressions need tightening. None of these are architectural blockers; they’re the kind of issues you clear on the road to 1.0.
- With a bit of polish—tests, device lifecycle hardening, runtime rebinding, and doc expansion—SparkleInput could be a dependable, low-friction input layer for cross-platform games. It already provides the right abstractions; now it needs the guardrails and tooling that make teams confident to ship with it.

If you want, I can draft a prioritized 2–3 sprint plan to reach a 1.0-ready baseline with concrete tickets and test scenarios.

