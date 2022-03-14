#include "Renderer.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "Scene.h"

namespace Phantom
{
    Renderer* Renderer::_instance = nullptr;

	Renderer::Renderer()
	{
		if(!_instance)
			_instance = this;

        _window = nullptr;
        _width = 800.0f;
        _height = 600.0f;
        _mvp = glm::mat4(1.0f);
	}

	bool Renderer::Init(int width, int heigth)
	{
        _width = 800;
        _height = 600;

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
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		return true;
	}

    void Renderer::Clear(glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SwapBuffers()
    {
        glfwSwapBuffers(_window);
    }

    void Renderer::DrawLight(Transform& transform, Light& light)
    {
        Shader::CurrentShader().SendUniformData("_light._color", light._color);
        Shader::CurrentShader().SendUniformData("_light._position", transform.position());
        Shader::CurrentShader().SendUniformData("_light._ambientColor", glm::vec3(1.0f) * 0.2f);
    }

	void Renderer::DrawMesh(Transform& model, MeshRenderer& meshRenderer, Scene& Scene)
	{
        //temp
        // if not editor ...
        
       /* Camera& cam = Scene._activeCamera->GetComponent<Camera>();
        cam.CalculateMatrices(*Scene._activeCamera->transform());
        glm::mat4 mvp = cam.proj() * cam.view() * model.matrix();*/
           
        /*meshRenderer._material.GetShader().SendUniformData("mvp", mvp);
        meshRenderer._material.GetShader().SendUniformData("model", model.matrix());
        meshRenderer._material.GetShader().SendUniformData("cameraPos", camera.transform());*/

        glm::mat4 mvp = Scene._editorCamera.Proj() * Scene._editorCamera.View() * model.matrix();
        meshRenderer._material.GetShader().SendUniformData("mvp", mvp);
        meshRenderer._material.GetShader().SendUniformData("model", model.matrix());

        meshRenderer._material.Apply();
        meshRenderer._model.Draw(meshRenderer._material.GetShader());
	}
    Renderer& Renderer::Instance()
    {
        return *_instance;
    }
    void Renderer::Draw(Scene& scene)
    {
        const auto& lights = scene._registry.view<Light, Transform>();
        for (auto entity : lights)
        {
            const auto& [transform, light] = lights.get<Transform, Light>(entity);
            DrawLight(transform, light);
        };

        const auto meshes = scene._registry.view<Transform, MeshRenderer>();
        for (auto entity : meshes)
        {
            const auto& [transform, mesh] = meshes.get<Transform, MeshRenderer>(entity);
            Renderer::Instance().DrawMesh(transform, mesh, scene);
        }
    }
}
