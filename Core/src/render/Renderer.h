#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "../shader/Shader.h"
#include "../components/Components.h"
#include "../components/Transform.h"
#include "../components/Camera.h"
#include "../scene/EditorCamera.h"
#include "FrameBuffer.h"

namespace Phantom
{
	class Scene;
	class Entity;
	class Renderer
	{
	public:
		Renderer();

		void Render(Scene& scene, EditorCamera& camera, const float& aspectRatio);
		void Clear(glm::vec4 color = glm::vec4(0.0f));
		static Renderer* Instance();

	private:
		
		static Renderer* _instance;

		void DrawLight(Transform& transform, Light& light);
		void DrawMesh(Transform& model, MeshRenderer& meshRenderer, Scene& scene, EditorCamera& camera, const float& aspectRatio);
	};
}

#endif

