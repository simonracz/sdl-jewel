//
//  LogicSystem.cpp
//  sdl-jewel
//
//  Created by Simon Racz on 26/03/14.
//  Copyright (c) 2014 Simon Racz. All rights reserved.
//

#include "LogicSystem.h"
#include "Table.h"
#include "RenderingComponent.h"
#include "Entity.h"
#include <cmath>
#include "Action.h"
#include "World.h"
#include "AssetManager.h"
#include "EntityManager.h"

namespace jewel {

const float LogicSystem::GAME_SPEED = 0.2;
	
LogicSystem::LogicSystem(Table* table, AssetManager* assetManager, Sprite* aLongLivedSprite, ScoreDelegate* delegate) : table(table), assetManager(assetManager), lSprite(aLongLivedSprite), delegate(delegate)
{
	//empty
}

void LogicSystem::setInputHandler(InputHandler* inputHandler)
{
	this->inputHandler = inputHandler;
}
	
LogicSystem::~LogicSystem()
{

}

void LogicSystem::nodeTouchedAt(int index)
{
	//std::cout << "node touched at " << index << "\n";
	
	if (hasSelection) {
		if ((std::abs(selectedIndex1 - index) == 1) || (std::abs(selectedIndex1 - index) == 8)) {
			inputHandler->setProcessing(false);
			entities[selectedIndex1]->getComponent<RenderingComponent>()->selected = false;
			selectedIndex2 = index;
			processing = true;
		} else {
			entities[selectedIndex1]->getComponent<RenderingComponent>()->selected = false;
			entities[index]->getComponent<RenderingComponent>()->selected = true;
			selectedIndex1 = index;
		}
	} else {
		entities[index]->getComponent<RenderingComponent>()->selected = true;
		selectedIndex1 = index;
		hasSelection = true;
	}
}

void LogicSystem::nodeSlidTo(int index, Direction direction)
{
	if (hasSelection) {
		entities[selectedIndex1]->getComponent<RenderingComponent>()->selected = false;
	}
	switch (direction) {
		case Direction::Left:
			//std::cout << "node at index " << index << " slid to left\n";
			if ((index % 8)!=0) {
				inputHandler->setProcessing(false);
				selectedIndex1 = index;
				selectedIndex2 = index - 1;
				hasSelection = true;
				processing = true;
			}
			break;
		case Direction::Right:
			//std::cout << "node at index " << index << " slid to right\n";
			if ((index % 8)!=7) {
				inputHandler->setProcessing(false);
				selectedIndex1 = index;
				selectedIndex2 = index + 1;
				hasSelection = true;
				processing = true;
			}
			break;
		case Direction::Up:
			//std::cout << "node at index " << index << " slid to up\n";
			if ((index / 8)!=0) {
				inputHandler->setProcessing(false);
				selectedIndex1 = index;
				selectedIndex2 = index - 8;
				hasSelection = true;
				processing = true;
			}
			break;
		case Direction::Down:
			//std::cout << "node at index " << index << " slid to down\n";
			if ((index / 8)!=7) {
				inputHandler->setProcessing(false);
				selectedIndex1 = index;
				selectedIndex2 = index + 8;
				hasSelection = true;
				processing = true;
			}
			break;
	}
	
}
	
template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}
	
void LogicSystem::startSwapping(int ind1, int ind2)
{
	using namespace std;
		
	Sprite* sprite1 = entities[ind1]->getComponent<RenderingComponent>()->sprite;
	Sprite* sprite2 = entities[ind2]->getComponent<RenderingComponent>()->sprite;
	
	int x1 = - 80 * sgn(ind1 - ind2) * (std::abs(ind1 - ind2) % 8);
	int x2 =   80 * sgn(ind1 - ind2) * (std::abs(ind1 - ind2) % 8);
	int y1 = - 80 * sgn((ind1 - ind2)/8);
	int y2 =   80 * sgn((ind1 - ind2)/8);
	
	if (table->checkSwap(ind1, ind2)) {
		sprite1->runAction(Action::moveBy(GAME_SPEED, x1, y1));
		sprite2->runAction(Action::moveBy(GAME_SPEED, x2, y2));
		table->swapElements(ind1, ind2);
		swapEntities(ind1, ind2);
		//BOOM:)
		lSprite->runAction(Action::sequence({Action::wait(GAME_SPEED), Action::callFunction([this]{
			toBeBoom = true;
			setProcessing(true);
		})}));
		return;
	}
	
	//wrong path
	sprite1->runAction(Action::sequence({Action::moveBy(GAME_SPEED, x1, y1), Action::moveBy(GAME_SPEED, x2, y2)}));
	sprite2->runAction(Action::sequence({Action::moveBy(GAME_SPEED, x2, y2), Action::moveBy(GAME_SPEED, x1, y1)}));

	lSprite->runAction(Action::sequence({Action::wait(2*GAME_SPEED), Action::callFunction([this]{
		inputHandler->setProcessing(true && !isGameOver);
	})}));
}
	
void LogicSystem::swapEntities(int ind1, int ind2)
{
	using namespace artemis;
	
	if (entities.count(ind1) == 0) {
		if (entities.count(ind2) == 0) {
			return;
		}
		
		entities[ind1] = entities[ind2];
		entities.erase(ind2);
		return;
	}
		
	Entity* e1 = entities[ind1];
	
	if (entities.count(ind2) == 0) {
		entities[ind2] = e1;
		entities.erase(ind1);
		return;
	}
	
	Entity* e2 = entities[ind2];
	
	entities[ind1] = e2;
	entities[ind2] = e1;
}

void LogicSystem::boom()
{
	using namespace std;
	
	set<int> results;
	table->check(results);
	int size = static_cast<int>(results.size());
	//std::cerr << "at boom() table->check results size : " << results.size() << "\n";
	if (results.empty()) {
		inputHandler->setProcessing(true && !isGameOver);
		return;
	}
	
	for (auto ind : results) {
		entities[ind]->getComponent<RenderingComponent>()->sprite->runAction(Action::sequence({Action::alphaTo(GAME_SPEED, 0), Action::callFunction([ind,this]{
			removeEntity(ind);
		})}));
	}
	lSprite->runAction(Action::sequence({
		Action::wait(GAME_SPEED/2),
		Action::callFunction([this, size]{
			delegate->addScore(size);
		}),
		Action::wait(GAME_SPEED/2),
		Action::callFunction([this]{
			afterBoom = true;
			setProcessing(true);
		})}));
	
}
	
void LogicSystem::removeEntity(int index)
{
	artemis::Entity* entity = entities[index];
	world->getEntityManager()->remove(*entity);
	entities.erase(index);
}

void LogicSystem::checkForEmptyFields()
{
	using namespace std;
	
	if (!afterBoom && !table->hasEmpty()) {
		boom();
		return;
	}

	
	set<int> nodesToFall;
	set<int> newNodes;
	table->applyNextStep(nodesToFall, newNodes, afterBoom);
	afterBoom = false;
	/*
	std::cerr << "nodesToFall size : " << nodesToFall.size() << " ,newNodes size : " << newNodes.size() << "\n";
	for (auto it : nodesToFall) {
		std::cerr << "nodesToFall elements : " << it << "\n";
	}
	for (auto it : newNodes) {
		std::cerr << "newNodes : " << it << "\n";
	}*/
	
	createNewEntities(newNodes);
	fellEntities(nodesToFall);
}

void LogicSystem::fellEntities(const std::set<int>& fNodes)
{
	for (auto it = fNodes.rbegin(); it!=fNodes.rend(); ++it) {
		int i = (*it) - 8;
		swapEntities(i, i+8);
		entities[*it]->getComponent<RenderingComponent>()->sprite->runAction(Action::sequence({
			Action::moveBy(2*GAME_SPEED/3, 0, 80), Action::callFunction([this]{
				setProcessing(true);
			})}));
	}
	
	for (int i = 0; i<8; ++i) {
		entities.erase(i-8);
	}
}
	
void LogicSystem::createNewEntities(const std::set<int>& newNodes)
{
	using namespace artemis;
	
	SDL_Texture* gemTexture = assetManager->getTexture(AssetManager::TEXTURE_GEMS);
	Sprite* sprite = nullptr;
	int offsetX = 240;
	int offsetY = 192;
	for (auto it = newNodes.begin(); it != newNodes.end(); ++it) {
		sprite = new Sprite(gemTexture, LogicSystem::srcRectToNodeType(table->getNode((*it)).type));
		int indexX = (*it) % 8;
		int indexY = (*it) / 8;
		sprite->setPosition(offsetX + indexX*80, offsetY + indexY*80 - 80);
		Entity& entity = world->createEntity();
		entity.addComponent(new RenderingComponent(sprite));
		world->getEntityManager()->refresh(entity);
		addEntity((*it) - 8, &entity);
	}
}

SDL_Rect LogicSystem::srcRectToNodeType(NodeType type)
{
	switch(type) {
		case NodeType::Blue:
			return SDL_Rect{0,0,40,40};
			break;
		case NodeType::Green:
			return SDL_Rect{40,0,40,40};
			break;
		case NodeType::Purple:
			return SDL_Rect{80,0,40,40};
			break;
		case NodeType::Red:
			return SDL_Rect{0,40,40,40};
			break;
		case NodeType::Yellow:
			return SDL_Rect{40,40,40,40};
			break;
		case NodeType::None:
			return SDL_Rect{0,0,0,0};
			break;
	}
}
	
void LogicSystem::gameOver() {
	isGameOver = true;
	inputHandler->setProcessing(false);
}
	
void LogicSystem::addEntity(int index, artemis::Entity* entity)
{
	entities[index] = entity;
}
	
void LogicSystem::setProcessing(bool process)
{
	processing = process;
}

bool LogicSystem::checkProcessing()
{
	return processing;
}

void LogicSystem::begin()
{

}
void LogicSystem::processEntities(artemis::ImmutableBag<artemis::Entity*>& bag)
{
	if (toBeBoom) {
		toBeBoom = false;
		boom();
		return;
	}
	
	if (hasSelection) {
		hasSelection = false;
		startSwapping(selectedIndex1, selectedIndex2);
		return;
	}
	
	checkForEmptyFields();
}
void LogicSystem::end()
{
	processing = false;
}

	
} //namespace
