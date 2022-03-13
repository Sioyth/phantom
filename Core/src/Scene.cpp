#include "Scene.h"
#include "Entity.h"
#include "Components/Components.h"
#include "Renderer.h"
#include "Input.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Phantom
{
	Scene::Scene()
	{
		_activeCamera = new Entity(_registry.create(), this);
		_activeCamera->AddComponent<Camera>();
		_activeCamera->transform()->Translate(glm::vec3(0.0f, 1.0f, 10.0f));
	}

	Scene::~Scene()
	{
		delete _activeCamera;
	}

	void Scene::Update(const float& dt)
	{
		if (Input::Instance()->GetKey(GLFW_KEY_W, KeyState::PRESS))
			_activeCamera->transform()->Translate(_activeCamera->transform()->forward() * 1.0f * dt);
		if (Input::Instance()->GetKey(GLFW_KEY_S, KeyState::PRESS))
			_activeCamera->transform()->Translate(-_activeCamera->transform()->forward() * 1.0f * dt);
		if (Input::Instance()->GetKey(GLFW_KEY_A, KeyState::PRESS))
			_activeCamera->transform()->Translate(-_activeCamera->transform()->right() * 1.0f * dt);
		if (Input::Instance()->GetKey(GLFW_KEY_D, KeyState::PRESS))
			_activeCamera->transform()->Translate(_activeCamera->transform()->right() * 1.0f * dt);

		Renderer::Instance().Draw(*this);
	}

	Entity* Scene::activeCamera()
	{
		return _activeCamera;
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = Entity( _registry.create(), this);
		return entity;
	}
}
