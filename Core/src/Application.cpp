#include "Application.h"
#include <iostream>
namespace Phantom
{
    void Application::Start()
    {
        _window.Create();
        LoadGlad();

        Input::Instance()->SetWindow(_window.Handle());
        UI::Init(_window.Handle());

        Run();
    }

    void Application::Run()
    {
        while (!_window.ShouldClose())
        {
            Time::UpdateDeltaTime(glfwGetTime());
            EditorLayer::Instance()->Update(Time::DeltaTime());
            Input::Instance()->PollEvents();
            _window.SwapBuffers();
        }
    }

    Application::Application()
    {
        Start();
    }

    void Application::LoadGlad()
    {
        // Glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            //quit
        }

        // temp
        glViewport(0, 0, 800, 600);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void Application::Quit()
    {
    }

    Application::~Application()
    {
        Quit();
    }

}
