cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(imgui-standalone-opengl VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Use GLVND for OpenGL
cmake_policy(SET CMP0072 NEW)

# Find necessary libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# ImGui paths
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp

    # Backends for GLFW and OpenGL3
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_executable(imgui-standalone-opengl
    src/main.cpp
    ${IMGUI_SOURCES}
)

target_include_directories(imgui-standalone-opengl PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Link all required libraries
target_link_libraries(imgui-standalone-opengl PRIVATE
    OpenGL::GL
    glfw
)
