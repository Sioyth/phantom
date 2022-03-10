#include "RenderManager.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
namespace Phantom
{

    RenderManager* RenderManager::_instance = nullptr;

	RenderManager::RenderManager()
	{
		if(!_instance)
			_instance = this;
	}
	bool RenderManager::Init(int width, int heigth)
	{
        _width = width;
        _height = heigth;

        // glfw
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(_width, _height, "Phantom", NULL, NULL);
        _window = window;
        if (_window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(_window);

        // Glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        glViewport(0, 0, 800, 600);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        Shader::LoadDefaultShaders();

		return true;
	}

    void RenderManager::Clear(glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderManager::SwapBuffers()
    {
        glfwSwapBuffers(_window);
    }

	void RenderManager::DrawMesh(Transform& transform, MeshRenderer& meshRenderer)
	{
        //temp
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 5.0f, 10.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 proj = glm::perspective(glm::radians(50.0f), _width / _height, 0.1f, 100.0f);
        glm::mat4 mvp = proj * view * transform._matrix;
        meshRenderer._material.GetShader().SendUniformData("mvp", mvp);
        meshRenderer._material.GetShader().SendUniformData("model", transform._matrix);
        meshRenderer._material.GetShader().SendUniformData("cameraPos", glm::vec3(0.0f, 5.0f, 10.0f));
        meshRenderer._material.GetShader().SendUniformData("_light._color", glm::vec3(1.0f, 0.0f, 0.0f));
        meshRenderer._material.GetShader().SendUniformData("_light._position", glm::vec3(0.0f, 1.0f, 0.0f));
        meshRenderer._material.GetShader().SendUniformData("_light._ambientColor", glm::vec3(1.0f) * 0.2f);

        meshRenderer._material.Apply();
        meshRenderer._model.Draw(meshRenderer._material.GetShader());

	}
    RenderManager& RenderManager::Instance()
    {
        return *_instance;
    }
}
