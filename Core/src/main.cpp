#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
//#include <imgui/imconfig.h>
//#include <imgui/imgui_impl_glfw.h>
//#include <imgui/imgui_impl_opengl3.h>
#include "RenderManager.h"
#include "Time.h"
//#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"

int width = 800;
int height = 600;

using namespace Phantom;

int main()
{
    // TEMP - DO THIS WHEN YOU CALL INSTANCE;
    RenderManager manager;
    if (!RenderManager::Instance().Init())
        return 0;

    Scene scene;

    // TEMP
    Entity entity = scene.CreateEntity();
    entity.AddComponent<MeshRenderer>(Phantom::Model("D:\\Dev\\repos\\phantom\\assets\\backpack.obj"));
    entity.GetComponent<Transform>()._matrix = glm::translate(entity.GetComponent<Transform>()._matrix, glm::vec3(0.0f, 2.0f, 0.0f));

    Mesh planeMesh;
    Entity plane = scene.CreateEntity();
    plane.GetComponent<Transform>()._matrix = glm::scale(plane.GetComponent<Transform>()._matrix, glm::vec3(15.0f));
    plane.AddComponent<MeshRenderer>(planeMesh);

    Entity light = scene.CreateEntity();
    light.AddComponent<Light>(glm::vec3(0.5f, 0.2f, 0.3f));

    
    while (true)
    {
        // Update Delta Time;
        Time::UpdateDeltaTime(glfwGetTime());
        RenderManager::Instance().Clear();

        // feed inputs to dear imgui, start new frame
      /*  ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();*/
        scene.Update();
        // Render dear imgui into screen
        /*ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/

        glfwPollEvents();
        RenderManager::Instance().SwapBuffers();
    }

    /*ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();*/

    glfwTerminate();

    return 0;
}
