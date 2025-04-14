#ifndef GLH_OPENGL_APPLICATION_H
#define GLH_OPENGL_APPLICATION_H

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <thread>
#include <string>
#include <functional>

namespace glh {

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
        // std::function<void(GLFWwindow* window, int button, int action, int mods)>
        GLFWmousebuttonfun customMouseButtonCallback = nullptr;
        // std::function<void(GLFWwindow* window, double xpos, double ypos)>
        GLFWcursorposfun customCursorPosCallback = nullptr;
        // std::function<void(GLFWwindow* window, double xoffset, double yoffset)>
        GLFWscrollfun customScrollCallback = nullptr;
        // std::function<void(int error_code, const char* description)>
        GLFWerrorfun customErrorCallback = nullptr;
        // std::function<void(GLFWwindow* window, int count, const char** paths)>
        GLFWdropfun customDropCallback = nullptr;
        std::function<void()> customPollingFunc = nullptr;
    };

    //glh::OpenGLApplication::ApplicationConfig config;
    //config.windowName = "Dted Viewer";
    //config.windowInitWidth = 0;
    //config.windowInitHeight = 0;
    //config.windowPosX = 0;
    //config.windowPosY = 0;
    //config.windowBorderless = false;
    //config.windowResizeEnable = false;
    //config.windowDarkmode = false;
    //config.windowRounded = false;
    //config.windowAlwaysOnTop = false;
    //config.vsyncEnable = false;
    //config.transparentFramebuffer = false;
    //config.glVersionMajor = 4;
    //config.glVersionMinor = 6;
    //config.dearImguiGlslVersionString = "#version 460";
    //config.imguiIniFileName = nullptr;
    //config.customDrawFunc = nullptr;
    //// std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)>
    //config.customKeyCallback = nullptr;
    //// std::function<void(int error_code, const char* description)>
    //config.customErrorCallback = nullptr;
    //// std::function<void(GLFWwindow* window, int count, const char** paths)>
    //config.customDropCallback = nullptr;
    //config.customPollingFunc = nullptr;

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

} // End glh

#endif
