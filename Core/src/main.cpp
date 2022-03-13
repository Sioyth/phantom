#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imconfig.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "Renderer.h"
#include "Time.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Input.h"

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

    Scene scene;
    Entity entity = scene.CreateEntity();
    entity.AddComponent<MeshRenderer>(Phantom::Model("D:\\Dev\\repos\\phantom\\assets\\backpack.obj"));

    Mesh planeMesh;
    Entity plane = scene.CreateEntity();
    //plane.GetComponent<Transform>().Scale(glm::vec3(2.0f));
    plane.AddComponent<MeshRenderer>(planeMesh);
    
    Entity plane2 = scene.CreateEntity();
    plane2.GetComponent<Transform>().Scale(glm::vec3(10.0f));
    plane2.AddComponent<MeshRenderer>(planeMesh);

    Entity light = scene.CreateEntity();
    light.GetComponent<Transform>().Translate(glm::vec3(0.0f, 1.5f, 2.0f));
    light.AddComponent<Light>(glm::vec3(1.0f, 1.0f, 1.0f));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    if (!ImGui_ImplGlfw_InitForOpenGL(renderer.window(), true)) { return false; }
    if (!ImGui_ImplOpenGL3_Init()) { return false; }

    SceneManager::AddScene("Default", &scene);

    while (!Renderer::Instance().ShouldClose())
    {
        // Update Delta Time;
        Time::UpdateDeltaTime(glfwGetTime());
        Renderer::Instance().Clear(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        SceneManager::ActiveScene()->Update(Time::DeltaTime());

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        Renderer::Instance().SwapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}
