#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include <fstream>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

template <typename Derived>
class App {
public:
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    bool quit = false;

    App(const char* appName, int windowSizeWidth, int windowSizeHeight) {
        //App(){
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
            exit(1);

        // Create window with graphics context
        window = glfwCreateWindow(windowSizeWidth, windowSizeWidth, appName, nullptr, nullptr);
        if (window == nullptr)
            exit(1);
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        {
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        }

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL2_Init();
    }
    ~App() {
        // Cleanup
        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Run() {
        StartUp();

        while (!glfwWindowShouldClose(window) && !quit) {
            // Poll and handle events 
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL2_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            Update();

            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
            glfwMakeContextCurrent(window);
            glfwSwapBuffers(window);
        }
    }
    void Update() { static_cast<Derived*>(this)->Update(); }
    void StartUp() { static_cast<Derived*>(this)->StartUp(); }
    //void changeDinamicWindow(std::string title) {glfwSetWindowTitle(window, std::to_string(appName + " - " + title.c_str())); } /*V2.0 TO FIX*/
private:
     GLFWwindow* window;
    //const char* appName; /*V2.0 TO FIX*/
};