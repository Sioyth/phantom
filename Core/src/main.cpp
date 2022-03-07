#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

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

int main()
{
    std::vector<Entity> _entities;

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

    Input input = Input(window);

    // TODO: Fix this fucking paths
    Shader::LoadDefaultShaders();
    
    Entity cube = Entity(); \
    cube.AddComponent<Renderer>();
    cube.GetComponent<Renderer>()->LoadModel("D:\\Dev\\repos\\phantom\\assets\\backpack.obj");
    _entities.push_back(cube);

    Entity camera =  Entity();
    camera.AddComponent<Camera>();
    camera.AddComponent<DebugMovement>();
    camera.GetComponent<Transform>()->Translate(glm::vec3(0.0f, 0.0f, -3.0f));
    _entities.push_back(camera);

    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians(-80.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 mvp;

    while (!glfwWindowShouldClose(window))
    {
        // Update Delta Time;
        Time::UpdateDeltaTime((float)glfwGetTime());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();

    return 0;
}