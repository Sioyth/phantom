#include "Phantom.h"

int width = 800;
int height = 600;

using namespace Phantom;

int main()
{
    // TEMP - DO THIS WHEN YOU CALL INSTANCE;
    Renderer renderer;
    if (!Renderer::Instance().Init())
        return 0;

    Input input = Input(renderer.window());
    UI::Init(renderer.window());

    // TEMP big temp temp
    Scene scene;
    Entity* entity = scene.CreateEntity("Player")->get();
    //Entity* entity = scene.CreateEntity("Backpack");
    ////entity.AddComponent<MeshRenderer>(Phantom::Model("D:\\Dev\\repos\\phantom\\assets\\backpack.obj"));

    Mesh planeMesh;
    Entity* plane = scene.CreateEntity("Plane")->get();
    //plane.GetComponent<Transform>().Scale(glm::vec3(2.0f));
    plane->AddComponent<MeshRenderer>(planeMesh);
    
    Entity* plane2 = scene.CreateEntity()->get();
    plane2->GetComponent<Transform>().Scale(glm::vec3(10.0f));
    plane2->AddComponent<MeshRenderer>(planeMesh);

    Entity* light = scene.CreateEntity()->get();
    light->GetComponent<Transform>().Translate(glm::vec3(0.0f, 1.0f, 2.0f));
    light->AddComponent<Light>(glm::vec3(1.0f, 0.0f, 1.0f));

    //Entity* parent = scene.CreateEntity("Parent");
    //Entity* child = scene.CreateEntity("Children");
    //parent->AddChild(child);
    //Entity* child2 = scene.CreateEntity("Children");
    //child->AddChild(child2);
    //child->SetParent(parent);

    SceneManager::AddScene("Default", &scene);

    while (!Renderer::Instance().ShouldClose())
    {
        // Update Delta Time;
        Time::UpdateDeltaTime(glfwGetTime());
        //EditorLayer::Instance()->Update(Time::DeltaTime());
        SceneManager::ActiveScene()->Update(Time::DeltaTime());
        UI::Render();

        Input::Instance()->PollEvents();
        Renderer::Instance().SwapBuffers();
    }
    glfwTerminate();

    return 0;
}
