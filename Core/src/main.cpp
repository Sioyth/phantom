#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imconfig.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Shader/Shader.h"
#include "Entity.h"
#include "Components/Transform.h"
#include "Components/Camera.h"

#include "Input.h"
#include "Components/DebugMovement.h"
#include "Components/Renderer.h"
#include "Time.h"

int width = 800;
int height = 600;

std::vector<Entity> _entities;
int main()
{

    // glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    // Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Engine Core
    Input input = Input(window);
    Shader::LoadDefaultShaders();

    Entity cube = Entity();
    cube.AddComponent<Renderer>();
    cube.GetComponent<Renderer>()->LoadModel("D:\\Dev\\repos\\phantom\\assets\\backpack.obj");
    _entities.push_back(cube);

    Entity camera = Entity();
    camera.AddComponent<Camera>();
    camera.AddComponent<DebugMovement>();
    camera.GetComponent<Transform>()->Translate(glm::vec3(0.0f, 0.0f, -3.0f));
    _entities.push_back(camera);
    
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 mvp;

    while (!glfwWindowShouldClose(window))
    {
        // Update Delta Time;
        Time::UpdateDeltaTime((float)glfwGetTime());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        Shader::UseDefault();

        for (int i = 0; i < _entities.size(); i++)
        {
            if (!_entities[i].IsEnabled())
                continue;

            _entities[i].Update();

            // temp
            glm::mat4 model = _entities[i].GetComponent<Transform>()->GetMatrix();
            glm::mat4 view = Camera::GetMainCamera()->GetEntity()->GetComponent<Transform>()->GetMatrix();
            mvp = proj * view * model; 
            
            GLuint loc = glGetUniformLocation(Shader::GetDefaultID(), "mvp");
            glUniformMatrix4fv(loc, 1, GL_FALSE, &mvp[0][0]);
        }

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}
