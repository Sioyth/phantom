#include "Scene.h"
#include "Entity.h"
#include "../render/Renderer.h"
#include "../components/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Phantom
{
	Scene::Scene(bool stock)
	{
		/*_activeCamera = CreateEntity("MainCamera");
		_activeCamera->AddComponent<Camera>();
		_activeCamera->transform()->Translate(glm::vec3(0.0f, 1.0f, 10.0f));
		_editorCamera.Translate(glm::vec3(0.0f, 1.0f, 10.0f));*/
		//_editorCamera.Translate(glm::vec3(0.0f, 2.0f, 10.0f));

		if (!stock)
			return;

		Mesh planeMesh;
	  Entity* plane = CreateEntity("Plane")->get();
	  //plane.GetComponent<Transform>().Scale(glm::vec3(2.0f));
	  plane->AddComponent<MeshRenderer>(planeMesh);
  
	  Entity* plane2 = CreateEntity()->get();
	  plane2->GetComponent<Transform>().Scale(glm::vec3(10.0f));
	  plane2->AddComponent<MeshRenderer>(planeMesh);

	  Entity* light = CreateEntity()->get();
	  light->GetComponent<Transform>().Translate(glm::vec3(0.0f, 1.0f, 2.0f));
	  light->AddComponent<Light>(glm::vec3(1.0f, 0.0f, 1.0f));

	}

	Scene::~Scene()
	{
		delete _activeCamera;
	}

	void Scene::Update(const float& dt)
	{
		//Renderer::Instance().Render(*this);
	}

	Entity* Scene::activeCamera()
	{
		return _activeCamera;
	}

	std::unique_ptr<Entity>* Scene::CreateEntity(const std::string& name)
	{
		_entities.push_back(std::unique_ptr<Entity>(new Entity(_registry, name)));
		return &_entities.back();
	}
}
