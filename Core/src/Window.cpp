#include "Window.h"
#include <iostream>

namespace Phantom
{

    bool Window::Create()
    {
        _viewPort.x = 800;
        _viewPort.y = 600;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _window = glfwCreateWindow(_viewPort.x, _viewPort.y, "Phantom", NULL, NULL);
        if (_window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(_window);

        // Glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            std::cout << "Failed to initialize GLAD" << std::endl;

        // temp
        glViewport(0, 0, _viewPort.x, _viewPort.y);
        glDepthRange(-1, 1);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        return true;
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
