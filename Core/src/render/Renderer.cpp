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
        Shader::LoadDefaultShaders();
	}

    void Renderer::Clear(glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::DrawLight(Transform& transform, Light& light)
    {
        Shader::CurrentShader().SendUniformData("_light._color", light._color);
        Shader::CurrentShader().SendUniformData("_light._position", transform.position());
        Shader::CurrentShader().SendUniformData("_light._ambientColor", glm::vec3(1.0f) * 0.2f); // hardcoded for now
    }

	void Renderer::DrawMesh(Transform& model, MeshRenderer& meshRenderer, Scene& Scene, EditorCamera& camera, const float& aspectRatio)
	{
        //temp
        // if not editor ...
        //Scene._editorCamera.SetAspect(_colorFrameBuffer.Witdh() / _colorFrameBuffer.Height());
        camera.SetAspectRatio(aspectRatio);
        glm::mat4 mvp = camera.Proj() * camera.View() * model.matrix();
        meshRenderer._material.GetShader().SendUniformData("mvp", mvp); // change it to just mv.
        meshRenderer._material.GetShader().SendUniformData("model", model.matrix()); 
        meshRenderer._material.GetShader().SendUniformData("cameraPos", camera.position());

        meshRenderer._material.Apply();
        meshRenderer._model.Render(meshRenderer._material.GetShader());
	}

    Renderer* Renderer::Instance()
    {
        if (_instance == nullptr)
            _instance = new Renderer();
        return _instance;
    }
    void Renderer::Render(Scene& scene, EditorCamera& camera, const float& aspectRatio)
    {
        Clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
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
            DrawMesh(transform, mesh, scene, camera, aspectRatio);
        }
    }
}
