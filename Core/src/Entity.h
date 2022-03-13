#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <entt/entt.hpp>
#include "Scene.h"

#include "components/Transform.h"

namespace Phantom {
	class Entity
	{

	public:
		Entity(entt::entity id, Scene* scene);
		Entity(Entity& other) = default;

		Transform* transform();
		void SetTransform(Transform* transform);
		template<typename Component> bool HasComponent();
		template<typename Component, typename... Args> Component& AddComponent(Args&&... args);
		template<typename Component> Component& GetComponent();
		template<typename Component> void RemoveComponent();

		operator bool() { return _id != entt::null; }
	private:
		Transform* _transform;
		Scene* _scene = nullptr;
		entt::entity _id = entt::null;
	};

	template<typename Component>
	inline bool Entity::HasComponent()
	{
		return _scene->_registry.all_of<Component>();;
	}

	template<typename Component, typename... Args>
	inline Component& Entity::AddComponent(Args&&... args)
	{
		//assert check if it already has component
		// Assert(HasComponent<T>())
		return _scene->_registry.emplace<Component>(_id, std::forward<Args>(args)...);
	}

	template<typename Component>
	inline Component& Entity::GetComponent()
	{
		//assert check if it has a component of that type
		// Assert(HasComponent<T>())
		return _scene->_registry.get<Component>(_id);
	}
	template<typename Component>
	inline void Entity::RemoveComponent()
	{
		//assert check if it has a component of that type
		// Assert(HasComponent<T>())
		_scene->_registry.remove<Component>(_id);
	}
}

#endif;
