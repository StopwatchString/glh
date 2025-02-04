#ifndef GLH_OPENGL_APPLICATION_H
#define GLH_OPENGL_APPLICATION_H

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#include "glh/glh.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <thread>
#include <string>
#include <functional>

//------------------------------------------------------
// class: OpenGLApplication
// description: A small framework for managing a multithreaded
//              OpenGL window through GLFW with DearImgui
//              built in and automatically initialized.
//------------------------------------------------------

class OpenGLApplication
{
public:
    struct ApplicationConfig
    {
        std::string windowName;
        int windowInitWidth{0};
        int windowInitHeight{0};
        int windowPosX{0};
        int windowPosY{0};
        bool windowBorderless{false};
        bool windowResizeEnable{false};
        bool windowDarkmode{false};
        bool windowRounded{false};
        bool windowAlwaysOnTop{false};
        bool vsyncEnable{false};
        bool transparentFramebuffer{false};
        int glVersionMajor{4};
        int glVersionMinor{6};
        std::string dearImguiGlslVersionString{"#version 460"};
        const char* imguiIniFileName{nullptr};
        std::function<void(GLFWwindow*)> customDrawFunc = nullptr;
        // std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)>
        GLFWkeyfun customKeyCallback = nullptr;
        // std::function<void(int error_code, const char* description)>
        GLFWerrorfun customErrorCallback = nullptr;
        // std::function<void(GLFWwindow* window, int count, const char** paths)>
        GLFWdropfun customDropCallback = nullptr;
        std::function<void()> customPollingFunc = nullptr;
    };

    OpenGLApplication(const ApplicationConfig& appConfig);
    ~OpenGLApplication();

private:
    void initGLFW();
    void initExtensions();
    void initDearImgui();
    void startRenderThread();
    void eventLoop();

    void renderFunc() const;

    const ApplicationConfig appConfig{};

    GLFWwindow* glfwWindow{nullptr};
    ImGuiContext* imguiContext{nullptr};

    std::thread renderThread;
};

#endif