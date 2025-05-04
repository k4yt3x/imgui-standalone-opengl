#include <iostream>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// Enum that represents the selected tab
enum class Tab {
    Tab0,
    Tab1,
    Tab2
};

static void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main() {
    // Setup GLFW
    glfwSetErrorCallback(glfw_error_callback);
    if (glfwInit() != GLFW_TRUE) {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return 1;
    }

    // Use OpenGL 3.3 core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a system window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(900, 500, "ImGui Standalone OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return 1;
    }

    // Set the OpenGL context for the window
    glfwMakeContextCurrent(window);

    // Enable VSync
    glfwSwapInterval(1);

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Do not save configs to an .ini file
    io.IniFilename = nullptr;

    // Setup ImGui style
    ImGui::StyleColorsDark();

    // Define the window background color used by both the system window and ImGui
    ImVec4 bg_color = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);  // Dark gray

    // Adjust individual components' colors
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = bg_color;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Application variables
    Tab selected_tab = Tab::Tab0;
    float slider_value = 0.0f;
    int counter = 0;
    bool show_floating_window = false;
    bool show_demo_window = false;

    // FPS variables
    double fps = 0.0f;
    double last_time = glfwGetTime();
    int nb_frames = 0;

    while (glfwWindowShouldClose(window) == GLFW_FALSE) {
        // Poll and handle events
        glfwPollEvents();

        // Check for Ctrl+Q to quit
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS &&
            (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
             glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        // Calculate FPS
        double currentTime = glfwGetTime();
        nb_frames++;
        if (currentTime - last_time >= 1.0f) {
            fps = float(nb_frames) / (currentTime - last_time);
            nb_frames = 0;
            last_time = currentTime;
        }

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Fill the system window
#ifdef IMGUI_HAS_VIEWPORT
        ImGuiViewPort* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
#else
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(io.DisplaySize);
#endif

        {
            ImGui::Begin(
                "##vtabs",
                nullptr,
                ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus
            );

            ImGui::BeginChild("##tabs", ImVec2(200, 0), true);

            // Vertical tab items
            if (ImGui::Selectable("Tab 0", selected_tab == Tab::Tab0)) {
                selected_tab = Tab::Tab0;
            }
            if (ImGui::Selectable("Tab 1", selected_tab == Tab::Tab1)) {
                selected_tab = Tab::Tab1;
            }
            if (ImGui::Selectable("Tab 2", selected_tab == Tab::Tab2)) {
                selected_tab = Tab::Tab2;
            }

            ImGui::EndChild();

            // Content area on the right
            ImGui::SameLine();
            ImGui::BeginChild("Tab Content");

            if (selected_tab == Tab::Tab0) {
                // Display FPS
                ImGui::Text("Render FPS: %.1f", fps);

                // Text
                ImGui::Text("This is content for Tab 0.");

                // Slider
                ImGui::SliderFloat("Float slider", &slider_value, 0.0f, 1.0f);

                // Button with a counter
                if (ImGui::Button("Button")) {
                    counter++;
                }
                ImGui::SameLine();
                ImGui::Text("Counter = %d", counter);

                // Checkbox
                ImGui::Checkbox("Open a floating window", &show_floating_window);

                // Demo window
                ImGui::Checkbox("Show demo window", &show_demo_window);
            } else if (selected_tab == Tab::Tab1) {
                ImGui::Text("This is content for Tab 1.");
            } else if (selected_tab == Tab::Tab2) {
                ImGui::Text("This is content for Tab 2.");
            }

            ImGui::EndChild();
            ImGui::End();
        }

        // A simple floating window
        if (show_floating_window) {
            ImGui::Begin("A Floating Window", &show_floating_window);
            ImGui::Text(
                "This is a floating window!\n"
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n"
                "Vestibulum ultrices metus non sapien malesuada, quis tempus magna placerat."
            );
            ImGui::End();
        }

        // Demo window
        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(bg_color.x, bg_color.y, bg_color.z, bg_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render ImGui draw data
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // ImGui cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // GLFW cleanup
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
