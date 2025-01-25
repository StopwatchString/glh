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
//
//  Default Config for copy/paste:
//  OpenGLApplication::ApplicationConfig appConfig;
//  appConfig.windowName = "";
//  appConfig.windowInitWidth = 0;
//  appConfig.windowInitHeight = 0;
//  appConfig.windowPosX = 0;
//  appConfig.windowPosY = 0;
//  appConfig.windowBorderless = false;
//  appConfig.windowResizeEnable = false;
//  appConfig.windowDarkmode = false;
//  appConfig.windowRounded = false;
//  appConfig.windowAlwaysOnTop = false;
//  appConfig.vsyncEnable = false;
//  appConfig.transparentFramebuffer = false;
//  appConfig.glVersionMajor = 4;
//  appConfig.glVersionMinor = 6;
//  appConfig.glslVersionString = "#version 460"; // Used for DearImgui, leave default unless you know what to put here
//  appConfig.imguiIniFileName = nullptr;
//  appConfig.customDrawFunc = nullptr;      // std::function<void(GLFWwindow*)>
//  appConfig.customKeyCallback = nullptr;   // std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)>
//  appConfig.customErrorCallback = nullptr; // std::function<void(int error_code, const char* description)>
//  appConfig.customDropCallback = nullptr;  // std::function<void(GLFWwindow* window, int count, const char** paths)>
//  appConfig.customPollingFunc = nullptr;   // std::function<void()>
//------------------------------------------------------

class OpenGLApplication
{
public:
    struct ApplicationConfig
    {
        std::string windowName;
        int windowInitWidth         { 0 };
        int windowInitHeight        { 0 };
        int windowPosX              { 0 };
        int windowPosY              { 0 };
        bool windowBorderless       { false };
        bool windowResizeEnable     { false };
        bool windowDarkmode         { false };
        bool windowRounded          { false };
        bool windowAlwaysOnTop      { false };
        bool vsyncEnable            { false };
        bool transparentFramebuffer { false };
        int glVersionMajor          { 4 };
        int glVersionMinor          { 6 };
        std::string glslVersionString { "#version 460" }; // Used for DearImgui, leave default unless you know what to put here
        const char* imguiIniFileName { nullptr };
        std::function<void(GLFWwindow*)> customDrawFunc = nullptr;
        GLFWkeyfun customKeyCallback = nullptr; // std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)>
        GLFWerrorfun customErrorCallback = nullptr; // std::function<void(int error_code, const char* description)>
        GLFWdropfun customDropCallback = nullptr; // std::function<void(GLFWwindow* window, int count, const char** paths)>
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

    ApplicationConfig appConfig{};

    GLFWwindow* glfwWindow{ nullptr };
    ImGuiContext* imguiContext{ nullptr };

    std::thread renderThread;
};

#endif