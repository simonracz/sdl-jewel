//
//  LogicSystem.h
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#ifndef __sdl_jewel__LogicSystem__
#define __sdl_jewel__LogicSystem__

#include "EntitySystem.h"
#include "InputHandler.h"
#include <map>

namespace artemis {
	class Entity;
}

namespace jewel {
	
class Action;
class Table;
class Sprite;
class AssetManager;
	
class LogicSystem : public artemis::EntitySystem, public InputDelegate {
public:
	LogicSystem(Table* table, AssetManager* assetManager, Sprite* aLongLivedSprite);
	~LogicSystem();
	
	void setProcessing(bool process);
	void setInputHandler(InputHandler* inputHandler);
	
	void nodeTouchedAt(int index) override;
	void nodeSlidTo(int index, Direction direction) override;
	
	void addEntity(int index, artemis::Entity* entity);
	static SDL_Rect srcRectToNodeType(NodeType type);
protected:
	bool checkProcessing() override;
	
	void begin() override;
	void processEntities(artemis::ImmutableBag<artemis::Entity*> & bag) override;
	void end() override;
private:
	InputHandler* inputHandler{nullptr};
	AssetManager* assetManager;
	Table* table;
	Sprite* lSprite;
	std::set<int> toBeRemoved;
	bool toBeBoom{false};
	bool afterBoom{false};
	void boom();
	void removeEntity(int index);

	//The first parameter is the table index.
	//It is possible that there is no entity for a given valid index
	//when the gems are falling, therefore this can't be a vector.
	std::map<int, artemis::Entity*> entities;
	
	bool hasSelection{false};
	int selectedIndex1;
	int selectedIndex2;
		
	void startSwapping(int index1, int index2);
	void swapEntities(int index1, int index2);

	void createNewEntities(const std::set<int>& newNodes);
	void fellEntities(const std::set<int>& fNodes);
	
	void checkForEmptyFields();
	
	bool processing{false};
};
	
} //namespace


#endif /* defined(__sdl_jewel__LogicSystem__) */
