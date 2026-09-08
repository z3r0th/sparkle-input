set(CMAKE_CXX_STANDARD 20)
message(STATUS "Building Sparkle Input examples...")

# Define example sources
file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

message(STATUS "Examples: " ${EXAMPLE_SOURCES})

foreach(example_src ${EXAMPLE_SOURCES})
    get_filename_component(example_name ${example_src} NAME_WE)

    add_executable(${example_name} ${example_src} SDLInitialization.h)
    target_link_libraries(${example_name} PRIVATE Sparkle::SparkleInput)

    # SDL2main may not exist on all platforms (e.g. Linux)
    if(TARGET SDL2::SDL2main)
        target_link_libraries(${example_name} PRIVATE SDL2::SDL2main)
    endif()
    target_link_libraries(${example_name} PRIVATE SDL2::SDL2)

    set_target_properties(${example_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
    )

    message(STATUS "Example added: ${example_name}")
endforeach()