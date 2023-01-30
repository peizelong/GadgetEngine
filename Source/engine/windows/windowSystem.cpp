#include "windowSystem.h"
namespace GE {
    void windowSystem::init()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
    }
    GLFWwindow* windowSystem::getWindow()
    {
        return window;
    }
    bool windowSystem::windowClose()
    {
        return !glfwWindowShouldClose(window);
    }
    void windowSystem::windowEvent()
    {
        glfwPollEvents();
    }
    void windowSystem::destory()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}