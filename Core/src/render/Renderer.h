#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "../shader/Shader.h"
#include "../components/Components.h"
#include "../components/Transform.h"
#include "../components/Camera.h"
#include "FrameBuffer.h"

namespace Phantom
{
	class Scene;
	class Entity;
	class Renderer
	{
	public:
		Renderer();
		bool Init(int width = 800, int heigth = 600);

		void SwapBuffers();
		void Draw(Scene& scene);
		void Clear(glm::vec4 color = glm::vec4(0.0f));

		void SetCursorMode(bool enabled);
		inline bool ShouldClose() { return glfwWindowShouldClose(_window); };
		static Renderer& Instance();
		inline GLFWwindow* window() { return _window; };

		// temp 
		inline const float&  Witdh() { return _width; }
		inline const float&  Height() { return _height; }
		inline FrameBuffer& ColorFrameBuffer() { return _colorFrameBuffer; }
	private:
		
		//temp width height mvoe to window or something class
		float _width;
		float _height;
		glm::mat4 _mvp;
		GLFWwindow* _window;
		FrameBuffer _colorFrameBuffer;
		static Renderer* _instance;

		void DrawLight(Transform& transform, Light& light);
		void DrawMesh(Transform& model, MeshRenderer& meshRenderer, Scene& scene);
	};
}

#endif

