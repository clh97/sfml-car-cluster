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

# Add the include directories for Unix systems
include(GNUInstallDirs)
include_directories(/usr/local/include /opt/homebrew/include /opt/homebrew/Cellar/sdl2/2.26.3/include)

# Add the library directories
link_directories(/usr/local/lib /opt/homebrew/lib /opt/homebrew/Cellar/sdl2/2.26.3/lib)
link_libraries(/usr/local/lib /opt/homebrew/Cellar/sdl2/2.26.3/lib)

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

# Find PkgConfig
find_package(PkgConfig REQUIRED)

# Find SDL2 and SDL2_image
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_image REQUIRED IMPORTED_TARGET sdl2_image)

include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})

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

# Link libraries
target_link_libraries(InstrumentCluster fmt::fmt OpenGL::GL ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# Apple specific libraries
if (APPLE)
    target_link_libraries(InstrumentCluster "-framework OpenGL")
endif()
