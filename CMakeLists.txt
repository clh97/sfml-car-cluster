cmake_minimum_required(VERSION 3.14)

include(FetchContent)

# Add the fmt library as a dependency
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        master
    GIT_PROGRESS    TRUE
)

FetchContent_MakeAvailable(fmt)

# Add the SDL2 library as a dependency
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        SDL2
    GIT_PROGRESS   TRUE
)

FetchContent_MakeAvailable(SDL2)

# Add the SDL2_image library as a dependency
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_image
    GIT_TAG         SDL2
    GIT_PROGRESS    TRUE
)

FetchContent_MakeAvailable(SDL2_image)

project(InstrumentCluster VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

# Declare SOURCE_CPP and SOURCE_HEADER variables
file(GLOB SOURCE_CPP
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

file(GLOB SOURCE_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
)

# Add executable for the application
add_executable(InstrumentCluster
    ${SOURCE_CPP}
    ${SOURCE_HEADER}
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_demo.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_impl_sdl2.cpp
    src/imgui/imgui_impl_opengl3.cpp
)

# Add the include directories for Unix systems
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} /usr/local/include /usr/local/include/SDL2 /usr/local/include/glad /usr/local/include/imgui)
include(GNUInstallDirs)

# Add the include directories for Mac OS X
if(APPLE)
    # Homebrew include directory
    include_directories("/opt/homebrew/include")
endif()

# Find the SDL2 library
# find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Find the fmt library
find_package(fmt REQUIRED)

# Link the executable against the necessary libraries (SDL2, SDL2_image, fmt, glad)
target_link_libraries(InstrumentCluster PRIVATE SDL2 SDL2main SDL2_image fmt::fmt dl "-framework OpenGL")
