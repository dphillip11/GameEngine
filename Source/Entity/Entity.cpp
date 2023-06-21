#include "Entity/Entity.h"

EntityRef EntityRegistry::CreateEntity(ComponentRegistry& component_registry) {
	Entity tempEntity;
	tempEntity.m_entity_registry = this;
	tempEntity.m_component_registry = &component_registry;
	int id = HashedVector<Entity>::push_back(tempEntity);
	Entity& entity = HashedVector<Entity>::operator[](id);
	entity.m_id = id;

	EntityRef ref;
	ref.m_entityID = id;
	ref.m_entity_registry = this;
	return ref;
}

EntityRef EntityRegistry::GetRef(int entityID)
{
	EntityRef ref;
	ref.m_entityID = entityID;
	ref.m_entity_registry = this;
	return ref;
}