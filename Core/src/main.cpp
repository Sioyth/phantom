#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include "Shader/Shader.h"
#include "Entity.h"
#include "Components/Transform.h"


int main()
{
    std::vector<Entity> _entities;

    // glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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


    // TODO: Fix this fucking paths
    Shader shader = Shader("C:\\Users\\Joao Parreira\\source\\repos\\Phantom\\Core\\src\\Shader\\default.vert", "C:\\Users\\Joao Parreira\\source\\repos\\Phantom\\Core\\src\\Shader\\default.frag");
    
    _entities.push_back(Entity());
    
    unsigned int VAO, VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float pos[6] = 
    {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 *sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glPointSize(5.0f);


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        shader.SendUniformData("color", 1.0f, 1.0f, 0.0f);

        for (int i = 0; i < _entities.size(); i++)
        {
            if(_entities[i].IsEnabled()) 
                _entities[i].Update();
        }

        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, 2);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();

    return 0;
}