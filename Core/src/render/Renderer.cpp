#include "Renderer.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "../scene/Entity.h"
#include "../scene/Scene.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace Phantom
{
    Renderer* Renderer::_instance = nullptr;

	Renderer::Renderer()
	{
        if (!_instance)
            _instance = this;
        else
            std::cout << "ERROR::RENDERER::ALREADY_EXISTS" << std::endl;

        _window = nullptr;
        _width = 1920.0f;
        _height = 1080.0f;
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

        _colorFrameBuffer.Create(800, 600);
		return true;
	}

    void Renderer::Clear(glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SetCursorMode(bool enabled)
    {
        if(enabled)
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        else 
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
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
        //Scene._editorCamera.SetAspect(_colorFrameBuffer.Witdh() / _colorFrameBuffer.Height());
        glm::mat4 mvp = Scene._editorCamera.Proj() * Scene._editorCamera.View() * model.matrix();
        meshRenderer._material.GetShader().SendUniformData("mvp", mvp);
        meshRenderer._material.GetShader().SendUniformData("model", model.matrix());
        meshRenderer._material.GetShader().SendUniformData("cameraPos", Scene._editorCamera.position());

        meshRenderer._material.Apply();
        meshRenderer._model.Draw(meshRenderer._material.GetShader());
	}

    Renderer& Renderer::Instance()
    {
        return *_instance;
    }
    void Renderer::Draw(Scene& scene)
    {
        _colorFrameBuffer.Bind();
        Clear(glm::vec4(0.5f, 0.2f, 0.8f, 1.0f));
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
        _colorFrameBuffer.Unbind();
    }
}
