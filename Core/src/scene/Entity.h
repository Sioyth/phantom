#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <entt/entt.hpp>
#include "../components/Transform.h"

namespace Phantom {
	class Entity
	{

		public:
			Entity(entt::registry& registry, std::string name = "Empty Entity");
			~Entity();

			Transform* transform();
			void AddChild(Entity* child);
			void SetParent(Entity* parent);
			void RemoveChild(Entity* child);
			void SetTransform(Transform* transform);
			inline std::string& Name() { return _name; };
			inline const Entity* Parent() { return _parent; };
			inline std::vector<Entity*>& Children() { return _children; };
			template<typename Component> bool HasComponent();
			template<typename Component, typename... Args> Component& AddComponent(Args&&... args);
			template<typename Component> Component& GetComponent();
			template<typename Component> void RemoveComponent();

			operator bool() { return _id != entt::null; }
		private:
			
			Entity* _parent;
			std::string _name;
			Transform* _transform;
			entt::registry* _registry;
			std::vector<Entity*> _children;
			entt::entity _id = entt::null;
	};

	template<typename Component>
	inline bool Entity::HasComponent()
	{
		return _registry->all_of<Component>();
	}

	template<typename Component, typename... Args>
	inline Component& Entity::AddComponent(Args&&... args)
	{
		//assert check if it already has component
		// Assert(HasComponent<T>())
		return _registry->emplace<Component>(_id, std::forward<Args>(args)...);
	}

	template<typename Component>
	inline Component& Entity::GetComponent()
	{
		//assert check if it has a component of that type
		// Assert(HasComponent<T>())
		return _registry->get<Component>(_id);
	}
	template<typename Component>
	inline void Entity::RemoveComponent()
	{
		//assert check if it has a component of that type
		// Assert(HasComponent<T>())
		_registry->remove<Component>(_id);
	}
}

#endif;
