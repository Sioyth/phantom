#include "Application.h"
#include <iostream>
namespace Phantom
{
    Application::Application()
    {
        Start();
    }

    void Application::Start()
    {
        _window.Create();

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

    void Application::Quit()
    {
        UI::ShutDown();
    }

    Application::~Application()
    {
        Quit();
    }

}
