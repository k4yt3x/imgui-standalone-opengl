# ImGui Standalone OpenGL

An example standalone ImGui windowed application rendered with OpenGL and GLFW.

This project is a simple example of how to create a standalone ImGui windowed application using OpenGL and GLFW. OpenGL is the rendering API, GLFW creates and manages the platform window, and ImGui draws the GUI. It may be a good starting point if you want to create a standalone windowed application with ImGui. So far it has only been tested on Arch Linux.

![screenshot](https://github.com/user-attachments/assets/75d28d90-4e76-492a-b277-92c2bbd8fda7)

## Features

- Standalone ImGui windowed application
- Renders with OpenGL and GLFW
- Custom ImGui style
- Basic ImGui widgets (buttons, sliders, text, etc.)
- Floating ImGui windows
- FPS counter

## Build

Follow the instructions below to build the project on Arch Linux:

```bash
# Clone the repository
git clone https://github.com/k4yt3x/imgui-standalone-opengl.git
cd imgui-standalone-opengl
git submodule update --init --recursive

# Install dependencies
pacman -Sy mesa libglvnd glfw

# Build the project
cmake -S . -B build
cmake --build build
```

The built binary will be located at `build/imgui-standalone-opengl`.
