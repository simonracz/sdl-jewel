#include "World.h"
#include "Entity.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "EntitySystem.h"
#include "SystemBitManager.h"

namespace artemis {

	World::World() {
		//TODO add more managers
		this->systemManager = new SystemManager(*this);
		this->entityManager = new EntityManager(*this);
		this->groupManager = new GroupManager();
		this->tagManager = new TagManager();
		delta = 0;
	}

	void World::deleteEntity(Entity& e) {
		if(!deleted.contains(&e))
			deleted.add(&e);
	}

	float World::getDelta() {
		return this->delta;
	}

	SystemManager* World::getSystemManager() {
		return systemManager;
	}

	EntityManager* World::getEntityManager() {
		return entityManager;
	}
	
	GroupManager* World::getGroupManager(){
		return groupManager;
	}
	
	TagManager* World::getTagManager(){
		return tagManager;
	}

	void World::loopStart() {
		if(!refreshed.isEmpty()) {
			for(int i=0; i<refreshed.getCount(); i++) {
				//TODO ADD  MANAGERs
				entityManager->refresh(*refreshed.get(i));
			}

			refreshed.clear();

		}

		if(!deleted.isEmpty()) {
			for(int i=0; i<deleted.getCount(); i++) {
				Entity & e = *deleted.get(i);
				groupManager->remove(e);
				tagManager->remove(e);
				entityManager->remove(e);
			}

			deleted.clear();
		}

	}
	
	void World::process() {
		Bag<EntitySystem*>& systems = systemManager->getSystems();
		for(int i=0; i < systems.getCount(); ++i)
		{
			systems.get(i)->process();
		}
		return;
	}
	
	EntitySystem& World::addSystem(EntitySystem* stm) {
		return systemManager->setSystem(stm);
	}
	
	void World::initialize() {
		systemManager->initializeAll();
	}

	Entity& World::createEntity() {
		return entityManager->create();
	}

	Entity& World::getEntity(int entityId) {
		return entityManager->getEntity(entityId);
	}


	void World::refreshEntity(Entity& e) {
		refreshed.add(&e);
	}

	void World::setDelta(float delta) {
		this->delta = delta;
	}

	World::~World() {
		//Entity manager should be deleted first.
		delete entityManager;
		delete systemManager;
		delete groupManager;
		delete tagManager;
		ComponentTypeManager::deleteComponentTypes();
		SystemBitManager::removeBitSets();
	}
};
