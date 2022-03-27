#include "Window.h"

namespace Phantom
{
    bool Window::Create()
    {
        // glfw
        _viewPort.x = 800;
        _viewPort.y = 600;
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(_viewPort.x, _viewPort.y, "Phantom", NULL, NULL);
        _window = window;
        if (_window == NULL)
        {
            //std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(_window);
    }

    void Window::SwapBuffers()
    {
        glfwSwapBuffers(_window);
    }

    void Window::SetCursorMode(bool enabled)
    {

    }

    Window::~Window()
    {
        delete _window;
        glfwTerminate();
    }
}
