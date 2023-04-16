cmake_minimum_required(VERSION 3.14)

project(InstrumentCluster VERSION 0.1.0 LANGUAGES CXX C)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the C standard to C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

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

# Add the include directories for Unix systems
include(GNUInstallDirs)
include_directories(/usr/local/include /opt/homebrew/include /opt/homebrew/Cellar/sdl2/2.26.3/include)

# Add the library directories
link_directories(/usr/local/lib /opt/homebrew/Cellar/sdl2/2.26.3/lib)

# Add the include directories for Mac OS X
if(APPLE)
    # Homebrew include directory
    include_directories("/opt/homebrew/include")
endif()

# Find the SDL2 library
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Find the fmt library
find_package(fmt REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find NanoSVG
find_package(NanoSVG REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})

if (APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "13.3" CACHE STRING "Minimum OS X deployment version")
    set(CMAKE_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk" CACHE STRING "System root for OS X")
endif()

# Add executable for the application
add_executable(InstrumentCluster
    ${SOURCE_CPP}
    ${SOURCE_HEADER}
    src/imgui/imgui.cpp
    src/imgui/imgui_stdlib.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_demo.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_impl_sdl2.cpp
    src/imgui/imgui_impl_opengl3.cpp
)

target_compile_options(InstrumentCluster PRIVATE -w)


# Link libraries
target_link_libraries(InstrumentCluster
    fmt::fmt
    OpenGL::GL
    SDL2::SDL2
    SDL2_image::SDL2_image
    NanoSVG::nanosvg
    NanoSVG::nanosvgrast
)

# Apple specific libraries
if (APPLE)
    target_link_libraries(InstrumentCluster "-framework OpenGL")
    else()
    target_link_libraries(InstrumentCluster GL dl)
endif()
