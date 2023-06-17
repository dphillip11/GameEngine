#pragma once
#include <vector>
#include <unordered_map>
#include "Entity/entity.h"


// a container that registers components with entities
template <typename ComponentType>
class ComponentContainer
{
public:
	std::vector<ComponentType> m_components;
private:
	friend class ComponentRegistry;
	ComponentContainer()
	{
		m_components.reserve(200);
	}
	ComponentType* _registerComponent(Entity& entity)
	{
		ComponentType new_component;
		new_component.GameObjectID = entity.GetID();
		m_components.emplace_back(new_component);
		entity.AddComponent(&m_components.back());
		return &m_components.back();
	}

	std::vector<ComponentType>& _getComponents()
	{
		return m_components;
	}

	void _cullInactive()
	{
		m_components.erase(
			std::remove_if(
				m_components.begin(),
				m_components.end(),
				[](ComponentType& component)
				{
					return !component.Active;
				}
			),
			m_components.end()
					);
	}
};

// creates component containers as required
class ComponentRegistry
{
public:
	template <typename ComponentType>
	ComponentContainer<ComponentType>& GetContainer()
	{
		static ComponentContainer<ComponentType> container;
		return container;
	}

	template <typename ComponentType>
	ComponentType* RegisterComponent(Entity& entity)
	{
		return GetContainer<ComponentType>()._registerComponent(entity);
	}

	template <typename ComponentType>
	std::vector<ComponentType*> GetComponents(Entity& entity)
	{
		return entity.GetComponents<ComponentType>();
	}

	template <typename ComponentType>
	std::vector<ComponentType>& GetComponentVector()
	{
		auto& container = GetContainer<ComponentType>();
		return container._getComponents();
	}

	template <typename ComponentType>
	std::vector<ComponentType>& GetComponents()
	{
		return GetContainer<ComponentType>()._getComponents();
	}

	template <typename ComponentType>
	void CullInactive()
	{
		GetContainer<ComponentType>()._cullInactive();
	}

};
