cmake_minimum_required(VERSION 4.0)
project(SparkleInput VERSION 0.9.0 LANGUAGES CXX)

include(CMakePackageConfigHelpers)
set(CMAKE_CXX_STANDARD 20)

option(SPARKLE_INPUT_BUILD_TESTS "Build SparkleInputs test cases" ON)
option(SPARKLE_INPUT_BUILD_EXAMPLES "Build SparkleInputs examples" ON)

add_library(SparkleInput
        src/Sparkle/input_process/GamepadInputProcess.cpp
        src/Sparkle/input_process/GamepadInputProcess.h
        src/Sparkle/input_process/InputProcess.h
        src/Sparkle/input_process/KeyboardInputProcess.cpp
        src/Sparkle/input_process/KeyboardInputProcess.h
        src/Sparkle/GamepadController.cpp
        src/Sparkle/GamepadController.h
        src/Sparkle/Input.cpp
        src/Sparkle/Input.h
        src/Sparkle/InputAction.h
        src/Sparkle/InputController.cpp
        src/Sparkle/InputController.h
        src/Sparkle/InputEvent.h
        src/Sparkle/InputMap.h
        src/Sparkle/KeyboardController.cpp
        src/Sparkle/KeyboardController.h
        src/Sparkle/PlayerInputController.cpp
        src/Sparkle/PlayerInputController.h
)
add_library(Sparkle::SparkleInput ALIAS SparkleInput)

target_include_directories(SparkleInput PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:src> )

target_compile_features(SparkleInput PUBLIC cxx_std_17)
install(TARGETS SparkleInput EXPORT SparkleInputTargets)
install(DIRECTORY src/ DESTINATION src)
install(EXPORT SparkleInputTargets FILE SparkleInputTargets.cmake NAMESPACE Sparkle:: DESTINATION lib/cmake/SparkleInput )

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/SparkleInputConfigVersion.cmake"
        VERSION ${PROJECT_VERSION} COMPATIBILITY SameMajorVersion )
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/SparkleInputConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/SparkleInputConfig.cmake"
        INSTALL_DESTINATION lib/cmake/SparkleInput )
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/SparkleInputConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/SparkleInputConfigVersion.cmake"
        DESTINATION
        lib/cmake/SparkleInput )

include(FetchContent)
# Get SDL2 from find_package (SDL2::SDL2 package installed) or get it from source on github
FetchContent_Declare(
        SDL2_PCK
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.28.5
        FIND_PACKAGE_ARGS NAMES SDL2 SDL2main SDL2static )
FetchContent_MakeAvailable(SDL2_PCK)
# SDL2
# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(SparkleInput PUBLIC SDL2::SDL2main)
endif()
target_link_libraries(SparkleInput PUBLIC SDL2::SDL2)

message ("Fetching Sparkle Event")
FetchContent_Declare(
        sparkle-events
        GIT_REPOSITORY https://gitlab.com/sparkle-game-engine/sparkle-event.git
        GIT_TAG main
        FIND_PACKAGE_ARGS )
set(SPARKLE_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPARKLE_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(sparkle-events)
target_link_libraries(SparkleInput PUBLIC Sparkle::SparkleEvents)

get_target_property(INCLUDES SparkleInput INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "SparkleInput includes: ${INCLUDES}")

if(SPARKLE_INPUT_BUILD_TESTS)
    #enable_testing()
    #add_subdirectory(tests)
endif()

if(SPARKLE_INPUT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()