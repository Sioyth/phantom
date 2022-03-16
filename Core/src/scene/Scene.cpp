#include "Scene.h"
#include "Entity.h"
#include "../render/Renderer.h"
#include "../components/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Phantom
{
	Scene::Scene()
	{
		_activeCamera = CreateEntity("MainCamera");
		_activeCamera->AddComponent<Camera>();
		_activeCamera->transform()->Translate(glm::vec3(0.0f, 1.0f, 10.0f));
		_editorCamera.Translate(glm::vec3(0.0f, 1.0f, 10.0f));
	}

	Scene::~Scene()
	{
		delete _activeCamera;
	}

	void Scene::Update(const float& dt)
	{
	
		_editorCamera.Update(dt);
		Renderer::Instance().Draw(*this);
	}

	Entity* Scene::activeCamera()
	{
		return _activeCamera;
	}

	Entity* Scene::CreateEntity(const std::string& name)
	{
		Entity entity = Entity(_registry, name);
		_entities.push_back(entity);
		return &_entities.back();
	}
}