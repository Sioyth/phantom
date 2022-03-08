#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "RenderManager.h"

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
		auto group = _registry.group<Transform, MeshRenderer>();
		for (auto entity : group)
		{
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
