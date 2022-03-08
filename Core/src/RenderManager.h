#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Shader/Shader.h"
#include "Components.h"

namespace Phantom
{
	class RenderManager
	{
	public:
		RenderManager();
		bool Init(int width = 800, int heigth = 600);

		void End();
		void Begin(glm::vec4 color = glm::vec4(0.0f));
		void DrawMesh(Transform& transform, MeshRenderer& meshRenderer);

		static RenderManager& Instance();

	private:
		float _width;
		float _height;
		glm::mat4 _mvp;
		glm::mat4 _proj;
		glm::mat4 _model;
		GLFWwindow* _window;
		static RenderManager* _instance;
	};
}

#endif

