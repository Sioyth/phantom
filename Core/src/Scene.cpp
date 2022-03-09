#include "Scene.h"
#include "Entity.h"
#include "Components/Components.h"
#include "RenderManager.h"
#include "Input.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Phantom
{
	Scene::Scene()
	{
		entt::entity entity = _registry.create();
	}

	Scene::~Scene()
	{

	}
	void Scene::Update()
	{
		auto view = _registry.view<Transform>();
		for (auto entity : view)
		{
			
			if (Input::Instance()->GetKey(GLFW_KEY_W, KeyState::PRESS))
			{
				auto& t = view.get<Transform>(entity);
				/*glm::transpose(glm::mat4(1.0f), glm::vec3(1.0f));
				t._matrix = glm::transpose(t._matrix, glm::vec3(0.0f, 0.0f, 0.1f));*/
			}
		}

		// Move this to render?
		auto group = _registry.group<Transform, MeshRenderer>();
		for (auto entity : group)
		{
			// It's making a copy here fix this
			auto [transform, mesh] = group.get<Transform, MeshRenderer>(entity);
			RenderManager::Instance().DrawMesh(transform, mesh);
		}
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { _registry.create(), this };
		entity.AddComponent<Transform>();
		auto& tag = entity.AddComponent<Tag>();
		tag._name = name.empty() ? "Entity" : name;

		return entity;
	}
}
