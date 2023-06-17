#include "Entity/Entity.h"


int Entity::m_nextID = 0;
std::unordered_map<int, Entity*> Entity::m_entities;



Entity::~Entity() {
	// deactivate components
	for (auto componentVector : m_components)
	{
		for (auto component : componentVector.second)
		{
			component->Active = false;
		}
	}
	// remove ID from entities
	auto iter = m_entities.find(m_ID);

	if (iter != m_entities.end()) {
		// Key exists, erase the vector associated with it
		m_entities.erase(iter);
	}
}

Entity* Entity::GetEntity(int ID)
{
	auto iter = m_entities.find(ID);
	if (iter != m_entities.end()) {
		return m_entities[ID];
	}
	else
		return nullptr;

}