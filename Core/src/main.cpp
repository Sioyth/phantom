#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

//#include <imgui/imconfig.h>
//#include <imgui/imgui_impl_glfw.h>
//#include <imgui/imgui_impl_opengl3.h>
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

    GLFWwindow* window = glfwCreateWindow(width, height, "Phantom", NULL, NULL);
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
    glDepthFunc(GL_LESS);

    //// Setup Dear ImGui context
    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO();
    //// Setup Platform/Renderer bindings
    //ImGui_ImplGlfw_InitForOpenGL(window, true);
    //ImGui_ImplOpenGL3_Init("#version 460");
    //// Setup Dear ImGui style
    //ImGui::StyleColorsDark();

    // Engine Core
    Input input = Input(window);
    Shader::LoadDefaultShaders();

    Entity cube = Entity();
    cube.Name("Model");
    cube.AddComponent<Renderer>();
    cube.GetComponent<Renderer>()->LoadModel("D:\\Dev\\repos\\phantom\\assets\\backpack.obj");
    cube.GetComponent<Transform>()->Translate(glm::vec3(2.0f, 0.0f, 1.0f));
    //cube.AddComponent<DebugMovement>();
    _entities.push_back(cube);
  
    Entity cube3 = Entity();
    cube3.Name("Model3");
    cube3.AddComponent<DebugMovement>();
    cube3.GetComponent<Transform>()->Translate(glm::vec3(-2.0f, 0.0f, -1.0f));
    cube3.AddComponent<Renderer>();
    cube3.GetComponent<Renderer>()->LoadModel("D:\\Dev\\repos\\phantom\\assets\\backpack.obj");
    _entities.push_back(cube3);

    Entity cube4 = Entity();
    cube4.AddComponent<Renderer>();
    cube4.GetComponent<Renderer>()->LoadModel("D:\\Dev\\repos\\phantom\\assets\\backpack.obj");
    _entities.push_back(cube4);
    

    //Entity camera = Entity();
    //camera.AddComponent<Camera>();
    ////camera.GetComponent<Transform>()->Translate(glm::vec3(0.0f, 0.0f, 10.0f));
    ////camera.AddComponent<DebugMovement>();
    //_entities.push_back(camera);

    
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));;
    glm::mat4 mvp = glm::mat4(1.0f);

    while (!glfwWindowShouldClose(window))
    {
        // Update Delta Time;
        Time::UpdateDeltaTime(glfwGetTime());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // feed inputs to dear imgui, start new frame
      /*  ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();*/

        Shader::UseDefault();
        for (int i = 0; i < _entities.size(); i++)
        {
            if (!_entities[i].IsEnabled())
                continue;

            _entities[i].Update();

            // temp
            glm::mat4 model = _entities[i].GetComponent<Transform>()->Matrix();
            //model = cube.GetComponent<Transform>()->Matrix();
         /*   model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(1.0f, -1.0f, 0.0f));
            model = _entities[i].GetComponent<Transform>()->Matrix();
            model = glm::translate(model, glm::vec3(1.0f, -1.0f, 0.0f));*/

           /* if (Input::Instance()->GetKey(GLFW_KEY_W, KeyState::PRESS))
                _entities[i].GetComponent<Transform>()->Translate(glm::vec3(0.0f, 0.0f, 10.0f));

            if (Input::Instance()->GetKey(GLFW_KEY_S, KeyState::PRESS))
                _entities[i].GetComponent<Transform>()->Translate(glm::vec3(0.0f, 0.0f, -0.1f));

            if (Input::Instance()->GetKey(GLFW_KEY_A, KeyState::PRESS))
                _entities[i].GetComponent<Transform>()->Translate(glm::vec3(-0.1f, 0.0f, 0.0f));

            if (Input::Instance()->GetKey(GLFW_KEY_D, KeyState::PRESS))
                _entities[i].GetComponent<Transform>()->Translate(glm::vec3(0.1f, 0.0f, 0.0f));*/

            //model = glm::mat4(1.0f);
            //model = glm::translate(model, _entities[i].GetComponent<Transform>()->Position());
            
            //glm::mat4 view = Camera::GetMainCamera()->GetEntity()->GetComponent<Transform>()->Matrix();
          
           /* float z = Camera::GetMainCamera()->GetEntity()->GetComponent<Transform>()->Position().z;
            z = _entities[i].GetComponent<Transform>()->Position().z;*/
            //std::cout << _entities[i].Name() + "Z: " << z << std::endl;
            std::cout << _entities[i].Name() + " - " << _entities[i].GetComponent<Transform>()->Matrix()[3][2] << std::endl;
            mvp = proj * view * model;
        }

        // Render dear imgui into screen
        /*ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    /*ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();*/

    glfwTerminate();

    return 0;
}
