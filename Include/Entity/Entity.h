#pragma once
#include <unordered_map>
#include "Components/Components.h"
#include <algorithm>
#include "Tools/typeCounter.h"

class Entity {
private:
	static std::unordered_map<int, Entity*> m_entities;
	static int m_nextID;  // Static variable to track the next ID
	const int m_ID;       // Constant ID value for each entity

	// keep track of connected components
	std::unordered_map<int, std::vector<Component*>> m_components;

public:

	template<typename T>
	void AddComponent(T* ptr)
	{
		auto typeID = GetTypeID<T>();
		auto iter = m_components.find(typeID);

		if (iter == m_components.end()) {
			m_components[typeID] = std::vector<Component*>();
		}
		m_components[typeID].push_back(ptr);

	}

	static Entity* GetEntity(int ID);

	Entity() : m_ID(m_nextID++) { m_entities[m_ID] = this; }

	template<typename T>
	std::vector<T*> GetComponents()
	{
		using ComponentPtr = T*;
		auto typeID = GetTypeID<T>();
		if (m_components.find(typeID) != m_components.end())
		{
			const auto& components = m_components[typeID];
			std::vector<ComponentPtr> typedComponents(components.size());
			std::transform(components.begin(), components.end(), typedComponents.begin(),
				[](Component* component) { return static_cast<ComponentPtr>(component); });
			return typedComponents;
		}
		else
		{
			return {}; // Return an empty vector
		}
	}

	int GetID() const {
		return m_ID;
	}

	~Entity();
};


